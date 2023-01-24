#include <map>
#include <memory>
#include <chrono>
#include <future>
#include <iostream>
#include "master.h"
#include "appdebug.h"
#include "cmd.h"

Master::Master(CmdsQueue &cmdsQueue) : mCmds(cmdsQueue), mContinuesProcessing(false), mActive(false)
{
    std::cout << "Master constructor !" << std::endl;
}

Master::~Master()
{
    std::cout << "Master destrucotr !" << std::endl;
}

bool Master::isEndOfGame(std::vector<std::shared_ptr<WarriorAccessImpl>> warriors, std::string& winner)
{
    int counter = 0;
    for (auto w : warriors)
    {
        if (w->isAlive()) {
            winner = w->getId();
            counter++;
        }
    }

    return counter == 1;
}


/**
 * Method handling all cmds from Warriors.
 * 
 */
bool Master::proccessing(std::vector<std::shared_ptr<WarriorAccessImpl>> warriors)
{
    std::string winnerId;
    std::map<std::string, std::shared_ptr<WarriorAccessImpl>> warriorMap;

    for (auto w: warriors)
        warriorMap.insert(std::make_pair(w->getId(), w));

    std::cout << "Master Thread ID: " << std::this_thread::get_id() <<std::endl;
    std::flush(std::cout);

    mContinuesProcessing = true;

    while(mContinuesProcessing) //give time warriors to start researching
    {
        while(mActive && (! mCmds.empty()))
        {
            ICmd cmd = mCmds.getCmd();

            switch(cmd.getType())
            {
                case eClearToken:
                {
                    // check if send is dead
                    if (! warriorMap[cmd.getSenderId()]->isAlive() )
                    {
#ifdef MY_DEBUG
                        std::cout << "Sender (" << cmd.getSenderId() << ") is dead, cmd ClearToken skipped" << std::endl;
                        std::flush(std::cout);
#endif
                        break;
                    }

                    if (warriorMap[cmd.getEnemyId()]->isAlive())
                    {
                        warriorMap[cmd.getEnemyId()]->clearToken(cmd.getIndex());
                        if (! warriorMap[cmd.getEnemyId()]->isAlive() )
                        {
                            std::cout << std::endl << "Master: " << cmd.getSenderId() << " kill warrior " << cmd.getEnemyId() << std::endl;
                            if (isEndOfGame(warriors, std::ref(winnerId)))
                            {
                                mContinuesProcessing = false;
                                mActive = false;
                                std::cout << std::endl << "Master: WINNER IS " << winnerId << " !!!" << std::endl << std::endl;

                            }
                            std::flush(std::cout);

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
        }

        if (mActive && (mCmds.empty()))
        {
            std::cout << "Incorrect state, end task !" << std::endl;
            mContinuesProcessing = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

#ifdef MY_DEBUG 
    std::cout << "END MASTER LOOP" << std::endl << std::endl;
#endif

    return true;
}


bool Master::dummyTask(std::vector<std::shared_ptr<WarriorAccessImpl>> warriors)
{
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return true;
}

