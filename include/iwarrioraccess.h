#ifndef _IWARRIORACCESS_H_
#define _IWARRIORACCESS_H_

#include <cstdint>
#include <string>

class IWarriorAccess
{
    public:
        //IWarriorAccess(std::string &wariorId) : mId(wariorId) {}
        virtual std::string & getId() = 0;
        virtual bool isAlive() = 0;
        virtual bool isToken(uint32_t memIndex) = 0;
        virtual void clearToken(uint32_t memIndex) = 0;
        virtual uint32_t getTokensNo() = 0;
        // virtual bool duel(const IWarriorAccess *) = 0;
        virtual uint32_t getMemSize() = 0;
};


#endif /* _IWARRIORACCESS_H_ */