#include <iostream>
#include "Face.h"
#include "Cube.h"

int main() {
	Cube cube;

	//cube.printPos(std::cout);
	//cube.setcon(&std::cout);
	//for (int slice = CUBE_SIZE; slice--;) {
	//	cube.rotateSliceTwice(slice);
	//}

	//cube.printPos(std::cout);
	//return 0;

	std::cout << "Scramble...\n";
	cube.scramble(10, true);
	cube.print(std::cout);
	cube.setcon(&std::cout);

	cube.solve3x3();

	//cube.solveFaceCenters();

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

	cube.algoRotateCornerRD();
	cube.algoRotateCornerRD();
	cube.algoRotateCornerRD();
	cube.algoRotateCornerRD();
	cube.algoRotateCornerRD();
	cube.algoRotateCornerRD();
	return 0;

	cube.rotateColumnTwice(0); // L2
	cube.rotateColumnTwice(CUBE_SIZE - 1); // R2
	cube.rotateRowTwice(0); // U2
	cube.rotateRowTwice(CUBE_SIZE - 1); // D2
	cube.rotateSliceTwice(0); // F2
	cube.rotateSliceTwice(CUBE_SIZE - 1); // B2
	return 0;


}