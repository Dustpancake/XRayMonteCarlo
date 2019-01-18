//
// Created by ktulhu on 24/11/2018.
//

#include <CurveFunc.h>
#include <iostream>

CurveFunc::~CurveFunc() {
}

bool CurveFunc::eval(double x, double y) const {
    return y < interpolate3n(x);
}

int CurveFunc::place(double x) const {
    // returns index of first element greater than x
    int low = 0, i, old_i, high = xvec->size();
    double val;
    i = high/2;
    do {
        old_i = i;
        val = xvec->at(i);
        if (x < val) {
            high = i;
            i = high/2;
        } else {
            low = i;
            i = low + (high-low)/2;
        }
    } while(abs(i-old_i) > 1);
    if (old_i > i) i = old_i;
    return i;
}

double CurveFunc::interpolate3n(double x) const {
    // find location of the upper x_i given x
    int i_s[3];
    i_s[1] = place(x);
    // for now, using this as the midpoint, future maybe measure where point is
    i_s[0] = i_s[1] - 1;
    i_s[2] = i_s[1] + 1;
    // ensure not at edges of array, else shift
    if (i_s[0] < 0) {
        for (int j = 0; j < 3; j++) i_s[j] += 1;
    } else if (i_s[2] > size-1) {
        for (int j = 0; j < 3; j++) i_s[j] -= 1;
    }
    // interpolate
    // std::cout << "p(x) = " << px(x, i_s) << std::endl;
    return px(x, i_s);
}

double CurveFunc::px(double x, int i[3]) const {
    // derived from mathematica website on interpolation http://mathworld.wolfram.com/LagrangeInterpolatingPolynomial.html
    double product, running_sum = 0;
    for(int k, j = 0; j < 3; ++j) {
        product = yvec->at(i[j]);
        for (k = 0; k < 3; ++k) {
            if (k == j) continue;
            product *= (x - xvec->at(i[k])) / (xvec->at(i[j]) - xvec->at(i[k]));
        }
        running_sum += product;
    }
    return running_sum;
}

double CurveFunc::y_val(double x) const {
    return interpolate3n(x);
}

CurveFunc::CurveFunc(std::shared_ptr<XYData> fd)
	:   xvec{&(fd->x)},   yvec{&(fd->y)},
			size{(int)fd->x.size()}     {
}


