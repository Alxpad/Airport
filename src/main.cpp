#include <iostream>
#include <array>
#include <functional>
#include <atomic>

#include "../include/Tower.h"
#include "../include/Plane.h"
#include "../include/Models.h"
/*      OBJETIVOS DE LA PRÁCTICA:

        - Polimorfismo
        - Smart Pointers
        - STL : Maps / Vector
        - Lambda

*/
std::atomic<bool> timer_running{true};

void planeGenerator(std::weak_ptr<tower::Tower> CtrlTower)
{
    if (CtrlTower.lock()->m_planesNearby.size() < 2)
    {
        std::cout << "[Main] Generating default plane" << std::endl;
        auto Passengers_0 = std::make_shared<planes::PassengerPlane>(CtrlTower);
        Passengers_0->addPlaneNearby(CtrlTower, Passengers_0->m_planeID);
    }
}

void timer_start(std::function<void(void)> func, unsigned int interval)
{
  std::thread([func, interval]()
  { 
    while (true)
    { 
        if (timer_running.load()){
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
            func();
            std::this_thread::sleep_until(x);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Chequeo frecuente mientras está en pausa
        }
    }
  }).detach();
}

void fuel_consumption(std::shared_ptr<tower::Tower> ctlTower)
{
    ctlTower->fuelConsumption();    
}


int main()
{
    auto tower1 = std::make_shared<tower::Tower>();
    std::weak_ptr<tower::Tower> weak_ptr_tower (tower1);

   // auto Passengers_1 = std::make_shared<planes::PassengerPlane>(tower1, "Cessna 340");
    //Passengers_1->addPlaneNearby(weak_ptr_tower, Passengers_1->m_planeID);
    
   // auto Passengers_2 = std::make_shared<planes::PassengerPlane>(tower1, "Antonov");
    //Passengers_2->addPlaneNearby(weak_ptr_tower, Passengers_1->m_planeID);
   
    timer_start([tower1]() { 

            tower1->fuelConsumption();  
            planeGenerator(tower1);
    }, 5000);

    while(true)
    {
        //timer_running.store(false);
        tower1->readList();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // Chequeo frecuente mientras está en pausa
        //timer_running.store(true);


    }
    if (tower1->m_planesNearby.empty())
    {
        std::cout << "[Main:debug] Generating..." << std::endl;
        planeGenerator(tower1);
    }

    return 0;
}