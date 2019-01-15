//
// Created by ktulhu on 2019-01-14.
//

#include "EHistogram.h"
#include <cmath>
#include <iostream>
#include <PRNG.h>
#include <numeric>

EHistogram::EHistogram(const AttenuationLengths &at, const XRaySpectrum &xr) {
	at_length = at;
	xr_spectrum = xr;
	x_dist = 0.5;

}

EHistogram::~EHistogram() {

}

PhotonData EHistogram::n_probability(int n) {
	using namespace std;
	cout << "Simulating " << n << " absorption probabilities:\n[*] x = " << x_dist << " mm." << endl;
	xr_spectrum.photon_energy.clear();
	through.clear();
	absorbed.clear();
	xr_spectrum.populate_random(n);

	double energy, lambda, x, count = 0;
	for (int i = 0; i < xr_spectrum.photon_energy.size(); ++i) {
		energy = xr_spectrum.photon_energy.at(i);
		lambda = at_length.at_energy(energy);

		// convert mm to microns by dividing factor 1000
		x = (x_dist * -1000.0) / lambda;
		x = 1 - exp(x);
		// cout << "DEBUG:\tenergy = " << energy << ",\tlambda = " << lambda << "\tprob = " << x << endl;

		if (prng::rdouble(0, 1) < x) {
			absorbed.emplace_back(energy);
			++count;
		} else {
			// cout << "[+] photon made it through." << endl;
			through.emplace_back(energy);
			++count;
		}
	}
	cout << "[*] Finished - counted " << count << " photons through material." << endl;
	return PhotonData(through, x_dist, at_length.title, xr_spectrum.title);
}

void EHistogram::set_x(double val) {
	x_dist = val;
}

PhotonData::PhotonData(const std::vector<double> &evec, double t, const std::string &at, const std::string &xr) {
	AtLen_title = at;
	XRay_title = xr;
	thickness = t;

	// describe data
	mean = std::accumulate(evec.begin(), evec.end(), 0.0) / evec.size();
	if (isnan(mean)) mean = 0;
	// error or standard deviation
	std = std::inner_product(evec.begin(), evec.end(), evec.begin(), 0.0);
	std = std::sqrt((std / evec.size()) - (mean * mean));
	if (isnan(std)) std = 0;
}

std::ostream& operator<<(std::ostream &out, const PhotonData& pd) {
	out << "PhotonData @ " << &pd << "::\tmean = " << pd.mean << "\tstd = " << pd.std << std::endl;
	return out;
}
