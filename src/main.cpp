#include <iostream>
#include <ctime>
#include <vector>

// custom lib
#include <Plotting.h>

#define MAX 1.0
using namespace std;

void plot_test() {
	grph::plot_file("../xraydata/e_spectra/test.txt", "test_plot_func.png");

	FileParse fp{"../xraydata/e_spectra/test1.txt"};
	auto data = fp.parse();		// returns shared ptr to FileData

	grph::plot_data(data.get(), "test_data_plot.png");

}

int main() {
    plot_test();
    return 0;
}
