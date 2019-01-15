//
// Created by ktulhu on 24/11/2018.
//

#ifndef XRAYMONTECARLO_FILEPARSE_H
#define XRAYMONTECARLO_FILEPARSE_H

#include <vector>
#include <memory>
#include <string>

struct XYData{
    std::vector<double> x ;
    std::vector<double> y ;
};

struct FileParse {
    explicit FileParse(const std::string& path) ;
    virtual ~FileParse() ;

    std::shared_ptr<XYData> parse() ;
    std::string path, title, xlabel, ylabel;
private:
    void to_latex() ;
};

namespace tofile {
	void write(const std::string &path, const std::stringstream& ss) ;
}


#endif //XRAYMONTECARLO_FILEPARSE_H
