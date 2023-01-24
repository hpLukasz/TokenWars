#include "cmd.h"
#include <ostream>

ICmd::ICmd(CmdType type, uint32_t index, std::string senderId, std::string enemyId) :
    mType(type), mIndex(index), mSenderId(senderId), mEnemyId(enemyId)
{

}

std::ostream & operator<<(std::ostream &out, ICmd &cmd)
{
    out << "CMD [T: " << cmd.mType << ", I:" << cmd.mIndex
        << ", S_id:" << cmd.mSenderId << ", E_id:" << cmd.mEnemyId
        << "]";

    return out;
}