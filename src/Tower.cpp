#include "../include/Tower.h"
#include "../include/Models.h"

//TODO:: Landing request
// Using templates here

tower::Tower::Tower()
{
    
}

tower::Tower::~Tower()
{
    std::cout << "Destroying tower" << this->towerID << std::endl;
}

//----------- Long airway--------------------------------

void tower::long_airway::land_aircraft(const int newOcc)
{
    double Occupation{checkOccupation()};
    double newOccupation = Occupation += newOcc;
    if (newOccupation <= m_max_occupation)
    {
        m_occupation = newOccupation;
    }
    else
    {
        std::cout <<"[Tower] Error: Max occupation exceeded." << std::endl;
        return;
    }
}

void tower::long_airway::takeoff()
{
    
}

double tower::long_airway::checkOccupation()
{
    return m_occupation;
}

//------------------------------------------------------
//------------------------------------------------------
//----------- Short airway -----------------------------

void tower::short_airway::land_aircraft(const int newOcc)
{
    double Occupation{checkOccupation()};
    double newOccupation = Occupation += newOcc;
    if (newOccupation <= m_max_occupation)
    {
        m_occupation = newOccupation;
    }
    else
    {
        std::cout <<"[Tower] Error: Max occupation exceeded." << std::endl;
        return;
    }
}

void tower::short_airway::takeoff()
{
    
}

double tower::short_airway::checkOccupation()
{
    return m_occupation;
}

//------------------------------------------------------
//------------------------------------------------------
//----------- Tower ------------------------------------

void tower::Tower::toggleApproachAlarm()
{
    m_alertPlaneApproaching = !m_alertPlaneApproaching;
    std::cout << "[Tower] Plane detected!" <<std::endl;
}

/*void tower::Tower::increaseNumPlanesInSpace()
{
    if(this->m_alertPlaneApproaching == true)
    {
        ++m_numPlanesInSpace;
        this->toggleApproachAlarm();
        std::cout << "[Tower] New plane in space. Alarm off "<< std::endl;
    }
}
*/
void tower::Tower::readList()
{
    std::cout <<"[Tower]Leyendo lista de aviones detectados : " << std::size(this->m_planesNearby) << std::endl;
    auto it_list{this->m_planesNearby.begin()};

    std::cout << "Name                                Fuel                                Weight                     Landed"<< std::endl;
    std::cout << std::endl;  
    if (!(this->m_planesNearby.empty())) 
    {
        for (size_t elem{0} ; elem < std::size(this->m_planesNearby); ++elem)
        {
            std::cout << (*it_list)->m_planeID << "                 " << (*it_list)->readFuel() << "                                " << (*it_list)->readLoad() << "                 " << std::boolalpha << (*it_list)->landed << std::endl;
            ++it_list;
        }
        std::cout << std::endl; 
    }
    else{
        return;
    }
}

bool tower::Tower::solve_landingRequest(const unsigned int &planeCargo)
{
    std::cout << "[Tower] Checking airways..." << std::endl;
    unsigned int planeSize{0};
    if (planeCargo >= 3000)
        {
            planeSize = 2;
        }
        else
        {
            planeSize = 1;
        }
    std::cout << "[Tower:debug] Plane size : " << planeSize << std::endl;

    if (planeSize > 1)
    {
        return this->check_LongWay(planeSize);
    }
    else
    {
        if (this->check_ShortWay(planeSize))
        {
            return this->check_ShortWay(planeSize);
        }
        else
        {
            return this->check_LongWay(planeSize);
        }
    }
}    
    
bool tower::Tower::check_LongWay(const unsigned int &size)
{
    if (this->Airway_L1.checkOccupation() == 2)
    {
        std::cout << "[Tower] Landing permission denied" << std::endl;
        return false;    
    }
    else
    {
        std::cout << "[Tower] Landing permission granted - L1" << std::endl;
        this->Airway_L1.land_aircraft(size);
        return true;
    }
}

bool tower::Tower::check_ShortWay(const unsigned int &size)
{    
    double airway_S1_occupation = this->Airway_S1.checkOccupation();
    double airway_S2_occupation = this->Airway_S2.checkOccupation();

    if (airway_S1_occupation != 1)
    {
        std::cout << "[Tower] Landing permission granted - S1" << std::endl;
        this->Airway_S1.land_aircraft(size);
        return true;
    }

    else if (airway_S2_occupation != 1)
    {
        std::cout << "[Tower] Landing permission granted - S2" << std::endl;
        this->Airway_S2.land_aircraft(size);
        return true;
    }

    else
    {
        std::cout << "[Tower] Landing permission denied" << std::endl;
        return false;    
    }
}

void tower::Tower::fuelConsumption()
{
    for (std::shared_ptr <planes::Plane> elt : m_planesNearby)
    {
        {   std::cout << "[Tower] Checking fuel in " << elt->m_planeID << std::endl;
            elt->consumeFuel();
            elt->checkFuel();
        }
    }
}

//TODO:: try catch here
void tower::Tower::takeOffRequest(std::shared_ptr<planes::Plane> takeoff_plane)
{
    auto it = this->m_planesNearby.begin();
    while (it != this->m_planesNearby.end())
    {
        if (*it == takeoff_plane)
        {
            std::cout << "[Tower:debug] Plane takes off" << std::endl;
            std::cout << "[Tower] " << it->get()->m_planeID << " taking off" << std::endl;
            std::cout << "[Tower] " << it->get()->m_planeID << " erased from list" << std::endl;
            this->m_planesNearby.erase(it);
            break;
        }
        ++it;
    }
}    