#ifndef ROSNEURO_NEURODATA_CPP
#define ROSNEURO_NEURODATA_CPP


#include "rosneuro_data/NeuroData.hpp"

namespace rosneuro {

template<class T>
NeuroData<T>::NeuroData(unsigned int ns, unsigned int nch, const std::string name) {

	size_t ssize;
	
	this->ns_		= ns;
	this->nch_		= nch;
	this->stride_	= this->nch_ * sizeof(T);
	this->name_		= name;

	// Allocate data memory
	ssize = this->stride_ * this->ns_;	
	this->data_ = ssize ? (T*)malloc(ssize) : nullptr;

	// Allocate info memory
	this->info_ = this->nch_ ? new NeuroDataInfo() : nullptr;

	// Reserve info vectors
	if(this->info_ != nullptr) {
		this->info_->labels.reserve(this->nch_);
		this->info_->minmax.reserve(2);
	}
}

template<class T>
NeuroData<T>::~NeuroData(void) {

	if(this->data_ != nullptr)
		free(this->data_);

	if(this->info_ != nullptr)
		free(this->info_);

}

template<class T>
T* NeuroData<T>::get(void) {
	return this->data_;
}

template<class T>
T* NeuroData<T>::get(void) const {
	return this->data_;
}

template<class T>
NeuroDataInfo* NeuroData<T>::get_info(void) {
	return this->info_;
}

template<class T>
size_t NeuroData<T>::nchannels(void) const {
	return this->nch_;
}

template<class T>
size_t NeuroData<T>::nsamples(void) const {
	return this->ns_;
}

template<class T>
size_t NeuroData<T>::stride(void) const {
	return this->stride_;
}

template<class T>
std::string NeuroData<T>::name(void) const {
	return this->name_;
}

template<class T>
void NeuroData<T>::info(void) {

	printf("[info] '%s' NeuroData:\n", this->name().c_str());
	printf(" |- nsamples:\t\t%zu\n", this->nsamples());
	printf(" |- nchannels:\t\t%zu\n", this->nchannels());
	printf(" |- unit:\t\t%s\n", this->info_->unit.c_str());
	printf(" |- transducter:\t%s\n", this->info_->transducter.c_str());
	printf(" |- prefiltering:\t%s\n", this->info_->prefiltering.c_str());
	printf(" |- min/max:\t\t[%f %f]\n", this->info_->minmax[0], this->info_->minmax[1]);
	printf(" |- isint:\t\t%d\n",	 this->info_->isint);
	printf(" |- labels:\t\t");
	for(auto it = this->info_->labels.begin(); it != this->info_->labels.end(); ++it)
		printf("%s ", (*it).c_str());
	printf("\n");

}


}

#endif
