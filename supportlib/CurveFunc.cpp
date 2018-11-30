//
// Created by ktulhu on 24/11/2018.
//

#include <CurveFunc.h>
#include <iostream>

CurveFunc::CurveFunc(std::shared_ptr<XYData> fd)
    :   xvec{&(fd->x)},   yvec{&(fd->y)},
        size{(int)fd->x.size()}     {
}

CurveFunc::~CurveFunc() {
}

bool CurveFunc::eval(double x, double y) const {
    return y < interpolate3n(x);
}

int CurveFunc::place(double x) const {
    // returns index of first element greater than x
    int count = 0;
    for (int i = 0; i < xvec->size(); ++i) {
        if (x < xvec->at(i)) break;
        count++;
    }
    return count;
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
    for(int k, j = 0; j < 3; j++) {
        product = yvec->at(i[j]);
        for (k = 0; k < 3; k++) {
            if (k == j) continue;
            product *= (x - xvec->at(i[k])) / (xvec->at(i[j]) - xvec->at(i[k]));
        }
        running_sum += product;
    }
    return running_sum;
}

