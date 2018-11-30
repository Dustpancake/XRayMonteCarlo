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
    XRaySpectrum() = delete ;
    explicit XRaySpectrum(const std::string& path) ;
    virtual ~XRaySpectrum() ;

    void populate_random(int n) ;

//private:
    std::shared_ptr<XYData> fdata;
    std::vector<double> photon_energy;
    std::string title;
    double xmax, ymax;
};


#endif //XRAYMONTECARLO_XRAYSPECTRUM_H
