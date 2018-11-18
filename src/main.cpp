#include <PRNG.h>
#include <iostream>

int main() {
	for (int i = 0; i<1000; i++) {
		printf("%0.20f\n", prng::rdouble(0, 1));
	}
	return 0;
}