#pragma once

#include <queue>

namespace murmur {

template <typename T>
class MessageQueue {
public:
    MessageQueue() = default;
    
    // Disallow copying of MessageQueue (mutexes and condition_variables don't have copy constructors so it would result in a compile error)
    MessageQueue(const MessageQueue&) = delete;
    MessageQueue& operator = (const MessageQueue&) = delete;
    void push(T value) {
        // RAII on lock to make sure it destructs as soon as I don't need it
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(T);
        } // RAII unlocks mutex
        cv_.notify_one();
    }

    // wait_and_pop could remain waiting until queue is destroyed, so return is optional
    std::optional<T> wait_and_pop() {
        return NULL;
    }

    // try_pop could opperate on an empty queue so return is optional
    std::optional<T> try_pop() {
        return NULL;
    }

    bool is_empty() {
        return true;
    }
        

private:
    mutable std::mutex mutex_;
    std::queue queue_;
    std::condition_variable cv_;

};

} // namespace murmur
