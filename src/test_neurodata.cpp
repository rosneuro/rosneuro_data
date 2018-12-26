#include "rosneuro_data/NeuroData.hpp"

using namespace rosneuro;

int main(int argc, char** argv) {

	size_t ns	= 32;
	size_t neeg = 16;
	size_t nexg = 3;
	size_t ntri = 1;

	NeuroDataInfo *ieeg, *iexg, *itri;

	NeuroData<float>	eeg(ns, neeg, "EEG");
	NeuroData<float>	exg(ns, nexg, "EXG");
	NeuroData<int32_t>	tri("TRI");

	tri.reserve(ns, ntri);

	ieeg = eeg.info();
	iexg = exg.info();
	itri = tri.info();

	// Info eeg
	ieeg->unit = "[uV]";
	ieeg->transducter = "Active";
	ieeg->prefiltering = "Notch 50Hz | Highpass: 0.1 Hz";
	ieeg->minmax = {-823000.0, 823000.0};
	ieeg->isint  = 0;
	ieeg->labels = {"Fz", "FC3", "FC1", "FCz", "FC2", "FC4", "C3", "C1", 
					"Cz", "C2", "C4", "CP3", "CP1", "CPz", "CP2", "CP4"};
	
	// Info exg
	iexg->unit = "[mV]";
	iexg->transducter = "Active";
	iexg->prefiltering = "None";
	iexg->minmax = {-823000.0, 823000.0};
	iexg->isint  = 0;
	iexg->labels = {"EXG1", "EXG2", "EXG3"};
	
	// Info trigger
	itri->unit = "[V]";
	itri->transducter = "Active";
	itri->prefiltering = "None";
	itri->minmax = {-10.0, 10.0};
	itri->isint  = 1;
	itri->labels = {"Status", "ciao"};

	eeg.dump();
	exg.dump();
	tri.dump();

	return 0;
}
