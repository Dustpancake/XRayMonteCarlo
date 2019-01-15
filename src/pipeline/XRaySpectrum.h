//
// Created by ktulhu on 24/11/2018.
//

#ifndef XRAYMONTECARLO_XRAYSPECTRUM_H
#define XRAYMONTECARLO_XRAYSPECTRUM_H

#include <string>
#include <memory>
#include <FileParse.h>
#include <PRNG.h>
#include <vector>

class XRaySpectrum {
public:
    XRaySpectrum() = default ;
    explicit XRaySpectrum(const std::string& path) ;
    explicit XRaySpectrum(const XRaySpectrum& xr) ;
    virtual ~XRaySpectrum() ;

    void populate_random(int n) ;

    // vector storing all the energies generated
    std::vector<double> photon_energy;
    std::string title;

private:
    std::shared_ptr<XYData> fdata;
    double xmax, ymax;
};


#endif //XRAYMONTECARLO_XRAYSPECTRUM_H
