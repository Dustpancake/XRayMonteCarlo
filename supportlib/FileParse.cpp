//
// Created by ktulhu on 24/11/2018.
//

#include <FileParse.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

FileParse::~FileParse() noexcept {
}

FileParse::FileParse(const std::string& path) noexcept
        :   path{path},
            title{""},
            xlabel{""},
            ylabel{""} {
}

std::shared_ptr<FileData> FileParse::parse() noexcept {
    std::shared_ptr<FileData> pt(new FileData);
    std::ifstream fs;
    fs.open(path);
    if (!fs) {
        std::cerr << "Failed to open file.";
        return std::shared_ptr<FileData>(new FileData);
    }

    {   // scoping cus lots of local variables that can be lost after
        // member assignment
        std::string line = "";
        std::getline(fs, line);
        title = boost::algorithm::trim_copy(line);
        std::getline(fs, line);
        std::vector<std::string> ret;
        boost::algorithm::split(ret, line, boost::is_any_of(","));
        xlabel = boost::algorithm::trim_copy(ret.at(0));
        ylabel = boost::algorithm::trim_copy(ret.at(1));
    }

    double valx, valy;
    while(fs >> valx, fs >> valy) {
        pt->x.push_back(valx);
        pt->y.push_back(valy);
    }
    return pt;
}

void FileParse::to_latex() {
    /*
     * TODO
     * convert the title and labels into the ROOT
     * latex format, which i think uses # instead of \
     */
}


