//
// Created by ktulhu on 2019-01-14.
//

#ifndef XRAYMONTECARLO_EHISTOGRAM_H
#define XRAYMONTECARLO_EHISTOGRAM_H

#include "AttenuationLengths.h"
#include "XRaySpectrum.h"
#include <vector>
#include <ostream>

struct PhotonData {
	PhotonData(const std::vector<double> &evec, double t, const std::string &at, const std::string &xr) ;
	std::vector<double> energies ;
	double mean, thickness, std ;
	std::string AtLen_title, XRay_title ;

};

class EHistogram {
public:
	EHistogram() = delete ;
	EHistogram(const AttenuationLengths &at, const XRaySpectrum &xr) ;
	virtual ~EHistogram() ;

	PhotonData n_probability(int n);

	void set_x(double val) ;

	std::vector<double> through ;
	std::vector<double> absorbed ;

private:
	AttenuationLengths at_length ;
	XRaySpectrum xr_spectrum ;
	double x_dist;
};

namespace save {
	void photon_struct(const std::string& path, const PhotonData& pdata);
	void photon_vector(const std::string& path, const std::vector<PhotonData>& pvec);
}

std::ostream& operator<<(std::ostream &out, const PhotonData& pd);



#endif //XRAYMONTECARLO_EHISTOGRAM_H
