#ifndef _MASTER_H_
#define _MASTER_H_

#include "imasteraccess.h"
#include "warrior.h"
#include <list>
#include <mutex>

class Master : public IMasterAccess
{
    private:

    protected:
        bool mContinuesProcessing;
        std::mutex mQueueMutex;
        std::unique_lock<std::mutex> mLock;

    public:
        Master();
        virtual bool addCmd(const ICmd &cmd);
        void proccessing(std::list<std::shared_ptr<Warrior>> warriors);
        void startProcessing(std::list<std::shared_ptr<Warrior>> warriors);
        void stopProcessing() { mContinuesProcessing = false; }
    
};


#endif /* _MASTER_H_ */