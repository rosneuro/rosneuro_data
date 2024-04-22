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

    template<class T>
    NeuroData<T>::NeuroData(const std::string name) {
        this->name_		= name;
        this->data_		= nullptr;
    }

    template<class T>
    NeuroData<T>::NeuroData(unsigned int ns, unsigned int nch, const std::string name) {
        this->name_			  = name;
        this->reserve(ns, nch);
    }

    template<class T>
    NeuroData<T>::~NeuroData(void) {
        this->destroy();
    }

    template<class T>
    NeuroData<T>::NeuroData(const NeuroData& data) {
        this->name_ = data.name();
        this->reserve(data.nsamples(), data.nchannels());
        std::copy(data.data(), data.data() + data.nsamples()*data.nchannels(), this->data_);
        this->info_ = data.getinfo();
    }

    template<class T>
    NeuroData<T>& NeuroData<T>::operator=(const NeuroData& data) {
        T* p = new T[data.nsamples()*data.nchannels()];
        std::copy(data.data(), data.data() + data.nsamples()*data.nchannels(), p);

        if(this->data_ != nullptr)
            free(this->data_);

        this->name_ = data.name();
        this->reserve(data.nsamples(), data.nchannels());
        this->info_ = data.getinfo();
        this->data_ = p;

        return *this;
    }

    template<class T>
    void NeuroData<T>::destroy(void) {
        if(this->data_ != nullptr)
            free(this->data_);
    }

    template<class T>
    void NeuroData<T>::reserve(unsigned int ns, unsigned int nch) {
        this->info_.nsamples  = ns;
        this->info_.nchannels = nch;
        this->info_.stride	  = this->info_.nchannels * sizeof(T);

        size_t ssize = this->info_.stride * this->info_.nsamples;
        this->data_ = ssize ? (T*)malloc(ssize) : nullptr;

        this->info_.labels.reserve(this->info_.nchannels);
        this->info_.minmax.reserve(2);
    }

    template<class T>
    size_t NeuroData<T>::size(void) const {
        return (this->info_.nchannels*this->info_.nsamples);
    }

    template<class T>
    T* NeuroData<T>::data(void) {
        return this->data_;
    }

    template<class T>
    const T* NeuroData<T>::data(void) const {
        return this->data_;
    }

    template<class T>
    NeuroDataInfo* NeuroData<T>::info(void) {
        return &(this->info_);
    }

    template<class T>
    const NeuroDataInfo* NeuroData<T>::info(void) const {
        return &(this->info_);
    }

    template<class T>
    NeuroDataInfo NeuroData<T>::getinfo(void) const {
        return this->info_;
    }

    template<class T>
    size_t NeuroData<T>::nchannels(void) const {
        return this->info_.nchannels;
    }

    template<class T>
    size_t NeuroData<T>::nsamples(void) const {
        return this->info_.nsamples;
    }

    template<class T>
    size_t NeuroData<T>::stride(void) const {
        return this->info_.stride;
    }

    template<class T>
    std::string NeuroData<T>::name(void) const {
        return this->name_;
    }

    template<class T>
    void NeuroData<T>::dump(void) {
        printf("[info] '%s' NeuroData:\n",	this->name().c_str());
        printf(" |- nsamples:\t\t%zu\n",	this->nsamples());
        printf(" |- nchannels:\t\t%zu\n",	this->nchannels());
        printf(" |- unit:\t\t%s\n",			this->info_.unit.c_str());
        printf(" |- transducter:\t%s\n",	this->info_.transducter.c_str());
        printf(" |- prefiltering:\t%s\n",	this->info_.prefiltering.c_str());
        printf(" |- min/max:\t\t[%f %f]\n", this->info_.minmax[0], this->info_.minmax[1]);
        printf(" |- labels:\t\t");
        for(auto it = this->info_.labels.begin(); it != this->info_.labels.end(); ++it)
            printf("%s ", (*it).c_str());
        printf("\n");
    }
}

#endif
