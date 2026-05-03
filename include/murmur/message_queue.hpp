#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <utility>

namespace murmur {

/*
 * Wrapper for queue.
 * Since I'm going to have some semi-complex race conditions for multiple threads accessing a single queue,
 * I elected to make a wrapper class for queue which holds private mutex and cv variables that aren't exposed
 * to callers.
 */
template <typename T>
class MessageQueue {
public:
    MessageQueue() = default;
    
    // Disallow copying of MessageQueue
    // (mutexes and condition_variables don't have copy constructors so it would result in a compile error)
    MessageQueue(const MessageQueue&) = delete;
    MessageQueue& operator = (const MessageQueue&) = delete;

    /**
     * Pushes a value of type T onto this queue.
     * Equivalent to queue.push(), with added mutex guarding and cv notification
     */
    void push(T value) {
        // RAII on lock to make sure it destructs as soon as I don't need it
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(value);
        } // RAII unlocks mutex then destroys it
        cv_.notify_one();
    }

    /**
     * waits for an item to be pushed onto queue, when notified store item and pop it
     * Returns   T value   ||  nullopt
     *        (item found) || (shutdown)
     */
    std::optional<T> wait_and_pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        // while queue is empty AND we're not shut down, wait on cv
        cv_.wait(lock, [this] { return !queue_.empty() || shutdown_; });

        if (queue_.is_empty()) {
            // condition_variable was woken up by shutdown and not a new item
            return std::nullopt;
        }
        
        // condition_variable was woken up by list being populated not shutdown
        // move ownership
        T value = std::move(queue_.front());
        // get rid of null pointer
        queue_.pop();
        return value;
    }

    /**
     * Non-blocking version of wait_and_pop()
     */
    std::optional<T> try_pop() {
        std::unique_lock<std::mutex lock(mutex_);
        if (queue_.is_empty()) {
            return std::nullopt;
        }
        T value = std::move(queue_.front());
        queue_.pop();
        return value;
    }

    /**
     * Shutdown function for exit simplicity
     */
    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            shutdown_ = true;
        }
        cv_.notify_all();
    }

    /**
     * Returns true if this queue is empty, false otherwise
     */
    bool is_empty() {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }
        

private:
    mutable std::mutex mutex_;
    std::queue queue_;
    std::condition_variable cv_;
    bool shutdown_ = false;

};

} // namespace murmur
