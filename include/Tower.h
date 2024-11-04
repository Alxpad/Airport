#ifndef TOWER_H
#define TOWER_H

#include <memory>
#include <iostream>
#include <list>
#include "Plane.h"
#include <thread>
#include <chrono>
#include <memory>

namespace planes {class Plane; class PassengerPlane;}

namespace tower{
    class long_airway
    {
        public:
            long_airway() = default;
            ~long_airway() = default;
            void land_aircraft(const int);
            void takeoff();
            double checkOccupation();

        private:
            double m_occupation{0};
            const double m_max_occupation{2};
    };

    class short_airway
    {
        public:
            short_airway() = default;
            ~short_airway() = default;
            void land_aircraft(const int);
            void takeoff();
            double checkOccupation();

        private:
            double m_occupation{0};
            const double m_max_occupation{1};
            
    };
    
    class Tower
    {
        public:
            Tower();
            virtual ~Tower();
            friend class planes::Plane;
            void toggleApproachAlarm();
            //std::size_t m_numPlanesInSpace{0};
            std::list<std::shared_ptr<planes::Plane>> m_planesNearby;
            void readList();
            bool solve_landingRequest(const unsigned int &);
            void fuelConsumption();
            long_airway Airway_L1;
            long_airway Airway_S1;
            short_airway Airway_S2;
            bool check_LongWay(const unsigned int &);
            bool check_ShortWay(const unsigned int &);
            void takeOffRequest(std::shared_ptr<planes::Plane> takeoff_plane);
            std::string towerID{"DefaultTower_ID"};

        private:
            //int numPlanes{};
            bool m_alertPlaneApproaching;
            //void radarScan(planes::Plane);
            //void increaseNumPlanesInSpace();
            
    };
}
#endif //TOWER_H