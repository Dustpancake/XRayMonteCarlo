#include <iostream>
#include <ctime>
#include <vector>

// custom lib
#include <Plotting.h>
#include <Support.h>
#include "pipeline/XRaySpectrum.h"

#define MAX 1.0
using namespace std;

/*
void rngtest(){
    TH1F* h_Uniform = new TH1F("h_Uniform", "uniform random numbers",  100,  0, MAX);
    std::clock_t start;

	start = std::clock();
	for (int i = 0; i<100000000; i++) {
		double r = supportlib::rdouble(0, MAX);
		// cout << r << endl;
		h_Uniform->Fill(r);
	}
	std::cout << "time taken = " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;


    start = std::clock();
    supportlib::ncallback(100000000, 0, MAX, [&](double r){ h_Uniform->Fill(r); });
    std::cout << "time taken = " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    h_Uniform->SetMinimum(0);
    TCanvas canvas;
    h_Uniform->Draw();
    canvas.Print("output.png");
}
*/


void test_fetching(){
	// url http://henke.lbl.gov/tmp/xray7615.dat
	WEB::fetch("http://henke.lbl.gov/tmp/xray6654.dat", "../xraydata/e_spectra/test.txt");
}

/*

    double* x = &(pt->x)[0];
    double* y = &(pt->y)[0];

    TGraph *grph = new TGraph(501, x, y);

    TCanvas c;
    grph->Draw();
    c.Print("xray.png");

*/


/*
 * need comment out private in CurveFunc.h for this to work
#define N_MAX 100000
void interpolation_test() {
    FileParse *fp = new FileParse("../xraydata/test1.txt");
    auto pt = fp->parse();
    delete fp;

    CurveFunc cf{pt};

    double x[N_MAX], y[N_MAX];
    double x_val = 0;
    double inc = (10000 - 10) / (double) N_MAX;

    for (int i = 0; i < N_MAX; i++) {
        x[i] = x_val;
        y[i] = cf.interpolate3n(x_val);
        x_val += inc;
    }
    TGraph *grph = new TGraph(N_MAX, x, y);
    TCanvas c;
    grph->Draw();
    c.Print("itp_test.png");
}
*/

void plot_test() {

	grph::plot_file("../xraydata/e_spectra/test.txt", "test_plot_func.png");

	FileParse fp{"../xraydata/e_spectra/test1.txt"};
	auto data = fp.parse();		// returns shared ptr to XYData

	grph::plot_XY_data(data.get(), "test_data_plot.png");

}

void test_XRaySpectrum() {
	XRaySpectrum xray{"../xraydata/e_spectra/test.txt"};
	xray.populate_random(1e6);
	grph::plot_histogram(xray.photon_energy, "generation_test.png");
}

int main() {
	test_XRaySpectrum();
	return 0;
}