#include "rosneuro_data/NeuroData.hpp"

using namespace rosneuro;

void print_data(const NeuroData<float>* data) {
	for(auto i=0; i<data->size(); i++)
		printf("%f ", data->data()[i]);
	printf("\n");
}


int main(int argc, char** argv) {

	size_t ns	= 5;
	size_t neeg = 2;
	
	NeuroData<float>	eeg(ns, neeg, "EEG");
	NeuroDataInfo *ieeg;
	ieeg = eeg.info();
	
	// Info eeg
	ieeg->unit = "[uV]";
	ieeg->transducter = "Active";
	ieeg->prefiltering = "Notch 50Hz | Highpass: 0.1 Hz";
	ieeg->minmax = {-823000.0, 823000.0};
	ieeg->isint  = 0;
	ieeg->labels = {"Fz", "FC3", "FC1", "FCz", "FC2", "FC4", "C3", "C1", 
					"Cz", "C2", "C4", "CP3", "CP1", "CPz", "CP2", "CP4"};

	
	// Genereting some data
	float eegtmp[eeg.size()];
	
	for(auto i=0; i<eeg.size(); i++)
		eegtmp[i] = i+1;
	memcpy(eeg.data(), eegtmp, eeg.size()*sizeof(float));

	// Dumping
	printf(">>>>>>>>>>>>>Data generated:\n");
	eeg.dump();
	print_data(&eeg);	

	// Test copy assignment
	printf(">>>>>>>>>>>>>Data copied:\n");
	NeuroData<float> eeg2(100, 2, "EEG2");
	eeg2 = eeg;
	eeg2.dump();
	print_data(&eeg2);	

	// Test self_copy
	printf(">>>>>>>>>>>>>Data copied (self_assignement):\n");
	eeg2 = eeg2;
	eeg2.dump();
	print_data(&eeg2);	

	// Test copy constructor
	printf(">>>>>>>>>>>>>Data copied (constructor):\n");
	NeuroData<float> eeg3 {eeg2};
	eeg3.dump();
	print_data(&eeg3);	


	return 0;
}


