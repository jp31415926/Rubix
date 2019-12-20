#pragma once

#include "Cubelet.h"
#include "Face.h"

//
//            1
//            00 01 02 
//            10 11 12 
//            20 21 22 
// 3          0         4         5
// 00 01 02   00 01 02  00 01 02  00 01 02
// 10 11 12   10 11 12  10 11 12  10 11 12
// 20 21 22   20 21 22  20 21 22  20 21 22
//            2
//            00 01 02 
//            10 11 12 
//            20 21 22 
//
//
//                 1
//                 00 01 02 03 04
//                 10 11 12 13 14
//                 20 21 22 23 24
//                 30 31 32 33 34
//                 40 41 42 43 44
// 3               0               4               5
// 00 01 02 03 04  00 01 02 03 04  00 01 02 03 04  00 01 02 03 04
// 10 11 12 13 14  10 11 12 13 14  10 11 12 13 14	 10 11 12 13 14
// 20 21 22 23 24  20 21 22 23 24  20 21 22 23 24	 20 21 22 23 24
// 30 31 32 33 34  30 31 32 33 34  30 31 32 33 34	 30 31 32 33 34
// 40 41 42 43 44  40 41 42 43 44  40 41 42 43 44	 40 41 42 43 44
//                 2
//                 00 01 02 03 04
//                 10 11 12 13 14
//                 20 21 22 23 24
//                 30 31 32 33 34
//                 40 41 42 43 44
//
//
//                       1
//                       00 01 02 03 04 05 06
//                       10 11 12 13 14 15 16
//                       20 21 22 23 24 25 26
//                       30 31 32 33 34 35 36
//                       40 41 42 43 44 45 46
//                       50 51 52 53 54 55 56
//                       60 61 62 63 64 65 66
//
// 3                     0                     4                     5
// 00 01 02 03 04 05 06  00 01 02 03 04 05 06  00 01 02 03 04 05 06  00 01 02 03 04 05 06
// 10 11 12 13 14 15 16  10 11 12 13 14 15 16  10 11 12 13 14 15 16	 10 11 12 13 14 15 16
// 20 21 22 23 24 25 26  20 21 22 23 24 25 26  20 21 22 23 24 25 26	 20 21 22 23 24 25 26
// 30 31 32 33 34 35 36  30 31 32 33 34 35 36  30 31 32 33 34 35 36	 30 31 32 33 34 35 36
// 40 41 42 43 44 45 46  40 41 42 43 44 45 46  40 41 42 43 44 45 46	 40 41 42 43 44 45 46
// 50 51 52 53 54 55 56  50 51 52 53 54	55 56  50 51 52 53 54 55 56  50 51 52 53 54 55 56
// 60 61 62 63 64 65 66	 60 61 62 63 64 65 66  60 61 62 63 64 65 66  60 61 62 63 64 65 66
//
//                       2
//                       00 01 02 03 04 05 06
//                       10 11 12 13 14 15 16
//                       20 21 22 23 24 25 26
//                       30 31 32 33 34 35 36
//                       40 41 42 43 44 45 46
//                       50 51 52 53 54 55 56
//                       60 61 62 63 64 65 66
//

constexpr auto FRONT = 0;
constexpr auto UP = 1;
constexpr auto DOWN = 2;
constexpr auto LEFT = 3;
constexpr auto RIGHT = 4;
constexpr auto BACK = 5;

class Cube {
public:
	Cube(unsigned size);

	~Cube();

	void setcon(std::ostream* console);

	Face& getFace(unsigned side) const;

	void rotateCubeUp();

	void rotateCubeDown();

	void rotateCubeLeft();

	void rotateCubeRight();

	void rotateCubeSpinCW();

	void rotateCubeSpinCCW();

	void rotateCubeUp2();

	void rotateCubeLeft2();

	void rotateCubeSpin2();

	// rotates specified cube face to the front
	void rotateCubeToFront(int side);

	// rotates specified cube face to the specified face position
	void rotateCubeFaceToPos(int side, int pos);

	// returns face number of face with specified color
	int findCubeByColor(Cubelet::color_t color);

	// rotates cube to place specified face to the front based on face color
	void rotateCubeToFrontByColor(Cubelet::color_t color);

	void rotateColumnUp(int col);

	void rotateColumnDown(int col);

	void rotateColumnTwice(int col);

	void rotateRowLeft(int row);

	void rotateRowRight(int row);

	void rotateRowTwice(int row);

	// rotate slice clockwise (slice=0 is top layer)
	void rotateSliceCW(int slice);

	// rotate slice counter-clockwise (slice=0 is top layer)
	void rotateSliceCCW(int slice);

	// rotate slice twice (slice=0 is top layer)
	void rotateSliceTwice(int slice);

	// rotate the specified face clockwise
	void rotateFaceCW(int side);

	// rotate front slice to the rotation specified
	void restoreFrontRotation(int rot);

	// repeatedly and randomly call various move functions to scramble the cube
	void scramble(int iterations = 200, bool limitTo3x3 = false);

	// Is the cube solved?
	bool isSolved() const;

	// searches for an unsolved center and returns face index
	// returns -1 if none are found
	int findUnsolvedCenter();

	// searches for an unsolved center (excluding the front and the specified position) and returns face index
	// returns -1 if none are found
	int findUnsolvedCenterExcludingPosAndFront(int pos);

	// if the specified face is solved or the specified color, rotate cube until it is not
	// returns true if successful, or false if not
	bool rotateUnsolvedAdjacentToPos(Cubelet::color_t excludeColor, int pos);

	// returns number of unsolved centers
	int countUnsolvedCenters();

	// Assumptions: front face as already been searched for a matching part 1
	// move cubelet(s) to form part 1 of center
	// this part is always center column, but can be many rows (from center to bottom edge, not inclusive)
	// 43-53 cubelets on a 7x7
	void solveFaceCenterPart1();

	void solveFaceCenterPart2();

	void solveFaceCenterPart3();


	void solveFaceCenterPart4();

	// 00 01 02 03 04 05 06
	// 10 11 12 13 14 15 16
	// 20 21 22 23 24 25 26
	// 30 31 32 33 34 35 36
	// 40 41 42 43 44 45 46
	// 50 51 52 53 54 55 56
	// 60 61 62 63 64 65 66

	// center parts for 7x7 example:
	// part 1: 43-53
	// part 2: 44-55
	// part 3: 41-52
	// part 4: 11-25

	// move cubelet(s) to form part 1 of center
	// this part is always 1 column, but can be many rows (from center to edge, not inclusive)
	void solveCurrentFaceCenter();

	// solve the front face center
	void solveFaceCenters();

	// perform algorithms
	// Example: F U' R U
	// U - a 90-degree clockwise rotation of the upper face
	// U' - a 90-degree counterclockwise rotation of the U face
	// U2 - a half turn of the upper face
	// (not implemented) u - a 90-degree clockwise rotation of the two upper faces
	// Fw - the two outer front layers together (deep turn)
	// 3Fw - The three front layers together on a big cube (min 7x7x7)
	// 3Fw2 - 180 degree turn of the three front layers on a big cube
	// (not implemented) 2F - second inner front layer (inner slice)
	// x - rotate the entire cube on R (do an R move without holding the two other layers)
	// y - rotate the entire cube on U
	// z - rotate the entire cube on F
	void performAlgorithm(const std::string& s);

	bool isFrontCrossSolved();

	// Solve the 2st later cross on FRONT layer
	bool solve3x3FirstLayerCross();

	bool isFirstLayerSolved();

	bool solve3x3FirstLayerCorners();

	bool isSecondLayerSolved();

	bool solve3x3SecondLayer();

	void solve3x3LastLayerCross();

	void solve3x3LastLayerCornerOrientation();

	bool areCornersSolved();

	void solve3x3LastLayerCornerPermutation();

	bool solve3x3LastLayerEdgePermutation();

	// This solves any size cube like a 3x3. It assumes all the centers and edges are complete for cubes greater than 3x3.
	bool solve3x3();

	void printRow(std::ostream& s, Face* face, int row) const;

	void printRowPos(std::ostream& s, Face* face, int row) const;

	void print(std::ostream& s) const;

	void print2(std::ostream& s) const;

	void printPos(std::ostream& s) const;

private:
	unsigned CUBE_SIZE;
	unsigned CENTER;
	Face* face[6];
	std::ostream* m_con;
};
