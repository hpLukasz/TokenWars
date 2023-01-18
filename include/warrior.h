#ifndef _WARRIOR_H_
#define _WARRIOR_H_

#include "warriorconfig.h"
#include "localmemory.h"
#include "iwarrioraccess.h"
#include "imasteraccess.h"
#include <cstring>
#include <list>


class Warrior : public IWarriorAccess
{
    protected:
        std::string mId;
        WarriorConfig mWarriorConfig;
        LocalMemory mMemory;
        uint32_t mTokensNo;

    public:
        Warrior(const std::string &wariorId, const WarriorConfig &config);
        LocalMemory& getMemory() { return mMemory; }

        //IWarriorAccess
        virtual std::string & getId() { return mId; }
        virtual bool isAlive() { return mTokensNo != 0; }
        virtual bool isToken(uint32_t memIndex);
        virtual void clearToken(uint32_t memIndex);
        virtual uint32_t getTokensNo() { return mTokensNo; };
        virtual uint32_t getMemSize() { return mMemory.getSize(); }
        //virtual bool duel(Warrior &enemy);
        bool duel(std::shared_ptr<IMasterAccess> master, std::list<std::shared_ptr<IWarriorAccess>> warriors);

        // Warrior(const Warrior &) = delete;
        // Warrior & operator=(const Warrior &) = delete;

        virtual ~Warrior() = default;
};


#endif /* _WARRIOR_H_ */