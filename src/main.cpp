#include "xorshift.h"
#include <iostream>


int main() {
	for (int i = 0; i<100; i++) {
		std::cout << prng::xorshift128plus() << std::endl;
	}
	return 0;
}