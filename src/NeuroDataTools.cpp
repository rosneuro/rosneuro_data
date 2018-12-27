#ifndef ROSNEURO_NEURODATA_TOOLS_CPP
#define ROSNEURO_NEURODATA_TOOLS_CPP

#include "rosneuro_data/NeuroDataTools.hpp"

namespace rosneuro {

bool NeuroDataTools::ConfigureMessage(const NeuroDataInfo* data, rosneuro_msgs::NeuroDataInfo& msg) {

	if(data == nullptr)
		return false;

	msg.unit			= data->unit;
	msg.transducter		= data->transducter;
	msg.prefiltering	= data->prefiltering;
	msg.minmax			= data->minmax;
	msg.labels			= data->labels;
	msg.isint			= data->isint;

	return true;
}

bool NeuroDataTools::ConfigureData(const rosneuro_msgs::NeuroDataInfo& msg, NeuroDataInfo* data) {

	if(data == nullptr)
		return false;
	
	data->unit			= msg.unit;
	data->transducter	= msg.transducter;
	data->prefiltering	= msg.prefiltering;
	data->minmax			= msg.minmax;
	data->labels			= msg.labels;
	data->isint			= msg.isint;

	return true;
}

bool NeuroDataTools::ToMessage(const NeuroData<float>& data, rosneuro_msgs::NeuroDataFloat& msg) {

	size_t ns, nch;
	float* array;

	ns    = data.nsamples();
	nch   = data.nchannels(); 
	array = data.data();
	
	NeuroDataTools::ConfigureDataLayout(ns, nch, msg.array.layout);
	msg.array.data.clear();

	msg.array.data.assign(array, array + (ns*nch));

	return true;
}

bool NeuroDataTools::ToMessage(const NeuroData<int32_t>& data, rosneuro_msgs::NeuroDataInt32& msg) {
	size_t ns, nch;
	int32_t* array;

	ns    = data.nsamples();
	nch   = data.nchannels(); 
	array = data.data();
	
	NeuroDataTools::ConfigureDataLayout(ns, nch, msg.array.layout);
	msg.array.data.clear();

	msg.array.data.assign(array, array + (ns*nch));

	return true;
}

void NeuroDataTools::ConfigureDataLayout(size_t ns, size_t nch, std_msgs::MultiArrayLayout& layout) {


	layout.dim.clear();

	// Define dimension for samples and channels
	layout.dim.push_back(std_msgs::MultiArrayDimension());
	layout.dim.push_back(std_msgs::MultiArrayDimension());

	layout.data_offset = 0;

	layout.dim[0].size = nch;
	layout.dim[0].stride = ns*nch;
	layout.dim[0].label = "channels";
	
	layout.dim[1].size = ns;
	layout.dim[1].stride = ns;
	layout.dim[1].label = "samples";
}

}

#endif
