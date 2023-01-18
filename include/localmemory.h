#ifndef _LOCALMEMORY_H_
#define _LOCALMEMORY_H_

#include "ibaselocalmemory.h"
#include <iostream>

class LocalMemory : public IBaseLocalMemory
{
    private:
        uint32_t mSize;
    public:
        LocalMemory(uint32_t size);

        virtual uint32_t getSize();
        virtual bool setMemory(uint32_t value);
        virtual bool setMemory(uint32_t index, uint32_t value);
        virtual bool getMemory(uint32_t index, uint32_t * const value);

        friend std::ostream & operator<<(std::ostream &o, const LocalMemory &memory);
};


#endif /* _LOCALMEMORY_H_ */