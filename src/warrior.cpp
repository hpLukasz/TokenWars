#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "imasteraccess.h"
#include "warrior.h"
#include "appdebug.h"
#include "cmd.h"


Warrior::Warrior(const std::string &wariorId, const WarriorConfig &config) : 
    mId(wariorId), mWarriorConfig(config), mMemory{mWarriorConfig.getMemSize()}, mTokensNo(0)
{
    //set tokens in memory
    int index;
    std::vector<uint32_t> indexVec(mWarriorConfig.getTokensNo());
    int counter = mWarriorConfig.getTokensNo();

    //generate unique seed
    uint32_t randSeed = time(0);
    uint32_t i = 0;
    while(mId[i])
    {
        randSeed += static_cast<uint32_t>(mId[i++]);
    }
    srand(randSeed);

    while(counter)
    {
        // verify to don't repeat the same vector's index
        do {
            index = 1 + rand() % mWarriorConfig.getMemSize();
        } while(std::find(indexVec.begin(), indexVec.end(), index)!=indexVec.end());
        indexVec[counter-1] = index;

        mMemory.setMemory(index, 1);
        counter--;
    }

#ifdef MY_DEBUG
    std::cout << mId << ": memory ids: ";
    for (auto i: indexVec)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
#endif

    mTokensNo = mWarriorConfig.getTokensNo();
}

bool Warrior::isToken(uint32_t memIndex)
{
    uint32_t dummy = 0;
    if (mMemory.getMemory(memIndex, &dummy))
        return dummy == 1;
    else
        return false;
}

void Warrior::clearToken(uint32_t memIndex)
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

bool Warrior::duel(std::shared_ptr<IMasterAccess> master, std::list<std::shared_ptr<IWarriorAccess>> warriors)
{
    uint32_t index;

    for (auto enemy: warriors)
    {
        // skip myself
        if (enemy->getId() == mId) continue;

        index = 0;
        while(enemy->isAlive())
        {
            do {
                // check if myself is still alive
                if (this->isAlive())
                {
                    //scan enemy memory
                    master->addCmd(ICmd(eClearToken, index, mId, enemy->getId() ) );
                }
                else
                {
                    // died myself
                    return false;
                }

            } while((++index < enemy->getMemSize()) && enemy->isAlive());
        }
    }

    return true;
}

// bool Warrior::duel(Warrior &enemy)
// {
//     uint32_t index = 0;
//     while(enemy.isAlive())
//     {
//         do {
//             // check if myself is still alive
//             if (this->isAlive())
//             {
//                 //scan enemy memory
//                 if (enemy.isToken(index))
//                 {
//                     enemy.clearToken(index);
//                     if (!enemy.isAlive())
//                     {
//                         std::cout << std::endl << mId << ": Killed enemy ! (" << enemy.getId() << ")"  << std::endl;
//                         break;
//                     }
//                 }
//             }
//             else
//             {
//                 // died myself
//                 return false;
//             }

//         } while(++index < enemy.getMemSize());
//     }

//     return true;
// }