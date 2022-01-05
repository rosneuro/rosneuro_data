#ifndef ROSNEURO_NEURODATA_HPP
#define ROSNEURO_NEURODATA_HPP

#include <string.h>
#include <string>
#include <vector>

namespace rosneuro {

struct NeuroDataInfo {
	size_t						nsamples		= 0;
	size_t						nchannels		= 0;
	size_t						stride			= 0;
	std::string					unit			= "";
	std::string					transducter		= "";
	std::string					prefiltering	= "";
	unsigned int				isint			= 0;
	std::vector<double>			minmax{0.0f, 0.0f};
	std::vector<std::string>	labels;
};



template<class T>
class NeuroData {
	public:
		NeuroData(const std::string name="unknown");
		NeuroData(unsigned int ns, unsigned int nch, const std::string name="unknown");
		virtual ~NeuroData(void);

		NeuroData(const NeuroData& data);
		NeuroData& operator=(const NeuroData& data);

		T* data(void);
		const T* data(void) const;
		NeuroDataInfo* info(void);
		const NeuroDataInfo* info(void) const;
		NeuroDataInfo getinfo(void) const;

		void reserve(unsigned int ns, unsigned int nch);
	
		size_t		size(void) const;
		size_t		nchannels(void) const;
		size_t		nsamples(void) const;
		size_t		stride(void) const;
		std::string name(void) const;
		
		void dump(void);

	private:
		void destroy(void);

	private:
		T*				data_;
		NeuroDataInfo	info_;
		std::string		name_;
};

struct NeuroFrame   {

	unsigned int		sr;
	NeuroData<float>	eeg;
	NeuroData<float>	exg;
	NeuroData<int32_t>	tri;

	NeuroFrame() : eeg("EEG"), exg("EXG"), tri("TRI"), sr(0) {} 
};

}

#include "../src/NeuroData.cpp"


#endif
