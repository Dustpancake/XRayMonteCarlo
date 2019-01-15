#include <iostream>
#include <ctime>
#include <vector>
#include "pipeline/XRaySpectrum.h"
#include "pipeline/AttenuationLengths.h"
#include "pipeline/EHistogram.h"
#include <Plotting.h>

#define MAX 1.0
using namespace std;

void plot_test() {
	grph::plot_file("../xraydata/e_spectra/test.txt", "test_plot_func.png");

	FileParse fp{"../xraydata/e_spectra/test1.txt"};
	auto data = fp.parse();		// returns shared ptr to XYData

	grph::plot_XY_data(data.get(), "test_data_plot.png");

}

void thickness() {
	AttenuationLengths at{"../xraydata/atten_lengths/test.txt"};
	XRaySpectrum xr{"../xraydata/e_spectra/test.txt"};

	EHistogram eh{at, xr};

	std::vector<PhotonData> vec;
	for(double i = 1; i < 70; i+=2) {
		eh.set_x(i);
		PhotonData pd = eh.n_probability(1e6);
		vec.emplace_back(pd);
	}

	std::vector<double> means, thicknesses;
	for(int i = 0; i < vec.size(); ++i) {
		std::cout << vec.at(i);
		means.emplace_back(vec.at(i).mean);
		thicknesses.emplace_back(vec.at(i).thickness);
	}

	XYData xy;
	xy.x=thicknesses;
	xy.y=means;
	grph::plot_XY_data(&(xy), "test_relation.png");
}

int main() {
    thickness();
    return 0;
}
