#include <iostream>
#include "Face.h"
#include "Cube.h"

int main() {
	Cube cube;

	cube.print(std::cout);

	std::cout << "\n";
	std::cout << "Scramble...\n";
	cube.scramble(20);

	cube.solveFaceCenters();

	return 0;
}
