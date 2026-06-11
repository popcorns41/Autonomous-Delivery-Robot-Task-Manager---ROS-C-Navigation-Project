#ifndef DELIVERY_ROBOT_CPP_TYPES_TASK_STATE_HPP_
#define DELIVERY_ROBOT_CPP_TYPES_TASK_STATE_HPP_

#include <string>

namespace delivery_robot_cpp
{
    enum class TaskState {
        IDLE,
        TASK_RECEIVED,
        TASK_FAILED
    };

    inline std::string to_string(TaskState state)
    {
        switch(state){
            case TaskState::IDLE:
                return "IDLE";
            case TaskState::TASK_RECEIVED:
                return "TASK_RECEIVED";
            case TaskState::TASK_FAILED:
                return "TASK_FAILED";
            default:
                return "UNKNOWN";
        }
    }
}

#endif