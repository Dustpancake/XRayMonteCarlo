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
		for(int i = 0; i < v.size(); ++i) {
			std::cout << v.at(i) << " ";
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
		std::cout << "[*] Saved to file '" << save_path << "'." << std::endl;
	}

}

namespace itt {
	template <typename T>
	T max_element(const std::vector<T>& vec) {
		T big = 0;
		for (int i = 0; i < vec.size(); ++i) {
			T val = vec.at(i);
			if (val > big) {
				big = val;
			}
		}
		return big;
	}

	template <typename T>
	T min_element(const std::vector<T>& vec) {
		T small = 1e6;
		for (int i = 0; i < vec.size(); ++i) {
			T val = vec.at(i);
			if (val < small) {
				small = val;
			}
		}
		return small;
	}
}

#endif //XRAYMONTECARLO_PRETTYPRINTS_H
