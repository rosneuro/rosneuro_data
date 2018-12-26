#ifndef ROSNEURO_NEURODATA_HPP
#define ROSNEURO_NEURODATA_HPP

#include <string.h>
#include <string>
#include <vector>

namespace rosneuro {

struct NeuroDataInfo {
	std::string					unit			= "";
	std::string					transducter		= "";
	std::string					prefiltering	= "";
	std::vector<double>			minmax{0.0f, 0.0f};
	std::vector<std::string>	labels;
	int							isint			= 0;
};

template<class T>
class NeuroData {
	public:
		NeuroData(unsigned int ns, unsigned int nch, const std::string name="unknown");
		virtual ~NeuroData(void);

		T* get(void);
		T* get(void) const;
		NeuroDataInfo* get_info(void);
		
		size_t		nchannels(void) const;
		size_t		nsamples(void) const;
		size_t		stride(void) const;
		std::string name(void) const;
		
		void info(void);


	private:
		T*				data_;
		NeuroDataInfo*	info_;
		
		size_t		ns_;
		size_t		nch_;
		size_t		stride_;
		std::string name_;
};



}

#include "../src/NeuroData.cpp"


#endif
