#include <PRNG.h>
#include <TH1F.h>
#include <iostream>
#include <TCanvas.h>
#include <ctime>

#define MAX 1.0
using namespace std;

void rngtest(){
    TH1F* h_Uniform = new TH1F("h_Uniform", "uniform random numbers",  100,  0, MAX);
    std::clock_t start;
/*
	start = std::clock();
	for (int i = 0; i<100000000; i++) {
		double r = prng::rdouble(0, MAX);
		// cout << r << endl;
		h_Uniform->Fill(r);
	}
	std::cout << "time taken = " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
*/

    start = std::clock();
    prng::ncallback(100000000, 0, MAX, [&](double r){ h_Uniform->Fill(r); });
    std::cout << "time taken = " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

    h_Uniform->SetMinimum(0);
    TCanvas canvas;
    h_Uniform->Draw();
    canvas.Print("output.png");
}

void test_fetching(){
    // url http://henke.lbl.gov/tmp/xray7615.dat
    system("curl http://henke.lbl.gov/tmp/xray7615.dat >> ../xraydata/test.txt");
}


int main() {
    test_fetching();
    return 0;
}
