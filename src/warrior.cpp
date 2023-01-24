#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <future>
#include <chrono>
#include "imasteraccess.h"
#include "warrior.h"
#include "appdebug.h"
#include "cmd.h"


Warrior::Warrior(const WarriorConfig& config, CmdsQueue& cmdsQueue) :
    WarriorAccessImpl(config.getId(), config.getMemSize(), config.getTokensNo()),
    mCmds(cmdsQueue), 
    mWarriorConfig(config)
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
            index = rand() % mWarriorConfig.getMemSize();
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

Warrior::~Warrior()
{
    std::cout << "Warrior " << mId << " destructor !" << std::endl;
}


// return true if finished scanning other warriors, false if own counter was set to 0
bool Warrior::duel(Master & master, std::vector<WarriorConfig> configs)
{
    uint32_t index;

    std::cout << "Warrior [" << mId << "] Thread ID: " << std::this_thread::get_id() <<std::endl;
    std::flush(std::cout);

    for (auto config: configs)
    {
        // skip myself
        if (config.getId() == mId) continue;

        index = 0;

        while(index < config.getMemSize()) {
            //scan enemy memory
            mCmds.addCmd(ICmd(eClearToken, index, mId, config.getId() ) );
            index++;

            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    }

    return true;
}

bool Warrior::dummyTask(std::vector<std::shared_ptr<WarriorAccessImpl>> warriors)
{
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return true;
}
