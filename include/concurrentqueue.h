#ifndef _CONCURRENTQUEUE_H_
#define _CONCURRENTQUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class ConcurrentQueue
{
    protected:
        std::queue<T> mQueue;
        std::mutex mMutex;
        std::condition_variable mConVariable;
    public:
        ConcurrentQueue() = default;
        void push(T& item) {
            std::lock_guard<std::mutex> lock(mMutex);
            mQueue.push(item);
            mConVariable.notify_one();
        }

        void pop(T& item)
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mConVariable.wait(lock, [this]{ return !mQueue.empty(); });
            item = mQueue.front();
            mQueue.pop();
        }
};

#endif /* _CONCURRENTQUEUE_H_ */