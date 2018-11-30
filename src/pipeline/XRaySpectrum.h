//
// Created by ktulhu on 24/11/2018.
//

#ifndef XRAYMONTECARLO_XRAYSPECTRUM_H
#define XRAYMONTECARLO_XRAYSPECTRUM_H

#include <string>
#include <memory>
#include <FileParse.h>
#include <PRNG.h>

class XRaySpectrum {
public:
    XRaySpectrum() = delete;
    explicit XRaySpectrum(const std::string& path) noexcept;
    virtual ~XRaySpectrum();

private:
    std::shared_ptr<FileData> fdata;
    std::string title;
};


#endif //XRAYMONTECARLO_XRAYSPECTRUM_H
