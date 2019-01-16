//
// Created by ktulhu on 24/11/2018.
//

#include <FileParse.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

FileParse::~FileParse() {
}

FileParse::FileParse(const std::string& path) {
    // had to change constructor for linapp server
    this->path = path;
    title = "";
    xlabel = "";
    ylabel = "";
}

std::shared_ptr<XYData> FileParse::parse() {
    std::shared_ptr<XYData> pt(new XYData);
    std::ifstream fs;

    std::cout << "Reading file '" << path << "'." << std::endl;

    fs.open(path);
    if (!fs) {
        std::cerr << "[-] Failed to open file.";
        return std::shared_ptr<XYData>(new XYData);
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

    std::cout << "[+] Read " << pt->x.size() << " data point(s)." << std::endl;
    std::cout << "[+] Data @ " << pt.get() << "." << std::endl;
    return pt;
}

void FileParse::to_latex() {
    /*
     * TODO
     * convert the title and labels into the ROOT
     * latex format, which i think uses # instead of \
     */
}

void tofile::write(const std::string &path, const std::string& ss) {
    std::ofstream fs;
    fs.open(path);
    if (fs) {
        fs << ss;
    } else {
        std::cerr << "failed to open file '" << path << "'" << std::endl;
        return;
    }
    fs.close();
}
