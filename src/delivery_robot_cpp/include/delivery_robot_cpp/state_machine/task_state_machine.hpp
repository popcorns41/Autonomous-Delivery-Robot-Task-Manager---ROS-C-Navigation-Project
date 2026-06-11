#ifndef DELIVERY_ROBOT_CPP_STATE_MACHINE_TASK_STATE_MACHINE_HPP_
#define DELIVERY_ROBOT_CPP_STATE_MACHINE_TASK_STATE_MACHINE_HPP_

#include "delivery_robot_cpp/types/task_state.hpp"

namespace delivery_robot_cpp
{
    class TaskStateMachine
    {
        public:
            TaskStateMachine();

            TaskState current_state() const;

            void receive_task();
            void fail_task();
            void reset();
            
            private:
                TaskState current_state_;
    };
}

#endif