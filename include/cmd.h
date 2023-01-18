#ifndef _CMD_H_
#define _CMD_H_

#include <cstdint>
#include <string>

enum CmdType { eIsToken, eClearToken };

struct ICmd
{
    protected:
        CmdType mType;
        uint32_t mIndex;
        uint32_t mResult;
        std::string mSenderId;
        std::string mEnemyId;
    
    public:
        ICmd(CmdType type, uint32_t index, std::string senderId, std::string enemyId);
        CmdType getType() { return mType; }
        uint32_t getIndex() { return mIndex; }
        uint32_t getResult() { return mResult; }
        std::string & getSenderId() { return mSenderId; }
        std::string & getEnemyId() { return mEnemyId; }

        friend std::ostream & operator<<(std::ostream &out, ICmd &cmd);
};


#endif /* _CMD_H_ */