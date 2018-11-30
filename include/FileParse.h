//
// Created by ktulhu on 24/11/2018.
//

#ifndef XRAYMONTECARLO_FILEPARSE_H
#define XRAYMONTECARLO_FILEPARSE_H

#include <vector>
#include <memory>
#include <string>

struct FileData{
    std::vector<double> x;
    std::vector<double> y;
};

struct FileParse {
    explicit FileParse(const std::string& path) ;
    virtual ~FileParse() ;

    std::shared_ptr<FileData> parse() ;
    std::string path, title, xlabel, ylabel;
private:
    void to_latex() ;
};


#endif //XRAYMONTECARLO_FILEPARSE_H
