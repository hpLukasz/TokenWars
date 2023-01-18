#include <iostream>
#include <thread>
#include <future>
#include "localmemory.h"
#include "warrior.h"
#include "master.h"

using namespace std;

int main() 
{
    // Warrior warrior1("W_1", WarriorConfig(1000,10));
    // Warrior warrior2("W_2", WarriorConfig(1000,10));
    // cout << "Warrior1:" << endl << warrior1.getMemory() << endl;
    // cout << "Warrior2:" << endl << warrior2.getMemory() << endl;

    // warrior1.duel(warrior2);
    // warrior2.duel(warrior1);

    std::list<std::shared_ptr<Warrior>> warriorList;

    for (int i=0;i<2;i++)
    {
        warriorList.push_back(
           make_shared<Warrior>("W_" + to_string(i), WarriorConfig(1000,10))
        );
    }

    // for (auto w: warriorList)
    //     cout << w->getId() << endl << w->getMemory() << endl;

    Master master;
    master.startProcessing(warriorList);

    cout << "======= END =======" << endl;
    master.stopProcessing();

    return 0;
}