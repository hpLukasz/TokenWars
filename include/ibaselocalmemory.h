#ifndef _BASELOCALMEMORY_H_
#define _BASELOCALMEMORY_H_

#include <vector>
#include <stdint.h>

class IBaseLocalMemory
{
    protected:
        std::vector<uint32_t> mMemory;
    public:

        virtual uint32_t getSize() = 0;
        virtual bool setMemory(uint32_t value) = 0;
        virtual bool setMemory(uint32_t index, uint32_t value) = 0;
        virtual bool getMemory(uint32_t index, uint32_t & value) = 0;

};

#endif /* _BASELOCALMEMORY_H_ */