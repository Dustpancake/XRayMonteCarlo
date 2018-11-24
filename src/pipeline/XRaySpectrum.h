//
// Created by ktulhu on 24/11/2018.
//

#ifndef XRAYMONTECARLO_XRAYSPECTRUM_H
#define XRAYMONTECARLO_XRAYSPECTRUM_H

#include <string>

class XRaySpectrum {
public:
    XRaySpectrum() = delete;
    XRaySpectrum(std::string path);
    virtual ~XRaySpectrum();

};


#endif //XRAYMONTECARLO_XRAYSPECTRUM_H
