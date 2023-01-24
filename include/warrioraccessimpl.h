#ifndef _WARRIORACCESSIMPL_H_
#define _WARRIORACCESSIMPL_H_

#include "iwarrioraccess.h"
#include "localmemory.h"

class WarriorAccessImpl : public IWarriorAccess
{
    protected:
        std::string mId;
        LocalMemory mMemory;
        uint32_t mTokensNo;
    public:
        WarriorAccessImpl(const std::string& id, uint32_t memSize, uint32_t tokensNo);
        //IWarriorAccess
        virtual std::string & getId() { return mId; }
        virtual bool isAlive() { return mTokensNo != 0; }
        virtual bool isToken(uint32_t memIndex);
        virtual void clearToken(uint32_t memIndex);
        virtual uint32_t getTokensNo() { return mTokensNo; };
        virtual uint32_t getMemSize() { return mMemory.getSize(); }
}; 

#endif /* _WARRIORACCESSIMPL_H_ */