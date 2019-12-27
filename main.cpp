#include <iostream>
#include <fstream>
#include <ctime>
#include "Cube.h"

bool test3x3() {
	for (int pass = 1; pass <= 10000; ++pass) {
		Cube cube(6);
		std::cout << "Pass " << pass << "\n";
		cube.scramble(pass, true);

		// turn on debug output after we reach a pass that needs a closer look.
		//if (pass >= 1) {
		//	cube.setcon(&std::cout);
		//	cube.print(std::cout);
		//}
		bool result = cube.solve3x3();
		if (!result || !cube.isSolved()) {
			std::cout << "Pass " << pass << " FAILED!\n";
			break;
		}
	}

	return 0;
}

void generateCubes()
{
	std::srand((unsigned)std::time(nullptr));
	std::ofstream f("random-cubes-10k.txt");

	for (int pass = 1; pass <= 10000; ++pass) {
		Cube cube(3);
		cube.scramble(1000);
		cube.printKociemba(f);
		cube.printKociemba(std::cout);
	}
	f.close();
}

int main() {
	//test3x3();
	//return 0;

	//generateCubes();
	//return 0;

	for (int pass = 100; pass <= 10000; ++pass) {
		Cube cube(5);
		std::cout << "Pass " << pass << "\n";
		cube.scramble(pass);

		// turn on debug output after we reach a pass that needs a closer look.
		//if (pass >= 1) {
		//	cube.setcon(&std::cout);
		//	cube.print(std::cout);
		//}
		bool result = cube.solveCube();
		//cube.print(std::cout);
		if (!result || (cube.findUnsolvedCenter() != -1)) {
			std::cout << "Pass " << pass << " FAILED!\n";
			break;
		}
	}

	return 0;
}

int test(Cube& cube) {
	// F  = rotateSliceCW(0)
	// F' = rotateSliceCCW(0)
	// B  = rotateSliceCCW(CUBE_SIZE-1)
	// B' = rotateSliceCW(CUBE_SIZE-1)
	// R  = rotateColumnUp(CUBE_SIZE-1)
	// R' = rotateColumnDown(CUBE_SIZE-1)
	// L  = rotateColumnDown(0)
	// L' = rotateColumnUp(0)
	// U  = rotateRowLeft(0)
	// U' = rotateRowRight(0)
	// D  = rotateRowRight(CUBE_SIZE-1)
	// D' = rotateRowLeft(CUBE_SIZE-1)

	cube.rotateCubeUp();
	cube.rotateColumnDown(0);
	cube.rotateCubeLeft();
	cube.rotateColumnDown(0);
	cube.rotateCubeRight();
	cube.rotateColumnDown(0);
	cube.rotateCubeDown();
	cube.rotateColumnDown(0);

	cube.rotateColumnUp(0);
	cube.rotateCubeUp();
	cube.rotateColumnUp(0);
	cube.rotateCubeLeft();
	cube.rotateColumnUp(0);
	cube.rotateCubeRight();
	cube.rotateColumnUp(0);
	cube.rotateCubeDown();
	return 0;

	cube.rotateColumnDown(0);
	cube.rotateCubeSpinCCW();
	cube.rotateColumnDown(0);
	cube.rotateCubeSpinCCW();
	cube.rotateColumnDown(0);
	cube.rotateCubeSpinCCW();
	cube.rotateColumnDown(0);
	cube.rotateCubeSpinCCW();

	cube.rotateCubeSpinCW();
	cube.rotateColumnUp(0);
	cube.rotateCubeSpinCW();
	cube.rotateColumnUp(0);
	cube.rotateCubeSpinCW();
	cube.rotateColumnUp(0);
	cube.rotateCubeSpinCW();
	cube.rotateColumnUp(0);
	return 0;

}