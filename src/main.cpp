#include <iostream>
#include <thread>
#include <future>
#include "localmemory.h"
#include "warrior.h"
#include "master.h"
#include "cmdsqueue.h"
#include "threadpool.h"

using namespace std;

mutex m;

void dummyTask()
{
    lock_guard<mutex> lg(m);
    std::cout << "Task start [ID: " << std::this_thread::get_id() << "]" <<std::endl;
    std::this_thread::sleep_for(chrono::milliseconds(100));
    std::cout << "Task stop [ID: " << std::this_thread::get_id() << "]" <<std::endl;
}

int main() 
{
    /*
    CmdsQueue cmdQueue;
    Master master(cmdQueue);
    std::vector<WarriorConfig> configs;
    std::vector<std::shared_ptr<WarriorAccessImpl>> warriors;

    configs.push_back(WarriorConfig(1000,30,"W_1"));
    configs.push_back(WarriorConfig(1000,30,"W_2"));
    configs.push_back(WarriorConfig(1000,30,"W_3"));
    configs.push_back(WarriorConfig(1000,30,"W_4"));

    shared_ptr<Warrior> warrior1 = make_shared<Warrior>(configs[0], cmdQueue);
    shared_ptr<Warrior> warrior2 = make_shared<Warrior>(configs[1], cmdQueue);
    shared_ptr<Warrior> warrior3 = make_shared<Warrior>(configs[2], cmdQueue);
    shared_ptr<Warrior> warrior4 = make_shared<Warrior>(configs[3], cmdQueue);
    warriors.push_back(warrior1);
    warriors.push_back(warrior2);
    warriors.push_back(warrior3);
    warriors.push_back(warrior4);


    std::cout << "Main Thread ID: " << std::this_thread::get_id() <<std::endl;

    auto masterResult = async(&Master::proccessing, &master, warriors);

    auto warriorRes_1 = async(&Warrior::duel, warrior1, ref(master), configs);
    auto warriorRes_2 = async(&Warrior::duel, warrior2, ref(master), configs);
    auto warriorRes_3 = async(&Warrior::duel, warrior3, ref(master), configs);
    auto warriorRes_4 = async(&Warrior::duel, warrior4, ref(master), configs);

    // Wait first for fill the cmd's queue
    auto r1 = warriorRes_1.get();
    auto r2 = warriorRes_2.get();
    auto r3 = warriorRes_3.get();
    auto r4 = warriorRes_4.get();

    master.setActive();

    auto r5 = masterResult.get();
    
    // std::this_thread::sleep_for(chrono::seconds(2));
*/
    ThreadPool thPool;

    for (uint32_t i=0; i<10; i++)
    {
        thPool.submit(dummyTask);
    }

    std::this_thread::sleep_for(chrono::seconds(5));

    thPool.stopTasks();
    cout << "======= END GAME =======" << endl;

    return 0;
}