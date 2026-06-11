#ifndef DELIVERY_ROBOT_CPP_PARSING_TASK_PARSER_HPP_
#define DELIVERY_ROBOT_CPP_PARSING_TASK_PARSER_HPP_

#include <optional>
#include <string>

#include "delivery_robot_cpp/types/delivery_task.hpp"

namespace delivery_robot_cpp
{
    std::optional<DeliveryTask> parse_delivery_task(const std::string & task_string);
}

#endif