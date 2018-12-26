#include "rosneuro_data/NeuroData.hpp"
#include "rosneuro_data/NeuroDataTools.hpp"
#include "rosneuro_msgs/NeuroDataFloat.h"
#include "rosneuro_msgs/NeuroDataInt32.h"

using namespace rosneuro;

int main(int argc, char** argv) {

	size_t ns	= 32;
	size_t neeg = 16;
	size_t ntri = 1;

	NeuroDataInfo *ieeg, *itri;
	rosneuro_msgs::NeuroDataFloat	mfloat;
	rosneuro_msgs::NeuroDataInt32	mint32;

	NeuroData<float>	eeg(ns, neeg, "EEG");
	NeuroData<int32_t>	tri(ns, ntri, "TRI");

	ieeg = eeg.get_info();
	itri = tri.get_info();

	// Info eeg
	ieeg->unit = "[uV]";
	ieeg->transducter = "Active";
	ieeg->prefiltering = "Notch 50Hz | Highpass: 0.1 Hz";
	ieeg->minmax = {-823000.0, 823000.0};
	ieeg->isint  = 0;
	ieeg->labels = {"Fz", "FC3", "FC1", "FCz", "FC2", "FC4", "C3", "C1", 
					"Cz", "C2", "C4", "CP3", "CP1", "CPz", "CP2", "CP4"};
	
	// Info trigger
	itri->unit = "[V]";
	itri->transducter = "Active";
	itri->prefiltering = "None";
	itri->minmax = {-10.0, 10.0};
	itri->isint  = 1;
	itri->labels = {"Status"};

	eeg.info();
	tri.info();


	// Genereting some data
	size_t nelem_tri = tri.nsamples()*tri.nchannels();
	size_t nelem_eeg = eeg.nsamples()*eeg.nchannels();
	int32_t tritmp[nelem_tri];
	float eegtmp[nelem_eeg];
	for(auto i=0; i<nelem_tri; i++)
		tritmp[i] = i+1;
	memcpy(tri.get(), tritmp, nelem_tri*sizeof(int32_t));
	
	for(auto i=0; i<nelem_eeg; i++)
		eegtmp[i] = i+1;
	memcpy(eeg.get(), eegtmp, nelem_eeg*sizeof(float));
	
	// Convert to message
	NeuroDataTools::ToMessage(eeg, mfloat);
	NeuroDataTools::ToMessage(tri, mint32);

	printf("EEG message data:\n");
	for(auto it = mfloat.array.data.begin(); it != mfloat.array.data.end(); ++it)
		printf("%f ", (*it));
	printf("\n\n");

	printf("TRI message data:\n");
	for(auto it = mint32.array.data.begin(); it != mint32.array.data.end(); ++it)
		printf("%d ", (*it));
	printf("\n");

	return 0;
}
