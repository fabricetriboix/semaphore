#pragma once

#include <mutex>
#include <condition_variable>

class semaphore
{
public:
    semaphore() : count_(0) { }
    explicit semaphore(int initial_count) : count_(initial_count) { }
    ~semaphore() = default;

    using lock_t = std::unique_lock<std::mutex>;

    int count()
    {
        lock_t lock(mutex_);
        return count_;
    }

    void post()
    {
        lock_t lock(mutex_);
        ++count_;
        cv_.notify_one();
    }

    void take()
    {
        lock_t lock(mutex_);
        while (count_ <= 0) {
            cv_.wait(lock);
        }
        --count_;
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int count_;

    semaphore(const semaphore&) = delete;
    semaphore& operator=(const semaphore&) = delete;
};
