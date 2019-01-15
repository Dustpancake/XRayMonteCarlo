//
// Created by ktulhu on 2019-01-07.
//

#ifndef XRAYMONTECARLO_ATTENUATIONLENGTHS_H
#define XRAYMONTECARLO_ATTENUATIONLENGTHS_H

#include <string>
#include <FileParse.h>
#include <CurveFunc.h>

class AttenuationLengths {
public:
	AttenuationLengths() = default ;
	virtual ~AttenuationLengths() ;
	explicit AttenuationLengths(const std::string& path) ;
	explicit AttenuationLengths(const AttenuationLengths& at) ;

	double at_energy(double energy) ;
	std::string title ;

private:
	std::shared_ptr<XYData> fdata ;
	double xmax, ymax ;
	std::shared_ptr<CurveFunc> cfunc;
};


#endif //XRAYMONTECARLO_ATTENUATIONLENGTHS_H
