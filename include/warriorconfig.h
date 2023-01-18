#ifndef _WARRIORCONFIG_H_
#define _WARRIORCONFIG_H_

#include <cstdint>

class WarriorConfig
{
    private:
        uint32_t mSizeOfMemory;
        uint32_t mTokensNo;
    public:
        WarriorConfig(uint32_t memSize, uint32_t tokensNo) : mSizeOfMemory(memSize), mTokensNo(tokensNo) {}
        uint32_t getMemSize() { return mSizeOfMemory; }
        uint32_t getTokensNo() { return mTokensNo; }
};

#endif /* _WARRIORCONFIG_H_ */