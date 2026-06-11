#include <chrono>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class TaskManagerNode : public rclcpp::Node
{
    public:
        TaskManagerNode() : Node("task_manager_node")
        {
            RCLCPP_INFO(this->get_logger(), "Task Manager Node has been started.");

            timer_ = this->create_wall_timer(
                1s,
                // Bind the timer callback function to the timer
                std::bind(&TaskManagerNode::timer_callback, this)
            );
        }

        private:
            void timer_callback()
            {
                RCLCPP_INFO(this->get_logger(), "Timer callback triggered.");
            }

            // Timer to periodically execute the timer_callback function
            rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TaskManagerNode>());
    rclcpp::shutdown();
    return 0;
}