#ifndef _MASTER_H_
#define _MASTER_H_

#include "imasteraccess.h"
#include "warrioraccessimpl.h"
#include "cmdsqueue.h"
#include <vector>
#include <mutex>
#include <thread>
#include <memory>

class Master
{
    private:
        CmdsQueue & mCmds;
        bool mContinuesProcessing;
        bool mActive;

    public:
        Master(CmdsQueue &cmdsQueue);
        virtual ~Master();
        bool isEndOfGame(std::vector<std::shared_ptr<WarriorAccessImpl>> warriors, std::string& winner);
        bool proccessing(std::vector<std::shared_ptr<WarriorAccessImpl>> warriors);
        void setActive() { mActive = true; }

        bool dummyTask(std::vector<std::shared_ptr<WarriorAccessImpl>> warriors);
    
};


#endif /* _MASTER_H_ */