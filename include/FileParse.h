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
    //TODO remember to use size for a lot of functions down the line
    //you're too tired to do it at the moment
};

struct FileParse {
    explicit FileParse(const std::string& path) noexcept;
    virtual ~FileParse() noexcept;

    std::shared_ptr<FileData> parse() noexcept;
    std::string path, title, xlabel, ylabel;
private:
    void to_latex();
};


#endif //XRAYMONTECARLO_FILEPARSE_H
