#include "../include/Plane.h"
#include "../include/Tower.h"
planes::Plane::Plane(std::weak_ptr<tower::Tower> ptr_tower)
{
    this->towerAssigned = ptr_tower.lock();
    std::cout << "[Plane]: Plane created wo/ID" << std::endl;
}

planes::Plane::Plane(std::weak_ptr<tower::Tower> ptr_tower, std::string planeID) :  m_planeID(planeID)
{
    this->towerAssigned = ptr_tower.lock();
    towerAssigned.get()->toggleApproachAlarm();
    std::cout << "[Plane]: Plane created w/ID" << std::endl;   
}

planes::Plane::~Plane()
{
    
    //std::cout << "[PassengerPlane]: Plane destroyed " <<std::endl;
    std::cout << "[Plane]: Plane "<< this->m_planeID <<" destroyed " << std::endl;
}

double planes::Plane::readLoad()
{
    return this->m_load;
}

bool planes::Plane::RequestLanding(std::weak_ptr<tower::Tower> ptr_tower)
{
    if (ptr_tower.lock()->solve_landingRequest(this->m_load))
    {
        std::cout << "[Plane] Landing plane " << this->m_planeID << std::endl;
        this->landed = true;
        return true;
    }
    else{
        return false;
    }
}

void planes::Plane::consumeFuel()
{
    if (this->landed == false)
    {
        unsigned int load = this->m_load;
        this->m_fuel -= load*0.01;
        if (this->m_fuel < 0){this->m_fuel = 0;};
        std::cout << "[Plane] Fuel level in " << this->m_planeID << " : " << this->m_fuel << std::endl;
    }
}       

void planes::Plane::checkFuel()
{
    if(this->m_fuel <= 30 && this->landed == false)
    {
        std::cout << "[Plane] Fuel alert in : " << this->m_planeID << std::endl;
        std::cout << "[Plane:debug] Sending request to tower assigned: " << this->towerAssigned->towerID << std::endl;
        if (!(this->RequestLanding(towerAssigned)))
        {
            std::cout << "[Plane] Plane ID - " << this->m_planeID << "- low on fuel" << std::endl;
            std::cout << "[Plane] Plane ID - " << this->m_planeID <<" - leaving airspace" << std::endl;
            auto it = towerAssigned->m_planesNearby.begin();
            while (it != towerAssigned->m_planesNearby.end()) 
            {
                if (*it == shared_from_this()) {  
                    // Eliminar el avión de la lista
                    std::cout << "[Plane]: Plane " << it->get()->m_planeID << " erased from list " <<std::endl;
                    towerAssigned->m_planesNearby.erase(it);
                    break;
                } 
                ++it;
                
            }
            std::cout << "[Plane:debug] List exploration end" <<std::endl;
        }
    }
    else if (this->m_fuel < 100 && this->landed == true)
    {
        this->m_fuel+=25;
        std::cout << "Refueling " << this->m_planeID << " plane : " << this->m_fuel << "%" << std::endl;
    }

    else if (this->m_fuel >= 100 && this->landed == true)
    {
        this->m_fuel = 100;
        std::cout << "[Plane] Plane "<< this->m_planeID <<" refueled" << std::endl;
        std::cout << "[Plane] Plane "<< this->m_planeID <<" requesting takeoff." << std::endl;
        auto sharedPlane = shared_from_this();
        this->towerAssigned->takeOffRequest(sharedPlane);
    }
    std::cout << "[Plane:debug] checkFuel() end" <<std::endl;

}

double planes::Plane::readFuel()
{
    return m_fuel;
}