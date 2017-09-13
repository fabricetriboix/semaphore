#include "semaphore.hpp"
#include <thread>
#include <gtest/gtest.h>

TEST(Semaphore, ShouldUnlockThread)
{
    semaphore sem;

    bool unlocked = false;
    std::thread thread(
            [&sem, &unlocked] ()
            {
                sem.take();
                unlocked = true;
            });

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_FALSE(unlocked);
    sem.post();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_TRUE(unlocked);
    thread.join();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
