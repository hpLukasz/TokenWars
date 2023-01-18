#ifndef _IMASTERACCESS_H_
#define _IMASTERACCESS_H_

#include <queue>
#include <mutex>
#include <memory>
#include <cstring>
#include "cmd.h"

class IMasterAccess
{
    protected:
        std::queue<ICmd> mQueue;
    public:
        virtual bool addCmd(const ICmd &cmd) =0;
};

#endif /* _IMASTERACCESS_H_ */