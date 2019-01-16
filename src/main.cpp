#include <iostream>
#include <ctime>
#include <vector>
#include "pipeline/XRaySpectrum.h"
#include "pipeline/AttenuationLengths.h"
#include "pipeline/EHistogram.h"
#include <Plotting.h>
#include <Support.h>

void fetch(const std::string& URL, const std::string& save_path){
	// url http://henke.lbl.gov/tmp/xray7615.dat
	WEB::fetch(URL, save_path);
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
	std::cout << "[*] Finished simulation." << std::endl;
}

void single(double N, double x, const std::string& at_path, const std::string& xr_path) {
	// TODO
}

void plot(const std::string& file, const std::string& path) {
	grph::plot_file(file, path);
	std::cout << "[*] Saved plot as '" << path << "'." << std::endl;
}

void logplot(const std::string& file, const std::string& path) {
	grph::plot_file_log(file, path);
	std::cout << "[*] Saved plot as '" << path << "'." << std::endl;
}

void usage() {
	std::cout << "Usage: " << std::endl; //TODO
}

void run_usage() {
	std::cout << "Usage: " << std::endl; //TODO
}

void fetch_usage() {
	std::cout << "Usage: " << std::endl; //TODO
}

void plot_usage() {
	std::cout << "Usage: " << std::endl; //TODO
}

void logplot_usage() {
	std::cout << "Usage: " << std::endl; //TODO
}

void errorplot_usage() {
	std::cout << "Usage: " << std::endl; //TODO
}

void single_usage() {
	std::cout << "Usage: " << std::endl; //TODO
}

int main(int argc, char** argv) {
// ------------------------------------------------ USAGE
	if (argc == 1) {
		usage();
		return 0;
	}
	std::string command{argv[1]};
	std::cout << "command = " << command << std::endl;

// ------------------------------------------------ FETCH
	if (command.compare("fetch") == 0) {
		// fetch resource from URL
		if (argc != 4) {
			fetch_usage();
			return 0;
		}
		fetch(argv[2], argv[3]);

	}
// ------------------------------------------------ SIMULATION
	else if (command.compare("simulate") == 0) {
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
// ------------------------------------------------ PLOT
	else if (command.compare("plot") == 0) {
		if (argc != 4) {
			plot_usage();
			return 0;
		}
		plot(argv[2], argv[3]);
	}
// ------------------------------------------------ LOGPLOT
	else if (command.compare("logplot") == 0) {
		if (argc != 4) {
			logplot_usage();
			return 0;
		}
		logplot(argv[2], argv[3]);
	}
// ------------------------------------------------ ERRORPLOT	TODO
	else if (command.compare("errorplot") == 0) {
		if (argc != 4) {
			errorplot_usage();
			return 0;
		}
	}
// ------------------------------------------------ CHECKGEN	TODO
	else if (command.compare("checkgen") == 0) {
		if (argc != 1) {
			// TODO
		}
	}
// ------------------------------------------------ SINGLE
	else if (command.compare("single") == 0) {
		if (argc != 6) {
			single_usage();
			return 0;
		}
		std::string param;
		double values[2];
		for (int i = 0; i < 2; ++i) {
			try {
				param = argv[i+2];
				values[i] = std::stod(param);
			} catch (...) {
				run_usage();
				return 0;
			}
		}
		single(values[0], values[1], argv[4], argv[5]);
	}

    return 0;
}
