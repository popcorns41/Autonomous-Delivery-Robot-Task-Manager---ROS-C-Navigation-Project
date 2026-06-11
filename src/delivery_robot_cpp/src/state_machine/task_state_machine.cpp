#include "delivery_robot_cpp/state_machine/task_state_machine.hpp"

namespace delivery_robot_cpp
{
    TaskStateMachine::TaskStateMachine() :
         current_state_(TaskState::IDLE)
    {
    }

    TaskState TaskStateMachine::current_state() const
    {
        return current_state_;
    }

    void TaskStateMachine::receive_task()
    {
        current_state_ = TaskState::TASK_RECEIVED;
    }

    void TaskStateMachine::fail_task()
    {
        current_state_ = TaskState::TASK_FAILED;
    }

    void TaskStateMachine::reset()
    {
        current_state_ = TaskState::IDLE;
    }
}