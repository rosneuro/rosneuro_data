#ifndef ROSNEURO_NEURODATA_TOOLS_CPP
#define ROSNEURO_NEURODATA_TOOLS_CPP

#include "rosneuro_data/NeuroDataTools.hpp"

namespace rosneuro {


bool NeuroDataTools::ConfigureNeuroMessage(const NeuroFrame& frame, rosneuro_msgs::NeuroFrame& msg) {

	// TODO Header configuration

	msg.sr = frame.sr;
	FromNeuroInfo(*frame.eeg.info(), msg.eeg.info);
	FromNeuroInfo(*frame.exg.info(), msg.exg.info);
	FromNeuroInfo(*frame.tri.info(), msg.tri.info);

	return true;
}

bool NeuroDataTools::ConfigureNeuroFrame(const rosneuro_msgs::NeuroFrame& msg, NeuroFrame& frame) {

	frame.sr = msg.sr;
	ToNeuroInfo(msg.eeg.info, *frame.eeg.info());
	ToNeuroInfo(msg.exg.info, *frame.exg.info());
	ToNeuroInfo(msg.tri.info, *frame.tri.info());

	return true;
}

bool NeuroDataTools::FromNeuroInfo(const NeuroDataInfo& info, rosneuro_msgs::NeuroDataInfo& msg) {

	msg.nsamples		= info.nsamples;
	msg.nchannels		= info.nchannels;
	msg.stride			= info.stride;
	msg.unit			= info.unit;
	msg.transducter		= info.transducter;
	msg.prefiltering	= info.prefiltering;
	msg.isint			= info.isint;
	msg.minmax			= info.minmax;
	msg.labels			= info.labels;

	return true;
}

bool NeuroDataTools::ToNeuroInfo(const rosneuro_msgs::NeuroDataInfo& msg, NeuroDataInfo& info) {

	info.nsamples		= msg.nsamples;
	info.nchannels		= msg.nchannels;
	info.stride			= msg.stride;
	info.unit			= msg.unit;
	info.transducter	= msg.transducter;
	info.prefiltering	= msg.prefiltering;
	info.isint			= msg.isint;
	info.minmax			= msg.minmax;
	info.labels			= msg.labels;

	return true;
}

bool NeuroDataTools::FromNeuroFrame(const NeuroFrame& frame, rosneuro_msgs::NeuroFrame& msg) {

	// Cleaning data message
	FromNeuroData(frame.eeg, msg.eeg);
	FromNeuroData(frame.exg, msg.exg);
	FromNeuroData(frame.tri, msg.tri);



	return true;
}

bool NeuroDataTools::ToNeuroFrame(const rosneuro_msgs::NeuroFrame& msg, NeuroFrame& frame) {

	ToNeuroData(msg.eeg, frame.eeg);
	ToNeuroData(msg.exg, frame.exg);
	ToNeuroData(msg.tri, frame.tri);

	return true;
}

bool NeuroDataTools::FromNeuroData(const NeuroData<float>& data, rosneuro_msgs::NeuroDataFloat& msg) {
	
	// Clear message data
	msg.data.clear();

	// Assign new data to message
	msg.data.assign(data.data(), data.data() + data.size());

	return true;
}

bool NeuroDataTools::FromNeuroData(const NeuroData<int32_t>& data, rosneuro_msgs::NeuroDataInt32& msg) {
	
	// Clear message data
	msg.data.clear();

	// Assign new data to message
	msg.data.assign(data.data(), data.data() + data.size());

	return true;
}

bool NeuroDataTools::ToNeuroData(const rosneuro_msgs::NeuroDataFloat& msg, NeuroData<float>& data) {


	float* arr = data.data();
	std::copy(msg.data.begin(), msg.data.end(), arr);

	return true;
}

bool NeuroDataTools::ToNeuroData(const rosneuro_msgs::NeuroDataInt32& msg, NeuroData<int32_t>& data) {

	int32_t* arr = data.data();
	std::copy(msg.data.begin(), msg.data.end(), arr);

	return true;
}


}
#endif
