#include <iostream>
#include "Face.h"
#include "Cube.h"

int main() {
	Cube<5> cube;

	cube.print(std::cout);

	std::cout << "\n";
	std::cout << "Starting scramble...";
	cube.scramble();
	std::cout << " done\n\n";

	cube.print(std::cout);

	std::cout << "\n\n";
	//cube.rotateRowTwice(0);
	//cube.print(std::cout);

	return 0;
}
