#ifndef ROSNEURO_NEURODATA_TOOLS_HPP
#define ROSNEURO_NEURODATA_TOOLS_HPP

#include <ros/ros.h>
#include "rosneuro_data/NeuroData.hpp"
#include "rosneuro_msgs/NeuroDataFloat.h"
#include "rosneuro_msgs/NeuroDataInt32.h"
#include "rosneuro_msgs/NeuroDataInfo.h"
#include "rosneuro_msgs/NeuroFrame.h"

namespace rosneuro {
    class NeuroDataTools {
        public:
            static bool ConfigureNeuroMessage(const NeuroFrame& frame, rosneuro_msgs::NeuroFrame& msg);
            static bool ConfigureNeuroFrame(const rosneuro_msgs::NeuroFrame& msg, NeuroFrame& frame);

            static bool FromNeuroInfo(const NeuroDataInfo& info, rosneuro_msgs::NeuroDataInfo& msg);
            static bool ToNeuroInfo(const rosneuro_msgs::NeuroDataInfo& msg, NeuroDataInfo& info);

            static bool FromNeuroFrame(const NeuroFrame& frame, rosneuro_msgs::NeuroFrame& msg);
            static bool ToNeuroFrame(const rosneuro_msgs::NeuroFrame& msg, NeuroFrame& frame);

            static bool FromNeuroData(const NeuroData<float>& data, rosneuro_msgs::NeuroDataFloat& msg);
            static bool FromNeuroData(const NeuroData<int32_t>& data, rosneuro_msgs::NeuroDataInt32& msg);

            static bool ToNeuroData(const rosneuro_msgs::NeuroDataFloat& msg, NeuroData<float>& data);
            static bool ToNeuroData(const rosneuro_msgs::NeuroDataInt32& msg, NeuroData<int32_t>& data);

        private:
            NeuroDataTools(void) {};
    };
}

#endif
