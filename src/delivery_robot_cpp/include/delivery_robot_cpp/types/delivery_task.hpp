#ifndef DELIVERY_ROBOT_CPP_TYPES_DELIVERY_TASK_HPP_
#define DELIVERY_ROBOT_CPP_TYPES_DELIVERY_TASK_HPP_

#include <string>

namespace delivery_robot_cpp
{
    struct DeliveryTask{
        std::string pickup_location;
        std::string dropoff_location;
    };
}

#endif