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
        

private:
    mutable std::mutex mutex_;
    std::queue queue_;
    std::condition_variable cv_;

};

} // namespace murmur
