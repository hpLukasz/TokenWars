#include <map>
#include <memory>
#include <chrono>
#include <thread>
#include "master.h"
#include "appdebug.h"
#include "cmd.h"

Master::Master() : mContinuesProcessing(false), mLock(mQueueMutex, std::defer_lock)
{
    
}

bool Master::addCmd(const ICmd &cmd)
{
    mLock.lock();
    mQueue.push(cmd);
    mLock.unlock();

    return true;
}

/**
 * Method handling all cmds from Warriors.
 * 
 */
void Master::proccessing(std::list<std::shared_ptr<Warrior>> warriors)
{
    std::map<std::string, std::shared_ptr<Warrior>> warriorMap;

    for (auto w: warriors)
        warriorMap.insert(std::make_pair(w->getId(), w));

    std::cout << std::endl << "W_0:" << std::endl << warriorMap["W_0"]->getMemory() << std::endl;
    std::cout << std::endl << "W_1:" << std::endl << warriorMap["W_1"]->getMemory() << std::endl;

    while (mContinuesProcessing)
    {
        mLock.lock();
        while(! mQueue.empty())
        {
            ICmd cmd = mQueue.front();

    #ifdef MY_DEBUG
            std::cout << "Processng " << cmd << std::endl;
    #endif

            switch(cmd.getType())
            {
                case eClearToken:
                {
                    // check if send is dead
                    if (! warriorMap[cmd.getSenderId()]->isAlive() )
                    {
                        std::cout << "Sender (" << cmd.getSenderId() << ") is dead, cmd ClearToken skipped" << std::endl;
                        break;
                    }

                    if (warriorMap[cmd.getEnemyId()]->isAlive())
                    {
                        warriorMap[cmd.getEnemyId()]->clearToken(cmd.getIndex());
                        if (! warriorMap[cmd.getEnemyId()]->isAlive() )
                        {
                            std::cout << std::endl << ": Killed warrior ! (" << cmd.getEnemyId() << ")"  << std::endl;
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    std::cout << "Unknown cmd id: " << cmd.getType() << std::endl;
                }
            }
            mQueue.pop();
        }
        mLock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}


void Master::startProcessing(std::list<std::shared_ptr<Warrior>> warriors)
{
    mContinuesProcessing = true;
    std::thread t(&Master::proccessing, this, warriors);

    if (t.joinable())
        t.join();
}