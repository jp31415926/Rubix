#pragma once

#include <algorithm> // std::swap
#include <cstdlib>
#include <ctime>
#include "Face.h"

// Notice that vertical rotation to and from the back face (face 5) requires a flip
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

constexpr auto FRONT  = 0;
constexpr auto TOP    = 1;
constexpr auto BOTTOM = 2;
constexpr auto LEFT   = 3;
constexpr auto RIGHT  = 4;
constexpr auto BACK   = 5;

class Cube {
public:
	Cube() {
		if ((CUBE_SIZE & 1) == 0) {
			std::cerr << "cube dimension must be odd\n";
			throw std::exception("cube dimension must be odd");
		}
		m_con = 0;

		//std::srand((unsigned)std::time(nullptr));
		for (int i = 6; i--;) {
			Face* f = new Face;
			f->initColor(i+1);
			face[i] = f;
		}
		face[FRONT]->initColor('W');
		face[TOP]->initColor('B');
		face[BOTTOM]->initColor('G');
		face[LEFT]->initColor('O');
		face[RIGHT]->initColor('R');
		face[BACK]->initColor('Y');
	}

	~Cube() {
		for (int i = 6; i--;) {
			delete face[i];
		}
	}

	void setcon(std::ostream* console) {
		m_con = console;
	}

	void rotateCubeUp() {
		// BACK = TOP (for example) means moving from TOP to BACK
		// BACK <- TOP or BOTTOM (and vice versa) require a rotateTwice (flip)
		Face* front = face[FRONT];
		face[FRONT] = face[BOTTOM];
		face[BOTTOM] = face[BACK];
		face[BACK] = face[TOP];
		face[TOP] = front;
		face[LEFT]->rotateCCW();
		face[RIGHT]->rotateCW();

		face[BOTTOM]->rotateTwice();
		face[BACK]->rotateTwice();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeDown() {
		// BACK = TOP (for example) means moving from TOP to BACK
		// BACK <- TOP or BOTTOM (and vice versa) require a rotateTwice (flip)
		Face* front = face[FRONT];
		face[FRONT] = face[TOP];
		face[TOP] = face[BACK];
		face[BACK] = face[BOTTOM];
		face[BOTTOM] = front;
		face[LEFT]->rotateCW();
		face[RIGHT]->rotateCCW();

		face[TOP]->rotateTwice();
		face[BACK]->rotateTwice();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeLeft() {
		Face* front = face[FRONT];
		face[FRONT] = face[RIGHT];
		face[RIGHT] = face[BACK];
		face[BACK] = face[LEFT];
		face[LEFT] = front;
		face[TOP]->rotateCW();
		face[BOTTOM]->rotateCCW();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeRight() {
		Face* front = face[FRONT];
		face[FRONT] = face[LEFT];
		face[LEFT] = face[BACK];
		face[BACK] = face[RIGHT];
		face[RIGHT] = front;
		face[TOP]->rotateCCW();
		face[BOTTOM]->rotateCW();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeSpinCW() {
		Face* top = face[TOP];
		face[TOP] = face[LEFT];
		face[LEFT] = face[BOTTOM];
		face[BOTTOM] = face[RIGHT];
		face[RIGHT] = top;

		face[TOP]->rotateCW();
		face[BOTTOM]->rotateCW();
		face[LEFT]->rotateCW();
		face[RIGHT]->rotateCW();
		face[FRONT]->rotateCW();
		face[BACK]->rotateCCW();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeSpinCCW() {
		Face* top = face[TOP];
		face[TOP] = face[RIGHT];
		face[RIGHT] = face[BOTTOM];
		face[BOTTOM] = face[LEFT];
		face[LEFT] = top;

		face[TOP]->rotateCCW();
		face[BOTTOM]->rotateCCW();
		face[LEFT]->rotateCCW();
		face[RIGHT]->rotateCCW();
		face[FRONT]->rotateCCW();
		face[BACK]->rotateCW();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeUp2() {
		// FIXME: optimize
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		rotateCubeUp();
		rotateCubeUp();
	}

	void rotateCubeLeft2() {
		// FIXME: optimize
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		rotateCubeLeft();
		rotateCubeLeft();
	}

	void rotateCubeSpin2() {
		// FIXME: optimize
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		rotateCubeSpinCW();
		rotateCubeSpinCW();
	}

	// rotates specified cube face to the front
	void rotateCubeToFront(int side) {
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << side << ")\n";
		switch (side) {
		default:
		case FRONT:
			// no rotation needed
			break;
		case LEFT:
			rotateCubeRight();
			break;
		case RIGHT:
			rotateCubeLeft();
			break;
		case TOP:
			rotateCubeDown();
			break;
		case BOTTOM:
			rotateCubeUp();
			break;
		case BACK:
			rotateCubeLeft2();
			break;
		}
	}

	// rotates specified cube face to the specified face position
	void rotateCubeFaceToPos(int side, int pos) {
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << side << ", " << pos << ")\n";
		if (side == pos) {
			return;
		}

		rotateCubeToFront(side);

		switch (pos) {
		default:
		case FRONT:
			// no rotation needed
			break;
		case LEFT:
			rotateCubeLeft();
			break;
		case RIGHT:
			rotateCubeRight();
			break;
		case TOP:
			rotateCubeUp();
			break;
		case BOTTOM:
			rotateCubeDown();
			break;
		case BACK:
			rotateCubeLeft2();
			break;
		}
	}

	// returns face number of face with specified color
	int findCubeByColor(Cubelet::color_t color) {
		for (int f = 0; f < 6; ++f) {
			if (face[f]->faceColor() == color) {
				return f;
			}
		}
		return -1;
	}

	// rotates cube to place specified face to the front based on face color
	void rotateCubeToFrontByColor(Cubelet::color_t color) {
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << color << ")\n";
		rotateCubeToFront(findCubeByColor(color));
	}

	void rotateColumnUp(int col) {
		for (int i = CUBE_SIZE; i--;) {
			Cubelet::rotate4(
				face[FRONT]->cface[i][col],
				face[TOP]->cface[i][col],
				//face[BACK]->cface[i][col],
				face[BACK]->cface[CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - col],
				face[BOTTOM]->cface[i][col]);
		}
		if (col == 0) {
			face[LEFT]->rotateCCW();
		}
		else if (col == CUBE_SIZE - 1) {
			face[RIGHT]->rotateCW();
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << col << ")\n";
		if (m_con) print(*m_con);
	}

	void rotateColumnDown(int col) {
		for (int i = CUBE_SIZE; i--;) {
			Cubelet::rotate4(
				face[FRONT]->cface[i][col],
				face[BOTTOM]->cface[i][col],
				//face[BACK]->cface[i][col],
				face[BACK]->cface[CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - col],
				face[TOP]->cface[i][col]);
		}
		if (col == 0) {
			face[LEFT]->rotateCW();
		}
		else if (col == CUBE_SIZE - 1) {
			face[RIGHT]->rotateCCW();
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << col << ")\n";
		if (m_con) print(*m_con);
	}

	void rotateColumnTwice(int col) {
		for (int i = CUBE_SIZE; i--;) {
			std::swap(
				face[FRONT]->cface[i][col],
				face[BACK]->cface[i][col]);
			std::swap(
				face[TOP]->cface[i][col],
				face[BOTTOM]->cface[i][col]);
		}
		if (col == 0) {
			face[LEFT]->rotateTwice();
		}
		else if (col == CUBE_SIZE - 1) {
			face[RIGHT]->rotateTwice();
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << col << ")\n";
		if (m_con) print(*m_con);
	}

	void rotateRowLeft(int row) {
		for (int i = CUBE_SIZE; i--;) {
			Cubelet::rotate4(
				face[FRONT]->cface[row][i],
				face[LEFT]->cface[row][i],
				face[BACK]->cface[row][i],
				face[RIGHT]->cface[row][i]);
		}
		if (row == 0) {
			face[TOP]->rotateCW();
		}
		else if (row == CUBE_SIZE - 1) {
			face[BOTTOM]->rotateCCW();
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << row << ")\n";
		if (m_con) print(*m_con);
	}

	void rotateRowRight(int row) {
		for (int i = CUBE_SIZE; i--;) {
			Cubelet::rotate4(
				face[FRONT]->cface[row][i],
				face[RIGHT]->cface[row][i],
				face[BACK]->cface[row][i],
				face[LEFT]->cface[row][i]);
		}
		if (row == 0) {
			face[TOP]->rotateCCW();
		}
		else if (row == CUBE_SIZE - 1) {
			face[BOTTOM]->rotateCW();
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << row << ")\n";
		if (m_con) print(*m_con);
	}

	void rotateRowTwice(int row) {
		for (int i = CUBE_SIZE; i--;) {
			std::swap(
				face[FRONT]->cface[row][i],
				face[BACK]->cface[row][i]);
			std::swap(
				face[RIGHT]->cface[row][i],
				face[LEFT]->cface[row][i]);
		}
		if (row == 0) {
			face[TOP]->rotateTwice();
		}
		else if (row == CUBE_SIZE - 1) {
			face[BOTTOM]->rotateTwice();
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << row << ")\n";
		if (m_con) print(*m_con);
	}

	// rotate slice clockwise (slice=0 is top layer)
	void rotateSliceCW(int slice) {
		// (equvilant to rotateCubeLeft, rotateColumnDown(slice), rotateCubeRight)
		for (int i = CUBE_SIZE; i--;) {
			Cubelet::rotate4(
				face[LEFT]->cface[i][CUBE_SIZE - slice - 1],
				face[TOP]->cface[CUBE_SIZE - slice - 1][CUBE_SIZE - i - 1],
				face[RIGHT]->cface[CUBE_SIZE - i - 1][slice],
				face[BOTTOM]->cface[slice][i]);
		}
		if (slice == 0) {
			face[FRONT]->rotateCW();
		}
		else if (slice == CUBE_SIZE - 1) {
			face[BACK]->rotateCCW();
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << slice << ")\n";
		if (m_con) print(*m_con);
	}

	// rotate slice counter-clockwise (slice=0 is top layer)
	void rotateSliceCCW(int slice) {
		// (equvilant to rotateCubeLeft, rotateColumnUp(slice), rotateCubeRight)
		for (int i = CUBE_SIZE; i--;) {
			Cubelet::rotate4(
				face[LEFT]->cface[i][CUBE_SIZE - slice - 1],
				face[BOTTOM]->cface[slice][i],
				face[RIGHT]->cface[CUBE_SIZE - i - 1][slice],
				face[TOP]->cface[CUBE_SIZE - slice - 1][CUBE_SIZE - i - 1]);
		}
		if (slice == 0) {
			face[FRONT]->rotateCCW();
		}
		else if (slice == CUBE_SIZE - 1) {
			face[BACK]->rotateCW();
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << slice << ")\n";
		if (m_con) print(*m_con);
	}

	// rotate slice twice (slice=0 is top layer)
	void rotateSliceTwice(int slice) {
		// (equvilant to rotateCubeLeft, rotateColumnTwice(slice), rotateCubeRight)
		for (int i = CUBE_SIZE; i--;) {
			std::swap(
				face[LEFT]->cface[i][CUBE_SIZE - slice - 1],
				face[RIGHT]->cface[CUBE_SIZE - i - 1][slice]);
			std::swap(
				face[TOP]->cface[CUBE_SIZE - slice - 1][CUBE_SIZE - i - 1],
				face[BOTTOM]->cface[slice][i]);
		}
		if (slice == 0) {
			face[FRONT]->rotateTwice();
		}
		else if (slice == CUBE_SIZE - 1) {
			face[BACK]->rotateTwice();
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << slice << ")\n";
		if (m_con) print(*m_con);
	}

	// rotate the specified face clockwise
	void rotateFaceCW(int side) {
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << side << ")\n";
		switch (side) {
		case FRONT:
			rotateSliceCW(0);
			break;
		case BACK:
			rotateSliceCW(CUBE_SIZE-1);
			break;
		case TOP:
			rotateRowLeft(0);
			break;
		case BOTTOM:
			rotateRowRight(CUBE_SIZE - 1);
			break;
		case LEFT:
			rotateColumnDown(0);
			break;
		case RIGHT:
			rotateColumnUp(CUBE_SIZE - 1);
			break;
		}
	}

	// rotate front slice to the rotation specified
	void restoreFrontRotation(int rot) {
		// rot = new rotation
		// faceRotation() = current rotation
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << rot << ") (was " << face[FRONT]->faceRotation() << ")\n";
		switch (rot - face[FRONT]->faceRotation()) {
		case 0:
			break;
		case 1:
		case -3:
			rotateSliceCW(0);
			break;
		case 2:
		case -2:
			rotateSliceTwice(0);
			break;
		case 3:
		case -1:
			rotateSliceCCW(0);
			break;
		}
	}

	// repeatedly and randomly call various move functions to scramble the cube
	void scramble(int iterations = 200) {
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << " STARTED\n";
		for (int x = iterations; x--;) {
			int r = std::rand() % 20;
			switch (r) {
			case 0:
				rotateCubeUp();
				break;
			case 1:
				rotateCubeDown();
				break;
			case 2:
				rotateCubeLeft();
				break;
			case 3:
				rotateCubeRight();
				break;
			case 4:
				rotateCubeLeft2();
				break;
			case 5:
				rotateCubeUp2();
				break;
			case 6:
				rotateCubeSpinCW();
				break;
			case 7:
				rotateCubeSpinCCW();
				break;
			case 8:
				rotateCubeSpin2();
				break;
			}
			
			r = std::rand() % 6;
			switch (r) {
			case 0:
				rotateColumnUp(std::rand() % CUBE_SIZE);
				break;
			case 1:
				rotateColumnDown(std::rand() % CUBE_SIZE);
				break;
			case 2:
				rotateColumnTwice(std::rand() % CUBE_SIZE);
				break;
			case 3:
				rotateRowLeft(std::rand() % CUBE_SIZE);
				break;
			case 4:
				rotateRowRight(std::rand() % CUBE_SIZE);
				break;
			case 5:
				rotateRowTwice(std::rand() % CUBE_SIZE);
				break;
			}
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << " COMPLETE\n";
	}

	// Is the cube solved?
	bool isSolved() const {
		for (int f = 6; f--;) {
			if (!face[f]->isSolved()) {
				return false;
			}
		}
		return true;
	}

	// searches for an unsolved center and returns face index
	// returns -1 if none are found
	int findUnsolvedCenter() {
		for (int f = 6; f--;) {
			if (!face[f]->isSolved()) {
				return f;
			}
		}
		return -1;
	}

	// searches for an unsolved center (excluding the front and the specified position) and returns face index
	// returns -1 if none are found
	int findUnsolvedCenterExcludingPosAndFront(int pos) {
		for (int f = 1; f < 6; ++f) {
			if ((f != pos) && !face[f]->isSolved()) {
				return f;
			}
		}
		return -1;
	}

	// if the specified face is solved or the specified color, rotate cube until it is not
	// returns true if successful, or false if not
	bool rotateUnsolvedAdjacentToPos(Cubelet::color_t excludeColor, int pos) {
		for (int i = 4; i--;) {
			if ((face[pos]->faceColor() != excludeColor) && !face[pos]->isSolved()) {
				return true;
			}
			rotateCubeSpinCW();
			rotateSliceCCW(0);
		}
		return false;
	}

	// returns number of unsolved centers
	int countUnsolvedCenters() {
		int count = 0;
		for (int f = 6; f--;) {
			if (!face[f]->isSolved()) {
				++count;
			}
		}
		return count;
	}

	// Assumptions: front face as already been searched for a matching part 1
	// move cubelet(s) to form part 1 of center
	// this part is always center column, but can be many rows (from center to bottom edge, not inclusive)
	// 43-53 cubelets on a 7x7
	void solveFaceCenterPart1() {
		int start = CENTER + 1;
		int end = CUBE_SIZE - 2;
		Cubelet::color_t color = face[FRONT]->faceColor();
		int rotation = face[FRONT]->faceRotation();

		for (int row = start; row <= end; ++row) {
			// is cubelet the color we want?
			if (face[FRONT]->cface[row][CENTER].color != color) {
				// find a cubelet the correct color and in the correct position and move it to here
				// search all the faces
				bool found = false;
				// for (int f = 6; f--;)
				for (int f = 0; f < 6; ++f) {
					// rotate each face up to 4 times
					for (int s = 4; s--;) {
						if (face[f]->cface[row][CENTER].color != color) {
							rotateFaceCW(f);
							// turn to that face, rotate the face, then move back.
							//rotateCubeToFront(f);
							//rotateSliceCW(0);
							//rotateCubeToFrontByColor(color);
						}
						else {
							// found a match! Now move it to the front
							found = true;
							switch (f) {
							case FRONT:
								// if first block, we don't care about the state of all the other blocks
								if (row == start) {
									rotation = face[FRONT]->faceRotation();
								} else {
									rotateRowRight(row);
									restoreFrontRotation(rotation);
									rotateRowLeft(row);
								}
								break;
							case BACK:
								rotateSliceCCW(0);
								rotateSliceCW(CUBE_SIZE-1);
								rotateColumnTwice(row);
								rotateSliceCW(0);
								rotateColumnTwice(row);
								break;
							case TOP:
								rotateSliceCCW(0);
								rotateRowRight(0);
								rotateColumnDown(row);
								rotateSliceCW(0);
								rotateColumnUp(row);
								break;
							case BOTTOM:
								rotateSliceCCW(0);
								rotateRowLeft(0);
								rotateColumnUp(row);
								rotateSliceCW(0);
								rotateColumnDown(row);
								break;
							case LEFT:
								rotateRowRight(row);
								rotateSliceCCW(0);
								rotateRowLeft(row);
								rotateSliceCW(0);
								break;
							case RIGHT:
								rotateRowLeft(row);
								rotateSliceCCW(0);
								rotateRowRight(row);
								rotateSliceCW(0);
								break;
							}
							break;
						}
					}
					if (found) break;
				}
			}
		}
	}

	void solveFaceCenterPart2() {
		int start = CENTER;
		int end = CUBE_SIZE - 2;
		Cubelet::color_t origColor = face[FRONT]->faceColor();
		int origRotation = face[FRONT]->faceRotation();
		int	rotation = origRotation;

		// for each column in part 2 & 3...
		for (int col = 1; col <= CUBE_SIZE - 2; ++col) {
			// is the column already done?
			if (!face[FRONT]->isRangeSolved(start, col, end, col)) {
				// if not, build it one at a time
				//rotate to a face that is not solved
				Cubelet::color_t workingFaceColor = -1;
				for (int f = 1; f < 6; ++f) {
					if (!face[f]->isCenterSolved()) {
						rotateCubeToFront(f);
						workingFaceColor = face[FRONT]->faceColor();
						break;
					}
				}
				for (int row = start; row <= end; ++row) {
					if (face[FRONT]->cface[row][col].color != origColor) {
						// find a cubelet the correct color and in the correct position and move it to here
						// search all the faces
						bool found = false;
						// for (int f = 6; f--;)
						for (int f = 0; f < 6; ++f) {
							// FIXME: for now, don't search for blocks on the face we are trying to solve.
							// (need to make sure we don't take blocks from the parts that we have already solved.)
							if (face[f]->faceColor() == origColor) {
								continue;
							}
							// rotate each face up to 4 times
							for (int s = 4; s--;) {
								if (face[f]->cface[row][col].color != origColor) {
									rotateFaceCW(f);
									// turn to that face, rotate the face, then move back.
									//Cubelet::color_t saveColor = face[FRONT]->faceColor();
									//rotateCubeToFront(f);
									//rotateSliceCW(0);
									//rotateCubeToFrontByColor(saveColor);
								}
								else {
									// found a match! Now move it to the working face
									found = true;
									switch (f) {
									case BACK:
										if (row == CENTER) {
											rotateColumnTwice(col);
											rotateSliceCW(0);
											rotateColumnTwice(col);
											rotateSliceCCW(0);
										}
										else {
											rotateRowTwice(row);
											if (col > CENTER) {
												rotateSliceCCW(0);
											}
											else {
												rotateSliceCW(0);
											}
											rotateRowTwice(row);
											if (col > CENTER) {
												rotateSliceCW(0);
											}
											else {
												rotateSliceCCW(0);
											}
										}
										break;

									case BOTTOM:
										// spin and then do left
										rotateCubeSpinCW();
										rotateSliceCCW(0);
										rotateColumnUp(0);
										// YES, I want to drop down to LEFT
									case LEFT:
										if (row == CENTER) {
											rotateSliceCW(0);
											rotateColumnDown(0);
											rotateRowRight(col);
											rotateSliceCCW(0);
											rotateRowLeft(col);
										}
										else {
											rotateRowRight(row);
											if (col > CENTER) {
												rotateSliceCCW(0);
											}
											else {
												rotateSliceCW(0);
											}
											rotateRowLeft(row);
											if (col > CENTER) {
												rotateSliceCW(0);
											}
											else {
												rotateSliceCCW(0);
											}
										}
										break;
									case FRONT:
										if (row == CENTER) {
											// if first block, we don't care about the state of all the other blocks
											// coincidentially, the center block MUST be moved first
											break;
										}
										else {
											//// for cases where the previous blocks will be in the way, rotate them out of the way
											//int delta = rotation - face[FRONT]->faceRotation();
											//if (delta < 0) {
											//	delta += 4;
											//}
											//if (((col > CENTER) && (delta == 3)) ||
											//	(col < CENTER) && (delta == 1)) {
											//	// make sure we don't break a solved face, or the one we are working on
												rotateUnsolvedAdjacentToPos(origColor, BOTTOM);
												rotateColumnUp(col);
												restoreFrontRotation(rotation);
											//	if (col > CENTER) {
											//		rotateSliceCW(0);
											//	}
											//	else {
											//		rotateSliceCCW(0);
											//	}
											//	rotateColumnDown(col);
											//}
											//// make sure we don't break a solved face, or the one we are working on
											//rotateUnsolvedAdjacentToPos(origColor, LEFT);
											//rotateRowRight(row);
											//restoreFrontRotation(rotation);
											//rotateRowLeft(row);
										}
										// YES, I want to drop down to TOP
									case TOP:
										// spin and then do right
										rotateCubeSpinCW();
										rotateSliceCCW(0);
										rotateColumnDown(CUBE_SIZE - 1);
										// YES, I want to drop down to RIGHT
									case RIGHT:
										if (row == CENTER) {
											rotateSliceCW(0);
											rotateColumnUp(CUBE_SIZE-1);
											rotateRowLeft(col);
											rotateSliceCCW(0);
											rotateRowRight(col);
										}
										else {
											rotateRowLeft(row);
											if (col > CENTER) {
												rotateSliceCCW(0);
											}
											else {
												rotateSliceCW(0);
											}
											rotateRowRight(row);
											if (col > CENTER) {
												rotateSliceCW(0);
											}
											else {
												rotateSliceCCW(0);
											}
										}
										break;
									}
									if (row == CENTER) {
										rotation = face[FRONT]->faceRotation();
									}
									break;
								}
							}
							if (found) break;
						}
					}
				}

				rotateCubeToFrontByColor(origColor);
				restoreFrontRotation(origRotation);
				// move this set to the face we are solving
				switch (findCubeByColor(workingFaceColor)) {
				case FRONT:
					// shouldn't happen
					break;
				case BACK:
					rotateSliceTwice(0);
					rotateColumnTwice(col);
					rotateSliceTwice(0);
					break;
				case LEFT:
					// spin and then do top
					rotateCubeSpinCW();
					rotateSliceCCW(0);
					rotateRowRight(0);
					// YES, I want to drop down to TOP
				case TOP:
					rotateColumnDown(col);
					if (col > CENTER) {
						rotateSliceCW(0);
					}
					else {
						rotateSliceCCW(0);
					}
					rotateColumnUp(col);
					if (col > CENTER) {
						rotateSliceCCW(0);
					}
					else {
						rotateSliceCW(0);
					}
					break;
				case RIGHT:
					// spin and then do bottom
					rotateCubeSpinCW();
					rotateSliceCCW(0);
					rotateRowLeft(CUBE_SIZE - 1);
					// YES, I want to drop down to BOTTOM
				case BOTTOM:
					rotateColumnUp(col);
					if (col > CENTER) {
						rotateSliceCW(0);
					}
					else {
						rotateSliceCCW(0);
					}
					rotateColumnDown(col);
					if (col > CENTER) {
						rotateSliceCCW(0);
					}
					else {
						rotateSliceCW(0);
					}
					break;
				}

			}
		}
		//restoreFrontRotation(origRotation);
	}

	void solveFaceCenterPart3() {
	}


	void solveFaceCenterPart4() {

	}

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
	void solveCurrentFaceCenter() {
		solveFaceCenterPart1();

		solveFaceCenterPart2();

		//solveFaceCenterPart3();

		solveFaceCenterPart4();
	}

	// solve the front face center
	void solveFaceCenters() {
		while (true) {
			// find an unsolved face center
			int f = findUnsolvedCenter();

			// if there are none, get out
			if (f == -1) {
				break;
			}

			// bring unsolved face to front
			rotateCubeToFront(f);

			// do steps to solve the center of current face
			solveCurrentFaceCenter();
			break;//debugging
		}
	}


	// 3x3 algorithms
	//1) F' U L' U' - flip side
	//2) R' D' R D - rotate corner
	//3) U R U' R' U' F' U F - get piece from top middle to right middle
	//4) U' L' U L U F U' F' - get piece from top middle to left middle
	//5) F R U R' U' F' - repeat to get cross on top
	//6) R U R' U R U U R' U - match back and R, get top middle to match
	//7) U R U' L' U R' U' L - corners; put correct corner at F top right
	//
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

	void algoRotateCornerRD() {
		rotateColumnDown(CUBE_SIZE - 1); // R'
		rotateRowLeft(CUBE_SIZE - 1); // D'
		rotateColumnUp(CUBE_SIZE - 1); // R
		rotateRowRight(CUBE_SIZE - 1); // D
	}

	void algoRotateCornerLD() {
		rotateColumnDown(0); // L
		rotateRowRight(CUBE_SIZE - 1); // D
		rotateColumnUp(0); // L'
		rotateRowLeft(CUBE_SIZE - 1); // D'
	}

	void printRow(std::ostream& s, Face* face, int row) const {
		for (int col = 0; col < CUBE_SIZE; ++col) {
			s << face->cface[row][col].color << ' ';
		}
	}

	void print(std::ostream& s) const {
		std::string spacing(CUBE_SIZE * 2 + 1, ' ');
		s << spacing << face[TOP]->faceColor() << ' ' << face[TOP]->m_rotation << "\n";
		for (int row = 0; row < CUBE_SIZE; ++row) {
			s << spacing;
			printRow(s, face[TOP], row);
			s << '\n';
		}
		s << '\n';
		s << face[LEFT]->faceColor() << ' ' << face[LEFT]->m_rotation << std::string((CUBE_SIZE * 2 + 1) - 3, ' ');
		s << face[FRONT]->faceColor() << ' ' << face[FRONT]->m_rotation << std::string((CUBE_SIZE * 2 + 1) - 3, ' ');
		s << face[RIGHT]->faceColor() << ' ' << face[RIGHT]->m_rotation << std::string((CUBE_SIZE * 2 + 1) - 3, ' ');
		s << face[BACK]->faceColor() << ' ' << face[BACK]->m_rotation << "\n";
		for (int row = 0; row < CUBE_SIZE; ++row) {
			printRow(s, face[LEFT], row);
			s << ' ';
			printRow(s, face[FRONT], row);
			s << ' ';
			printRow(s, face[RIGHT], row);
			s << ' ';
			printRow(s, face[BACK], row);
			s << '\n';
		}
		s << '\n';
		s << spacing << face[BOTTOM]->faceColor() << ' ' << face[BOTTOM]->m_rotation << "\n";
		for (int row = 0; row < CUBE_SIZE; ++row) {
			s << spacing;
			printRow(s, face[BOTTOM], row);
			s << '\n';
		}
		s << '\n';
	}

	Face* face[6];
	const int CENTER = CUBE_SIZE / 2;
	std::ostream* m_con;
};
