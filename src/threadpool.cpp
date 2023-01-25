#include "appdebug.h"
#include "threadpool.h"
#include <iostream>


ThreadPool::ThreadPool() : mActive(true)
{
    uint32_t hwThreadsNo = std::thread::hardware_concurrency();
#ifdef MY_DEBUG
    std::cout << "Available HW threads: " << hwThreadsNo << std::endl;
#endif

    for (uint32_t i=0; i<hwThreadsNo; i++)
    {
        mVec.push_back(std::thread(&ThreadPool::worker, this));
    }
}


ThreadPool::~ThreadPool()
{
    for(auto& t: mVec)
        t.join();
}

void ThreadPool::worker()
{
    while (mActive)
    {
        Task task;
        mQueue.pop(task);
        task();
    }
    
}

void ThreadPool::submit(Task task)
{
    mQueue.push(task);
}