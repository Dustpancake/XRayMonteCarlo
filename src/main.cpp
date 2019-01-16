#include <iostream>
#include <ctime>
#include <vector>
#include "pipeline/XRaySpectrum.h"
#include "pipeline/AttenuationLengths.h"
#include "pipeline/EHistogram.h"
#include <Plotting.h>

void plot_test() {
	grph::plot_file("../xraydata/e_spectra/test.txt", "test_plot_func.png");

	FileParse fp{"../xraydata/e_spectra/test1.txt"};
	auto data = fp.parse();		// returns shared ptr to XYData

	grph::plot_XY_data(data.get(), "test_data_plot.png");

}

void thickness(double N, double dx, double min, double max, const std::string& at_path, const std::string& xr_path) {
	std::cout << at_path << std::endl;
	std::cout << xr_path << std::endl;
	AttenuationLengths at{at_path};
	XRaySpectrum xr{xr_path};

	EHistogram eh{at, xr};

	std::vector<PhotonData> vec;
	for(double i = min; i < max; i+=dx) {
		eh.set_x(i);
		PhotonData pd = eh.n_probability(N);
		vec.emplace_back(pd);
	}

	std::vector<double> means, thicknesses;
	for(int i = 0; i < vec.size(); ++i) {
		means.emplace_back(vec.at(i).mean);
		thicknesses.emplace_back(vec.at(i).thickness);
	}

	save::photon_struct("first_photon.txt", vec.at(0));
	save::photon_vector("output.txt", vec);

	std::vector<double> errors;
	XYData xydata;
	for (int i = 0; i < vec.size(); ++i) {
		xydata.x.emplace_back(vec.at(i).thickness);
		xydata.y.emplace_back(vec.at(i).mean);
		errors.emplace_back(vec.at(i).std);
	}
	grph::plot_mean_thickness(&xydata, &errors.front(), N, dx, "output.png");
}

void usage() {
	std::cout << "Usage: " << std::endl; //TODO
}

void run_usage() {
	std::cout << "Usage: " << std::endl; //TODO
}

void peak(double N, double dx, double min, double max) {

}

int main(int argc, char** argv) {
	if (argc == 1) {
		usage();
		return 0;
	}
	std::string command{argv[1]};
	std::cout << "command = " << command << std::endl;
	if (command.compare("get") == 0) {
		// fetch resource from URL

	} else if (command.compare("simulate") == 0) {
		if (argc != 8) {
			run_usage();
			return 0;
		}
		std::string param;
		double values[4];
		for (int i = 0; i < 4; ++i) {
			try {
				param = argv[i+2];
				values[i] = std::stod(param);
			} catch (...) {
				run_usage();
				return 0;
			}
		}
		thickness(values[0], values[1], values[2], values[3], argv[6], argv[7]);
	}
    return 0;
}
