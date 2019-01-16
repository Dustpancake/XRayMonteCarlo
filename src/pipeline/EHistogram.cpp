//
// Created by ktulhu on 2019-01-14.
//

#include "EHistogram.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <PRNG.h>
#include <numeric>
#include <FileParse.h>

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

		if (prng::rdouble(0, 1) < x) {
			absorbed.emplace_back(energy);
			++count;
		} else {
			// photon made it through
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

	energies = evec;

	// describe data
	mean = std::accumulate(evec.begin(), evec.end(), 0.0) / evec.size();
	if (isnan(mean)) {
		mean = 0;
		std::cout << energies.size() << std::endl;
	}
	// error - standard deviation
	std = std::inner_product(evec.begin(), evec.end(), evec.begin(), 0.0);
	std = std::sqrt((std / evec.size()) - (mean * mean));
	if (isnan(std)) std = 0;
}

std::ostream& operator<<(std::ostream &out, const PhotonData& pd) {
	out << "PhotonData @ " << &pd << "::\tmean = " << pd.mean << "\tstd = " << pd.std << std::endl;
	return out;
}

void save::photon_struct(const std::string& path, const PhotonData &pdata) {
	using namespace std;
	cout << "Saving PhotonData object as '" << path << "'." << std::endl;
	stringstream ss;

	// save titles of graphs
	ss << pdata.AtLen_title << "\n" << pdata.XRay_title << "\n";
	// save descriptors
	ss << "mean = " << pdata.mean << ", std = " << pdata.std << ", x = " << pdata.thickness << "\n";
	// save distribution
	for (int i = 0; i < pdata.energies.size(); ++i) {
		ss << pdata.energies.at(i) << ",\n";
	}
	tofile::write(path, ss.str());
}

void save::photon_vector(const std::string &path, const std::vector<PhotonData> &pvec) {
	using namespace std;
	cout << "Saving PhotonData vector as '" << path << "'." << std::endl;
	stringstream ss;

	// save titles
	ss << pvec.at(0).AtLen_title << "\n" << pvec.at(0).XRay_title << "\n";

	// 'x, mean, std' for each PhotonData struct
	for (int i = 0; i < pvec.size(); ++i) {
		ss << pvec.at(i).thickness << ", " << pvec.at(i).mean << ", " << pvec.at(i).std << "\n";
	}
	tofile::write(path, ss.str());
}
