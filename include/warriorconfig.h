#ifndef _WARRIORCONFIG_H_
#define _WARRIORCONFIG_H_

#include <cstdint>
#include <string>

class WarriorConfig
{
    private:
        uint32_t mSizeOfMemory;
        uint32_t mTokensNo;
        std::string mId;
    public:
        WarriorConfig(uint32_t memSize, uint32_t tokensNo, std::string id) : 
            mSizeOfMemory(memSize), mTokensNo(tokensNo), mId(id) {}
        uint32_t getMemSize() { return mSizeOfMemory; }
        uint32_t getMemSize() const { return mSizeOfMemory; }
        uint32_t getTokensNo() { return mTokensNo; }
        uint32_t getTokensNo() const { return mTokensNo; }
        std::string getId() { return mId; }
        std::string getId() const { return mId; }
};

#endif /* _WARRIORCONFIG_H_ */