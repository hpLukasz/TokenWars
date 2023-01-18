#include <memory>
#include <cstring>
#include "localmemory.h"

LocalMemory::LocalMemory(uint32_t size) : mSize(size)
{
    IBaseLocalMemory::mMemory = std::vector<uint32_t>(mSize);
    memset(&mMemory[0], 0, mMemory.size());
}

uint32_t LocalMemory::getSize()
{
    return mSize;
}


bool LocalMemory::setMemory(uint32_t value)
{
    return memset(&mMemory[0], value, mMemory.size()) != NULL;
}


bool LocalMemory::setMemory(uint32_t index, uint32_t value)
{
    if (index < mSize) 
    {
        mMemory[index] = value;
        return true;
    }
    else 
    {
        return false;
    }
}

bool LocalMemory::getMemory(uint32_t index, uint32_t * const value)
{
    if (index < mSize) 
    {
        *value = mMemory[index];
        return true;
    }
    else 
    {
        return false;
    }
}

std::ostream & operator<<(std::ostream &out, const LocalMemory &memory)
{
    int counter = 0;
    for (auto i: memory.mMemory)
    {
        out << std::hex << i << ((++counter%16) ? ' ': '\n');
    }

    return out;
}