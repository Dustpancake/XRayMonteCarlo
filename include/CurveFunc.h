//
// Created by ktulhu on 24/11/2018.
//

#ifndef XRAYMONTECARLO_CURVEFUNC_H
#define XRAYMONTECARLO_CURVEFUNC_H

#include "FileParse.h"
#include <vector>

class CurveFunc {
public:
    // using linear interpolation for now

    // makes xvec and yvec point to the vectors in XYData, so
    // do not need to delete the pointers as the XYData still exists
    // - can safely let them run out of scope
    // - XYData however must perish after all instances
    //   to this class are deleted
    CurveFunc();
    explicit CurveFunc(std::shared_ptr<XYData>) ;
    virtual ~CurveFunc() ;

    bool eval(double x, double y) const ;
    double y_val(double x) const ;

private:
    int place(double x) const ;
    double interpolate3n(double x) const ;

    // p(x) returns height
    double px(double x, int i[3]) const ;
    std::vector<double> *xvec, *yvec;
    const int size;
};


#endif //XRAYMONTECARLO_CURVEFUNC_H
