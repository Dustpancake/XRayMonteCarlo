//
// Created by ktulhu on 24/11/2018.
//

#include "XRaySpectrum.h"
#include <CurveFunc.h>
#include <iostream>

XRaySpectrum::XRaySpectrum(const std::string& path) {
    FileParse fp{path};
    fdata = fp.parse();
    title = fp.title;

    auto *x = &(fdata->x);
    auto *y = &(fdata->y);
    xmax = x->at(x->size() - 1);
    ymax = y->at(y->size() - 1);
}

XRaySpectrum::~XRaySpectrum() {
}

void XRaySpectrum::populate_random(int n) {
    CurveFunc func{fdata};

    // generate 2 random points and if evaluate under curve
    // append to xvals and yvals vectors

    // will generate n successful points

    std::cout << "Generating " << n << " photon energies." << std::endl;

    double x, y;
    int fails = 0;
    for (int i = 0; i < n;) {
        x = prng::rdouble(0, xmax);
        y = prng::rdouble(0, ymax * 1000);
        //std::cout << x << ", " << y << std::endl;
        if (func.eval(x, y)) {
            photon_energy.emplace_back(x);
            ++i;
        } else {
            //std::cout << "FAIL" << std::endl;
            ++fails;
        }
    }

    std::cout << "Generated data set with " << fails << " rejected points." << std::endl;

}

XRaySpectrum::XRaySpectrum(const XRaySpectrum &xr) {
	fdata = std::make_shared<XYData>(*(xr.fdata));
	title = xr.title;
	xmax = xr.xmax;
	ymax = xr.ymax;
}

