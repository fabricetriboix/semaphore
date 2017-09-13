# semaphore

Simple intra-process semaphore

Usage:

    #include <semaphore.hpp>

    semaphore sem;
    sem.post();
    sem.take(); // potentially blocking

