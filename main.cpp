#include <iostream>
#include "Face.h"
#include "Cube.h"

int main() {
	Cube<5> cube;

	cube.print(std::cout);

	std::cout << "\n\n";
	cube.scramble(1000);
	cube.print(std::cout);

	//std::cout << "\n\n";
	//cube.rotateRowTwice(0);
	//cube.print(std::cout);

	return 0;
}