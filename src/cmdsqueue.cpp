#include "appdebug.h"
#include "cmdsqueue.h"
#include <iostream>

CmdsQueue::CmdsQueue() :
    mLock(mMutex, std::defer_lock)
{
    std::cout << "CmdsQueue constructor" << std::endl;
}

CmdsQueue::~CmdsQueue()
{
    // if (! mLock.try_lock())
    //     mLock.unlock();

    while (! mQueue.empty())
        mQueue.pop();
    
    std::cout << "CmdsQueue destructor" << std::endl;
}

bool CmdsQueue::addCmd(ICmd &cmd)
{
    // mLock.lock();
    std::unique_lock<std::mutex> lock(mMutex);
#ifdef MY_DEBUG
    std::cout << "Add " << cmd << std::endl;
    std::flush(std::cout);
#endif
    mQueue.push(cmd);
    // mLock.unlock();

    return true;
}

bool CmdsQueue::addCmd(ICmd &&cmd)
{
    // mLock.lock();
    std::unique_lock<std::mutex> lock(mMutex);
#ifdef MY_DEBUG
    std::cout << "Add " << cmd << " [" << mQueue.size()+1 << "]" << std::endl;
    std::flush(std::cout);
#endif
    mQueue.push(cmd);
    // mLock.unlock();

    return true;
}

ICmd CmdsQueue::getCmd()
{
    std::unique_lock<std::mutex> lock(mMutex);
    // mLock.lock();
    ICmd tmp = mQueue.front();
#ifdef MY_DEBUG
    std::cout << "Take " << tmp << " [" << mQueue.size() << "]" << std::endl;
    std::flush(std::cout);
#endif
    mQueue.pop();
    // mLock.unlock();

    return tmp;
}

bool CmdsQueue::empty()
{
    std::unique_lock<std::mutex> lock(mMutex);
    // mLock.lock();
    bool e = mQueue.empty();
    // mLock.unlock();
    return e;
}

uint32_t CmdsQueue::size()
{
    std::unique_lock<std::mutex> lock(mMutex);;
    return mQueue.size();
}

// C++17 protect by multithreading access to the static variable
CmdsQueue & getStoreInstance()
{
    static CmdsQueue oneStore;
    return oneStore;
}