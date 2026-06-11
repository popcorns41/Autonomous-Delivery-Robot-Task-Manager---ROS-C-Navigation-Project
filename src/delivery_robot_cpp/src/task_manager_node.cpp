#include <chrono>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include "delivery_robot_cpp/parsing/task_parser.hpp"
#include "delivery_robot_cpp/state_machine/task_state_machine.hpp"
#include "delivery_robot_cpp/types/task_state.hpp"

using namespace std::chrono_literals;

namespace delivery_robot_cpp
{

class TaskManagerNode : public rclcpp::Node
{
public:
  TaskManagerNode()
  : Node("task_manager_node")
  {
    RCLCPP_INFO(this->get_logger(), "Task Manager Node started.");
    log_current_state();

    task_subscriber_ = this->create_subscription<std_msgs::msg::String>(
      "/delivery/task_request",
      10,
      std::bind(&TaskManagerNode::task_request_callback, this, std::placeholders::_1)
    );

    timer_ = this->create_wall_timer(
      2s,
      std::bind(&TaskManagerNode::timer_callback, this)
    );
  }

private:
  void task_request_callback(const std_msgs::msg::String::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Raw task request received: '%s'", msg->data.c_str());

    const auto parsed_task = parse_delivery_task(msg->data);

    if (!parsed_task.has_value()) {
      RCLCPP_ERROR(this->get_logger(), "Invalid task format. Expected format: PICKUP:DROPOFF");
      state_machine_.fail_task();
      log_current_state();
      return;
    }

    current_task_ = parsed_task.value();

    RCLCPP_INFO(this->get_logger(), "Received delivery task.");
    RCLCPP_INFO(this->get_logger(), "Pickup: %s", current_task_.pickup_location.c_str());
    RCLCPP_INFO(this->get_logger(), "Dropoff: %s", current_task_.dropoff_location.c_str());

    state_machine_.receive_task();
    log_current_state();
  }

  void timer_callback()
  {
    RCLCPP_INFO(
      this->get_logger(),
      "Task manager alive. Current state: %s",
      to_string(state_machine_.current_state()).c_str()
    );
  }

  void log_current_state()
  {
    RCLCPP_INFO(
      this->get_logger(),
      "Current state: %s",
      to_string(state_machine_.current_state()).c_str()
    );
  }

  DeliveryTask current_task_;
  TaskStateMachine state_machine_;

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr task_subscriber_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace delivery_robot_cpp

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<delivery_robot_cpp::TaskManagerNode>();
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}