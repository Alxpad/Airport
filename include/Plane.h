#ifndef PLANE_H
#define PLANE_H
#include <iostream>
#include "Tower.h"

namespace tower{ class Tower;
}

namespace planes{       
    class Plane : public std::enable_shared_from_this<Plane>
    { 
        public:
            Plane(std::weak_ptr<tower::Tower>);
            Plane(std::weak_ptr<tower::Tower>, std::string planeID);
            virtual ~Plane();

            void increasePlanesList(std::size_t &);
            virtual void loadCalculus() = 0;
            bool m_planeDetected{false};
            double readLoad();
            bool RequestLanding(std::weak_ptr<tower::Tower> ptr_tower);
            std::string m_planeID{"Default Plane"};
            void consumeFuel();
            void checkFuel();
            bool landed{false};
            double readFuel();
            bool isActive{true};

        protected:
            bool m_flying{true}; // Whenever a plane is approaching, it is currently flying
            void m_fuelAlert();
            std::shared_ptr<tower::Tower> towerAssigned{nullptr};

            double m_timeOfFlight{0};
            unsigned int m_load{0};
            double m_fuel{100}; //En %
            
    };
}
#endif //PLANE_H