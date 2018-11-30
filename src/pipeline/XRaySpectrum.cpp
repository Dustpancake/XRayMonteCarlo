//
// Created by ktulhu on 24/11/2018.
//

#include "XRaySpectrum.h"

XRaySpectrum::XRaySpectrum(const std::string& path) {
    FileParse fp{path};
    fdata = fp.parse();
    title = fp.title;
}

XRaySpectrum::~XRaySpectrum() {
}