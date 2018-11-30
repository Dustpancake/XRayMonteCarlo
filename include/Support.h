//
// Created by ktulhu on 30/11/2018.
//

#ifndef XRAYMONTECARLO_PRETTYPRINTS_H
#define XRAYMONTECARLO_PRETTYPRINTS_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

namespace pPrint {

	void print(const std::vector<double>& v) {
		std::cout << "Length = " << v.size() << std::endl;
		for(const auto& i : v) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}

namespace WEB {

	void fetch(const std::string& url, const std::string& save_path) {
		// url http://henke.lbl.gov/tmp/xray7615.dat
		std::stringstream ss;
		ss << "curl " << url << " > " << save_path;
		std::system(ss.str().c_str());
	}

}


#endif //XRAYMONTECARLO_PRETTYPRINTS_H
