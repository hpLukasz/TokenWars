#ifndef _CMDSQUEUE_H_
#define _CMDSQUEUE_H_

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "cmd.h"

class CmdsQueue
{
    protected:
        std::queue<ICmd> mQueue;
        std::mutex mMutex;
        std::unique_lock<std::mutex> mLock;
        std::condition_variable mCondVariable;
    public:
        CmdsQueue();
        virtual ~CmdsQueue();

        ICmd getCmd();
        bool empty();
        uint32_t size();

        bool addCmd(ICmd &cmd);
        bool addCmd(ICmd &&cmd);

        CmdsQueue(const CmdsQueue &) = delete;
        CmdsQueue & operator=(const CmdsQueue &) = delete;
        CmdsQueue(CmdsQueue &&) = delete;
        CmdsQueue & operator=(CmdsQueue &&) = delete;
};

CmdsQueue & getStoreInstance();

#endif /* _CMDSQUEUE_H_ */