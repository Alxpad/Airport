#include "../include/Tower.h"
#include "../include/Models.h"

planes::PassengerPlane::PassengerPlane(std::weak_ptr<tower::Tower> ctl_tower) : planes::Plane(ctl_tower)
{
    this->loadCalculus();
    std::cout << "[PassengerPlane]: Plane created " <<std::endl;
}

planes::PassengerPlane::PassengerPlane(std::weak_ptr<tower::Tower> ctl_tower, std::string planeID) : planes::Plane(ctl_tower, planeID)
{
    this->loadCalculus();
    std::cout << "[PassengerPlane]: Plane created " << std::endl;
}

void planes::PassengerPlane::addPlaneNearby(std::weak_ptr<tower::Tower> ctl_tower, std::string planeID)
{
    auto newPlane = shared_from_this(); 
    auto lock_tower = ctl_tower.lock();
    lock_tower -> m_planesNearby.push_back(shared_from_this());   
}

planes::PassengerPlane::~PassengerPlane()
{
    std::cout << "[PassengerPlane]: Plane "<< this->m_planeID <<" destroyed " <<std::endl;
}

void planes::PassengerPlane::loadCalculus()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);
    unsigned int maxPassengers = 100;
    unsigned int initNum = generator() % maxPassengers + 30;
    int average_weight = 80;
    this->m_load = average_weight * initNum;
}

