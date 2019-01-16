//
// Created by ktulhu on 24/11/2018.
//

#ifndef XRAYMONTECARLO_PLOTTING_H
#define XRAYMONTECARLO_PLOTTING_H

#include <string>
#include <memory>
#include "FileParse.h"

namespace grph {
    void plot_file(const std::string &path, const std::string &save_path);
    void plot_file_log(const std::string &path, const std::string &save_path);

    void plot_XY_data(XYData *fd, const std::string &save_path);

    void plot_XY_data(XYData *fd, const std::string &title,
					  const std::string &save_path);

    void plot_XY_data(XYData *fd, const std::string &title,
					  const std::string &xlabel,
					  const std::string &ylabel,
					  const std::string &save_path);

    void plot_histogram(const std::vector<double>& v, const std::string& save_path, double minimum, double maximum, double bins);

    void plot_mean_thickness(XYData *fd, double* std, double N, double dx, const std::string& save_path);

};

#endif //XRAYMONTECARLO_PLOTTING_H
