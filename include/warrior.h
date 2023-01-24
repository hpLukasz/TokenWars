#ifndef _WARRIOR_H_
#define _WARRIOR_H_

#include "warriorconfig.h"
#include "iwarrioraccess.h"
#include "warrioraccessimpl.h"
#include "imasteraccess.h"
#include "master.h"
#include "cmdsqueue.h"
#include <memory>
#include <vector>
#include <string>
#include <thread>


class Warrior : public WarriorAccessImpl
{
    private:
        CmdsQueue & mCmds;
    protected:
        WarriorConfig mWarriorConfig;

    public:
        Warrior(const WarriorConfig& config, CmdsQueue& cmdsQueue);
        virtual ~Warrior();

        LocalMemory& getMemory() { return mMemory; }
        bool duel(Master & master, std::vector<WarriorConfig> configs);

        bool dummyTask(std::vector<std::shared_ptr<WarriorAccessImpl>> warriors);
};


#endif /* _WARRIOR_H_ */