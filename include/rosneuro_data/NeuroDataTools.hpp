#ifndef ROSNEURO_NEURODATA_TOOLS_HPP
#define ROSNEURO_NEURODATA_TOOLS_HPP

#include <ros/ros.h>
#include "rosneuro_data/NeuroData.hpp"
#include "rosneuro_msgs/NeuroDataFloat.h"
#include "rosneuro_msgs/NeuroDataInt32.h"
#include "rosneuro_msgs/NeuroDataInfo.h"

namespace rosneuro {

class NeuroDataTools {

	public:

		static bool ConfigureMessage(const NeuroDataInfo& data, rosneuro_msgs::NeuroDataInfo& msg);
		static bool ConfigureData(const rosneuro_msgs::NeuroDataInfo& msg, NeuroDataInfo& data);

		static bool ToMessage(const NeuroData<float>& data, rosneuro_msgs::NeuroDataFloat& msg);
		static bool ToMessage(const NeuroData<int32_t>& data, rosneuro_msgs::NeuroDataInt32& msg);

		static void ConfigureDataLayout(size_t ns, size_t nch, std_msgs::MultiArrayLayout& layout);

	private:
		NeuroDataTools(void) {};

};

}

#endif
