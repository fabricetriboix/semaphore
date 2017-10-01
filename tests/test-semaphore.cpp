#include "semaphore.hpp"
#include <thread>
#include <gtest/gtest.h>

TEST(Semaphore, ShouldUnlockThread)
{
    ft::semaphore_t sem;

    bool taken = false;
    std::thread thread(
            [&sem, &taken] ()
            {
                sem.take();
                taken = true;
            });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_FALSE(taken);
    sem.post();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_TRUE(taken);
    thread.join();
}

TEST(Semaphore, TakeWithTimeoutShouldSucceed)
{
    ft::semaphore_t sem;

    bool taken = false;
    std::thread thread(
            [&sem, &taken] ()
            {
                if (sem.take(std::chrono::milliseconds(20))) {
                    taken = true;
                }
            });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_FALSE(taken);
    sem.post();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_TRUE(taken);
    thread.join();
}

TEST(Semaphore, TakeWithTimeoutShouldTimeout)
{
    ft::semaphore_t sem;

    bool taken = false;
    std::thread thread(
            [&sem, &taken] ()
            {
                if (sem.take(std::chrono::milliseconds(10))) {
                    taken = true;
                }
            });

    std::this_thread::sleep_for(std::chrono::milliseconds(15));
    ASSERT_FALSE(taken);
    sem.post();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_FALSE(taken);
    thread.join();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
