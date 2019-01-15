//
// Created by ktulhu on 2019-01-07.
//

#include "AttenuationLengths.h"

AttenuationLengths::AttenuationLengths(const std::string &path) {
	FileParse fp{path};
	fdata = fp.parse();
	title = fp.title;

	auto *x = &(fdata->x);
	auto *y = &(fdata->y);
	xmax = x->at(x->size() - 1);
	ymax = y->at(y->size() - 1);
	cfunc = std::shared_ptr<CurveFunc>{new CurveFunc(fdata)};
}

double AttenuationLengths::at_energy(double energy) {
	if (energy > xmax || energy < 0) return 0;
	return cfunc->y_val(energy);
}

AttenuationLengths::~AttenuationLengths() {
}

AttenuationLengths::AttenuationLengths(const AttenuationLengths& at) {
	fdata = std::make_shared<XYData>(*(at.fdata));
	title = at.title;
	xmax = at.xmax;
	ymax = at.ymax;
	cfunc = std::make_shared<CurveFunc>(*(at.cfunc));
}

