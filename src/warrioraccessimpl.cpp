#include "warrioraccessimpl.h"
#include <iostream>
#include <functional>

WarriorAccessImpl::WarriorAccessImpl(const std::string& id, uint32_t memSize, uint32_t tokensNo) :
    mId(id), mMemory(memSize), mTokensNo(tokensNo)
{

}

bool WarriorAccessImpl::isToken(uint32_t memIndex)
{
    uint32_t dummy = 0;
    if (mMemory.getMemory(memIndex, std::ref(dummy)))
        return dummy == 1;
    else
        return false;
}

void WarriorAccessImpl::clearToken(uint32_t memIndex)
{
    if (isToken(memIndex))
    {
        mMemory.setMemory(memIndex, 0);
        if (--mTokensNo == 0)
        {
            std::cout << std::endl << mId << ": I am Dead !" << std::endl;
            // notify master ..
        }
    }
}