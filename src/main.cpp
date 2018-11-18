#include <PRNG.h>
#include <TH1F.h>
#include <TFile.h>
#include <TRandom3.h>
#include <iostream>
#include <TCanvas.h>

#define MAX 1.0
using namespace std;

int main() {
	TH1F* h_Uniform = new TH1F("h_Uniform", "uniform random numbers",  100,  0, MAX);
	for (int i = 0; i<100000; i++) {
		double r = prng::rdouble(0, MAX);
		h_Uniform->Fill(r);
	}

	h_Uniform->SetMinimum(0);
	TCanvas canvas;
	h_Uniform->Draw();
	canvas.Print("output.png");
	return 0;
}
