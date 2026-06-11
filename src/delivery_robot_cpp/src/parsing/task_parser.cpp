#include "delivery_robot_cpp/parsing/task_parser.hpp"
#include <optional>

namespace delivery_robot_cpp
{

std::optional<DeliveryTask> parse_delivery_task(const std::string & task_string)
{
  const auto delimiter_position = task_string.find(':');

  if (delimiter_position == std::string::npos) {
    return std::nullopt;
  }

  const std::string pickup = task_string.substr(0, delimiter_position);
  const std::string dropoff = task_string.substr(delimiter_position + 1);

  if (pickup.empty() || dropoff.empty()) {
    return std::nullopt;
  }

  return DeliveryTask{
    pickup,
    dropoff
  };
}

}  // namespace delivery_robot_cpp