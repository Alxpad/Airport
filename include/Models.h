#ifndef MODELS_H
#define MODELS_H

#include "Plane.h"
#include "Tower.h"
#include <random>
#include <chrono>

namespace tower{
    class Tower;
}

namespace planes{

class PassengerPlane : public planes::Plane
{
    public:
        PassengerPlane();
        PassengerPlane(std::weak_ptr<tower::Tower>);
        PassengerPlane(std::weak_ptr<tower::Tower>, std::string);
        void addPlaneNearby(std::weak_ptr<tower::Tower> ctl_tower, std::string planeID);
        virtual ~PassengerPlane();
        virtual void loadCalculus() override;
        unsigned int passengers{0};
        bool landed{false};
    };
}
#endif //MODELS_H