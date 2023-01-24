#ifndef _IMASTERACCESS_H_
#define _IMASTERACCESS_H_

#include "cmd.h"

class IMasterAccess
{
    public:
        virtual bool addCmd(ICmd &cmd) =0;
        virtual bool addCmd(ICmd &&cmd) =0;
};

#endif /* _IMASTERACCESS_H_ */