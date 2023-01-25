#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include "concurrentqueue.h"
#include <thread>
#include <functional>
#include <vector>

using Task = std::function<void()>;

class ThreadPool
{
    private:
        bool mActive;
        ConcurrentQueue<Task> mQueue;
        std::vector<std::thread> mVec;
        void worker();
    public:
        ThreadPool();
        ~ThreadPool();
        void submit(Task task);
        void stopTasks() { mActive = false; };
};

#endif /* _THREADPOOL_H_ */