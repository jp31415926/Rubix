#pragma once

#include <algorithm> // std::swap
#include <iomanip> // std::setw
#include <cstdlib>
#include <ctime>
#include "Tokenize.h"
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
	Cube() {
		if ((CUBE_SIZE & 1) == 0) {
			std::cerr << "cube dimension must be odd\n";
			throw std::exception("cube dimension must be odd");
		}
		m_con = 0;

		//std::srand((unsigned)std::time(nullptr));
		for (int i = 6; i--;) {
			Face* f = new Face;
			f->initColor(i + 1);
			face[i] = f;
		}
		face[FRONT]->initColor('W');
		face[UP]->initColor('B');
		face[DOWN]->initColor('G');
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
		// BACK = UP (for example) means moving from UP to BACK
		// BACK <- UP or DOWN (and vice versa) require a rotateTwice (flip)
		Face* front = face[FRONT];
		face[FRONT] = face[DOWN];
		face[DOWN] = face[BACK];
		face[BACK] = face[UP];
		face[UP] = front;
		face[LEFT]->rotateCCW();
		face[RIGHT]->rotateCW();

		face[DOWN]->rotateTwice();
		face[BACK]->rotateTwice();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeDown() {
		// BACK = UP (for example) means moving from UP to BACK
		// BACK <- UP or DOWN (and vice versa) require a rotateTwice (flip)
		Face* front = face[FRONT];
		face[FRONT] = face[UP];
		face[UP] = face[BACK];
		face[BACK] = face[DOWN];
		face[DOWN] = front;
		face[LEFT]->rotateCW();
		face[RIGHT]->rotateCCW();

		face[UP]->rotateTwice();
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
		face[UP]->rotateCW();
		face[DOWN]->rotateCCW();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeRight() {
		Face* front = face[FRONT];
		face[FRONT] = face[LEFT];
		face[LEFT] = face[BACK];
		face[BACK] = face[RIGHT];
		face[RIGHT] = front;
		face[UP]->rotateCCW();
		face[DOWN]->rotateCW();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeSpinCW() {
		Face* top = face[UP];
		face[UP] = face[LEFT];
		face[LEFT] = face[DOWN];
		face[DOWN] = face[RIGHT];
		face[RIGHT] = top;

		face[UP]->rotateCW();
		face[DOWN]->rotateCW();
		face[LEFT]->rotateCW();
		face[RIGHT]->rotateCW();
		face[FRONT]->rotateCW();
		face[BACK]->rotateCCW();

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "\n";
		if (m_con) print(*m_con);
	}

	void rotateCubeSpinCCW() {
		Face* top = face[UP];
		face[UP] = face[RIGHT];
		face[RIGHT] = face[DOWN];
		face[DOWN] = face[LEFT];
		face[LEFT] = top;

		face[UP]->rotateCCW();
		face[DOWN]->rotateCCW();
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
		case UP:
			rotateCubeDown();
			break;
		case DOWN:
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
		case UP:
			rotateCubeUp();
			break;
		case DOWN:
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
				face[UP]->cface[i][col],
				//face[BACK]->cface[i][col],
				face[BACK]->cface[CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - col],
				face[DOWN]->cface[i][col]);
			face[BACK]->cface[CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - col].adjustRotation(2);
			face[DOWN]->cface[i][col].adjustRotation(2);
		}
		if (col == 0) {
			face[LEFT]->rotateCCW();
		}
		else if (col == CUBE_SIZE - 1) {
			face[RIGHT]->rotateCW();
		}
		else if (col == CENTER) {
			face[BACK]->adjustRotation(2);
			face[DOWN]->adjustRotation(2);
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << col << ")\n";
		if (m_con) print(*m_con);
	}

	void rotateColumnDown(int col) {
		for (int i = CUBE_SIZE; i--;) {
			Cubelet::rotate4(
				face[FRONT]->cface[i][col],
				face[DOWN]->cface[i][col],
				//face[BACK]->cface[i][col],
				face[BACK]->cface[CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - col],
				face[UP]->cface[i][col]);
			face[BACK]->cface[CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - col].adjustRotation(2);
			face[UP]->cface[i][col].adjustRotation(2);
		}
		if (col == 0) {
			face[LEFT]->rotateCW();
		}
		else if (col == CUBE_SIZE - 1) {
			face[RIGHT]->rotateCCW();
		}
		else if (col == CENTER) {
			face[BACK]->adjustRotation(2);
			face[UP]->adjustRotation(2);
		}

		if (m_con) *m_con << "Cube::" << __FUNCTION__ << "(" << col << ")\n";
		if (m_con) print(*m_con);
	}

	void rotateColumnTwice(int col) {
		for (int i = CUBE_SIZE; i--;) {
			std::swap(
				face[FRONT]->cface[i][col],
				face[BACK]->cface[CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - col]);
			std::swap(
				face[UP]->cface[i][col],
				face[DOWN]->cface[i][col]);
			face[BACK]->cface[CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - col].adjustRotation(2);
			face[FRONT]->cface[i][col].adjustRotation(2);
		}
		if (col == 0) {
			face[LEFT]->rotateTwice();
		}
		else if (col == CUBE_SIZE - 1) {
			face[RIGHT]->rotateTwice();
		}
		else if (col == CENTER) {
			face[BACK]->adjustRotation(2);
			face[FRONT]->adjustRotation(2);
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
			face[UP]->rotateCW();
		}
		else if (row == CUBE_SIZE - 1) {
			face[DOWN]->rotateCCW();
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
			face[UP]->rotateCCW();
		}
		else if (row == CUBE_SIZE - 1) {
			face[DOWN]->rotateCW();
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
			face[UP]->rotateTwice();
		}
		else if (row == CUBE_SIZE - 1) {
			face[DOWN]->rotateTwice();
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
				face[UP]->cface[CUBE_SIZE - slice - 1][CUBE_SIZE - i - 1],
				face[RIGHT]->cface[CUBE_SIZE - i - 1][slice],
				face[DOWN]->cface[slice][i]);
			face[LEFT]->cface[i][CUBE_SIZE - slice - 1].adjustRotation(1);
			face[UP]->cface[CUBE_SIZE - slice - 1][CUBE_SIZE - i - 1].adjustRotation(1);
			face[RIGHT]->cface[CUBE_SIZE - i - 1][slice].adjustRotation(1);
			face[DOWN]->cface[slice][i].adjustRotation(1);
		}
		if (slice == 0) {
			face[FRONT]->rotateCW();
		}
		else if (slice == CUBE_SIZE - 1) {
			face[BACK]->rotateCCW();
		}
		else if (slice == CENTER) {
			face[LEFT]->adjustRotation(1);
			face[UP]->adjustRotation(1);
			face[RIGHT]->adjustRotation(1);
			face[DOWN]->adjustRotation(1);
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
				face[DOWN]->cface[slice][i],
				face[RIGHT]->cface[CUBE_SIZE - i - 1][slice],
				face[UP]->cface[CUBE_SIZE - slice - 1][CUBE_SIZE - i - 1]);
			face[LEFT]->cface[i][CUBE_SIZE - slice - 1].adjustRotation(-1);
			face[UP]->cface[CUBE_SIZE - slice - 1][CUBE_SIZE - i - 1].adjustRotation(-1);
			face[RIGHT]->cface[CUBE_SIZE - i - 1][slice].adjustRotation(-1);
			face[DOWN]->cface[slice][i].adjustRotation(-1);
		}
		if (slice == 0) {
			face[FRONT]->rotateCCW();
		}
		else if (slice == CUBE_SIZE - 1) {
			face[BACK]->rotateCW();
		}
		else if (slice == CENTER) {
			face[LEFT]->adjustRotation(-1);
			face[UP]->adjustRotation(-1);
			face[RIGHT]->adjustRotation(-1);
			face[DOWN]->adjustRotation(-1);
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
				face[UP]->cface[CUBE_SIZE - slice - 1][CUBE_SIZE - i - 1],
				face[DOWN]->cface[slice][i]);
			face[LEFT]->cface[i][CUBE_SIZE - slice - 1].adjustRotation(2);
			face[UP]->cface[CUBE_SIZE - slice - 1][CUBE_SIZE - i - 1].adjustRotation(2);
			face[RIGHT]->cface[CUBE_SIZE - i - 1][slice].adjustRotation(2);
			face[DOWN]->cface[slice][i].adjustRotation(2);
		}
		if (slice == 0) {
			face[FRONT]->rotateTwice();
		}
		else if (slice == CUBE_SIZE - 1) {
			face[BACK]->rotateTwice();
		}
		else if (slice == CENTER) {
			face[LEFT]->adjustRotation(2);
			face[UP]->adjustRotation(2);
			face[RIGHT]->adjustRotation(2);
			face[DOWN]->adjustRotation(2);
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
			rotateSliceCW(CUBE_SIZE - 1);
			break;
		case UP:
			rotateRowLeft(0);
			break;
		case DOWN:
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
	void scramble(int iterations = 200, bool limitTo3x3 = false) {
		if (m_con) *m_con << "Cube::" << __FUNCTION__ << " STARTED\n";
		int layer;
		for (int x = iterations; x--;) {
			switch (std::rand() % 20) {
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

			if (limitTo3x3) {
				layer = (std::rand() % 2) * (CUBE_SIZE - 1);
			}
			else {
				layer = std::rand() % CUBE_SIZE;
			}

			switch (std::rand() % 6) {
			case 0:
				rotateColumnUp(layer);
				break;
			case 1:
				rotateColumnDown(layer);
				break;
			case 2:
				rotateColumnTwice(layer);
				break;
			case 3:
				rotateRowLeft(layer);
				break;
			case 4:
				rotateRowRight(layer);
				break;
			case 5:
				rotateRowTwice(layer);
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
								}
								else {
									rotateRowRight(row);
									restoreFrontRotation(rotation);
									rotateRowLeft(row);
								}
								break;
							case BACK:
								rotateSliceCCW(0);
								rotateSliceCW(CUBE_SIZE - 1);
								rotateColumnTwice(row);
								rotateSliceCW(0);
								rotateColumnTwice(row);
								break;
							case UP:
								rotateSliceCCW(0);
								rotateRowRight(0);
								rotateColumnDown(row);
								rotateSliceCW(0);
								rotateColumnUp(row);
								break;
							case DOWN:
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

									case DOWN:
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
											rotateUnsolvedAdjacentToPos(origColor, DOWN);
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
										// YES, I want to drop down to UP
									case UP:
										// spin and then do right
										rotateCubeSpinCW();
										rotateSliceCCW(0);
										rotateColumnDown(CUBE_SIZE - 1);
										// YES, I want to drop down to RIGHT
									case RIGHT:
										if (row == CENTER) {
											rotateSliceCW(0);
											rotateColumnUp(CUBE_SIZE - 1);
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
					// YES, I want to drop down to UP
				case UP:
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
					// YES, I want to drop down to DOWN
				case DOWN:
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

	// perform algorithms
	// Example: F U' R U
	void performAlgorithm(const std::string& s) {
		if (m_con) *m_con << "performAlgorithm(" << s << ")\n";
		std::vector<std::string> tokens(tokenize(s, " \t\n\r()"));
		for (std::string move : tokens) {
			if (m_con) *m_con << "performAlgorithm move " << move << "\n";
			int width = 1;
			bool reverse = false;
			int interations = 1;
			if (move[0] == '3') {
				width = 3;
				move.erase(0, 1);
			}
			if (move[move.size() - 1] == 'W') {
				width = 2;
				move.erase(move.size() - 1, 1);
			}
			if (move[move.size() - 1] == '\'') {
				reverse = true;
				move.erase(move.size() - 1, 1);
			}
			if (move[move.size() - 1] == '2') {
				interations = 2;
				move.erase(move.size() - 1, 1);
			}
			if (move == "U") {
				while (width--) {
					for (int i = interations; i--;) {
						if (reverse) {
							rotateSliceCCW(width); // U'
						}
						else {
							rotateSliceCW(width); // U
						}
					}
				}
			}
			else if (move == "L") {
				while (width--) {
					for (int i = interations; i--;) {
						if (reverse) {
							rotateColumnUp(width); // L'
						}
						else {
							rotateColumnDown(width); // L
						}
					}
				}
			}
			else if (move == "F") {
				while (width--) {
					for (int i = interations; i--;) {
						if (reverse) {
							rotateRowLeft(CUBE_SIZE - 1 - width); // F'
						}
						else {
							rotateRowRight(CUBE_SIZE - 1 - width); // F'
						}
					}
				}
			}
			else if (move == "D") {
				while (width--) {
					for (int i = interations; i--;) {
						if (reverse) {
							rotateSliceCW(CUBE_SIZE - 1 - width); // D'
						}
						else {
							rotateSliceCCW(CUBE_SIZE - 1 - width); // D
						}
					}
				}
			}
			else if (move == "R") {
				while (width--) {
					for (int i = interations; i--;) {
						if (reverse) {
							rotateColumnDown(CUBE_SIZE - 1 - width); // R'
						}
						else {
							rotateColumnUp(CUBE_SIZE - 1 - width); // R
						}
					}
				}
			}
			else if (move == "B") {
				while (width--) {
					for (int i = interations; i--;) {
						if (reverse) {
							rotateRowRight(width);
						}
						else {
							rotateRowLeft(width);
						}
					}
				}
			}
			else {
				// unknown move... ignore it
			}
		}
	}

	// Solve the 2st later cross on FRONT layer
	bool solve3x3FirstLayerCross() {
		// start at top center of face and rotate clockwise
		Cubelet::color_t frontColor = face[FRONT]->faceColor();
		int timeout = 10;

		int sidesSolved = 0;
		// may have to make multiple passes
		while (sidesSolved < 4 && --timeout) {
			sidesSolved = 0;
			for (int s = 4; s--;) {
				bool solved = false;
				Cubelet::color_t frontBottomEdgeColor = face[FRONT]->cface[CUBE_SIZE - 1][CENTER].color;
				Cubelet::color_t downColorToMatch = face[DOWN]->faceColor();
				//if (m_con) *m_con << "Looking for " << frontColor << downColorToMatch << " edge\n";
				// is this edge peice solved?
				Cubelet::color_t downTopEdgeColor = face[DOWN]->cface[0][CENTER].color;

				//std::cout << "  checking " << frontBottomEdgeColor << downTopEdgeColor << " already solved\n";
				if ((frontBottomEdgeColor == frontColor) &&
					(downTopEdgeColor == downColorToMatch) &&
					(face[DOWN]->faceColor() == downColorToMatch)) {
					solved = true;
				}

				//std::cout << "  checking " << downTopEdgeColor << frontBottomEdgeColor << " top reversed\n";
				// check if piece is in the correct position, but needs to be flipped
				if (!solved && (frontBottomEdgeColor == downColorToMatch) &&
					(downTopEdgeColor == frontColor)) {
					// F U' R U
					performAlgorithm("F U' R U");
					//rotateRowRight(CUBE_SIZE - 1);
					//rotateSliceCCW(0);
					//rotateColumnUp(CUBE_SIZE - 1);
					//rotateSliceCW(0);
					solved = true;
				}

				if (!solved) {
					for (int t = 4; t--;) {
						// check middle for the edge piece we are looking for (on the down side)
						Cubelet::color_t downLeftEdgeColor = face[DOWN]->cface[CENTER][0].color;
						Cubelet::color_t leftBottomEdgeColor = face[LEFT]->cface[CUBE_SIZE - 1][CENTER].color;
						//std::cout << "  checking " << leftBottomEdgeColor << downLeftEdgeColor << " left\n";
						// check if left center of down side matches
						if ((downLeftEdgeColor == downColorToMatch) && (leftBottomEdgeColor == frontColor)) {
							performAlgorithm("F");
							//rotateRowRight(CUBE_SIZE - 1);
							solved = true;
							break;
						}

						Cubelet::color_t downRightEdgeColor = face[DOWN]->cface[CENTER][CUBE_SIZE - 1].color;
						Cubelet::color_t rightBottomEdgeColor = face[RIGHT]->cface[CUBE_SIZE - 1][CENTER].color;
						//std::cout << "  checking " << rightBottomEdgeColor << downRightEdgeColor << " right\n";
						// check if right center of down side matches
						if ((downRightEdgeColor == downColorToMatch) && (rightBottomEdgeColor == frontColor)) {
							performAlgorithm("F'");
							//rotateRowLeft(CUBE_SIZE - 1);
							solved = true;
							break;
						}

						// check bottom for the edge piece we are looking for (on the down side)
						Cubelet::color_t downBottomEdgeColor = face[DOWN]->cface[CUBE_SIZE - 1][CENTER].color;
						Cubelet::color_t backBottomEdgeColor = face[BACK]->cface[CUBE_SIZE - 1][CENTER].color;
						//std::cout << "  checking " << backBottomEdgeColor << downBottomEdgeColor << " bottom\n";
						// check if right center of down side matches
						if ((downBottomEdgeColor == downColorToMatch) && (backBottomEdgeColor == frontColor)) {
							performAlgorithm("F2");
							//rotateRowTwice(CUBE_SIZE - 1);
							solved = true;
							break;
						}

						//std::cout << "  checking " << downBottomEdgeColor << backBottomEdgeColor << " bottom reversed\n";
						// check if bottom peice needs to be flipped
						if ((downBottomEdgeColor == frontColor) && (backBottomEdgeColor == downColorToMatch)) {
							performAlgorithm("F' U' R U");
							//rotateRowLeft(CUBE_SIZE - 1);
							//rotateSliceCCW(0);
							//rotateColumnUp(CUBE_SIZE - 1);
							//rotateSliceCW(0);
							solved = true;
							break;
						}

						// not solved yet
						// rotate cube except FRONT if not solved
						rotateCubeSpinCW();
						rotateSliceCCW(0);
					}
				}

				if (solved) {
					//std::cout << "  solved!\n";
					++sidesSolved;
					while (downColorToMatch != face[DOWN]->faceColor()) {
						rotateCubeSpinCW();
						rotateSliceCCW(0);
					}
				}
				// rotate cube
				rotateCubeSpinCW();
			}
		}
		return timeout != 0;
	}

	bool solve3x3FirstLayerCorners() {
		int timeout = 10;
		while (!face[FRONT]->isSolved() && --timeout) {
			Cubelet::color_t frontColor = face[FRONT]->faceColor();
			Cubelet::color_t downColor = face[DOWN]->faceColor();
			Cubelet::color_t rightColor = face[RIGHT]->faceColor();
			if (m_con) *m_con << "Looking for " << frontColor << downColor << rightColor << " corner\n";

			for (int s = 4; s--;) {
				Cubelet::color_t frontBottomRightCornerColor = face[FRONT]->cface[CUBE_SIZE - 1][CUBE_SIZE - 1].color;
				Cubelet::color_t downTopRightCornerColor = face[DOWN]->cface[0][CUBE_SIZE - 1].color;
				Cubelet::color_t rightTopLeftCornerColor = face[RIGHT]->cface[0][0].color;

				// corner solved?
				if ((frontColor != frontBottomRightCornerColor) ||
					(downColor != downTopRightCornerColor) ||
					(rightColor != rightTopLeftCornerColor)) {

					Cubelet::color_t downBottomRightCornerColor = face[DOWN]->cface[CUBE_SIZE - 1][CUBE_SIZE - 1].color;
					Cubelet::color_t rightBottomRightCornerColor = face[RIGHT]->cface[CUBE_SIZE - 1][CUBE_SIZE - 1].color;
					Cubelet::color_t backBottomLeftCornerColor = face[BACK]->cface[CUBE_SIZE - 1][0].color;

					if (m_con) *m_con << "  checking " << downBottomRightCornerColor << backBottomLeftCornerColor << rightBottomRightCornerColor << "\n";
					if (m_con) *m_con << "  checking " << rightBottomRightCornerColor << downBottomRightCornerColor << backBottomLeftCornerColor << "\n";
					if (m_con) *m_con << "  checking " << backBottomLeftCornerColor << rightBottomRightCornerColor << downBottomRightCornerColor << "\n";

					// check down bottom right corner
					if ((frontColor == downBottomRightCornerColor) &&
						(downColor == backBottomLeftCornerColor) &&
						(rightColor == rightBottomRightCornerColor)) {
						rotateCubeSpinCW();
						performAlgorithm("L D L' D'");
						rotateCubeSpinCCW();
						break;
					}
					else if ((frontColor == rightBottomRightCornerColor) &&
						(downColor == downBottomRightCornerColor) &&
						(rightColor == backBottomLeftCornerColor)) {
						performAlgorithm("R' D' R D");
						break;
					}
					else if ((frontColor == backBottomLeftCornerColor) &&
						(downColor == rightBottomRightCornerColor) &&
						(rightColor == downBottomRightCornerColor)) {
						performAlgorithm("R' D' R D");
						performAlgorithm("R' D' R D");
						performAlgorithm("R' D' R D");
						break;
					}
				}
				rotateSliceCCW(CUBE_SIZE - 1); // D
			}
			rotateCubeSpinCW();
		}

		return timeout != 0;
	}

	bool isSecondLayerSolved() {
		Cubelet::color_t leftColor = face[LEFT]->faceColor();
		Cubelet::color_t upColor = face[UP]->faceColor();
		Cubelet::color_t rightColor = face[RIGHT]->faceColor();
		Cubelet::color_t downColor = face[DOWN]->faceColor();

		for (int i = CUBE_SIZE; i--;) {
			if ((face[LEFT]->cface[i][CENTER].color != leftColor) ||
				(face[UP]->cface[CENTER][CUBE_SIZE - i - 1].color != upColor) ||
				(face[RIGHT]->cface[CUBE_SIZE - i - 1][CENTER].color != rightColor) ||
				(face[DOWN]->cface[CENTER][i].color != downColor)) {
				return false;
			}
		}
		return true;
	}

/*
FIXME: sometimes this happens:

			 O 3
			 O O O
			 O O O
			 B R Y

W 0    B 2    Y 2    G 0
W W R  Y B O  B Y Y  G G G
W W O  B B B  Y Y Y  G G G
W R B  R W B  W W Y  G G G

			 R 2
			 W B O
			 Y R R
			 R R R

Notice all FRONT edge pieces belong to B and RY and RW are in the second later, but not in the correct location.

*/

	bool solve3x3SecondLayer() {
		int timeout = 20;
		if (face[FRONT]->isSolved()) {
			rotateCubeLeft2();
		}
		else {
			if (m_con) *m_con << "FRONT is not solved!!!\n";
			return false; // this should not happen if the last step worked
		}
		while (!isSecondLayerSolved() && --timeout) {
			for (int s = 4; s--;) {
				Cubelet::color_t downTopEdgeColor = face[DOWN]->cface[0][CENTER].color;
				Cubelet::color_t downColor = face[DOWN]->faceColor();
				Cubelet::color_t rightColor = face[RIGHT]->faceColor();

				if (downColor == downTopEdgeColor) {
					Cubelet::color_t frontBottomEdgeColor = face[FRONT]->cface[CUBE_SIZE - 1][CENTER].color;
					if (rightColor == frontBottomEdgeColor) {
						if (m_con) *m_con << "match to right edge\n";
						performAlgorithm("U R U' R' U' F' U F");
						break;
					}
					Cubelet::color_t leftColor = face[LEFT]->faceColor();
					if (leftColor == frontBottomEdgeColor) {
						if (m_con) *m_con << "match to left edge\n";
						performAlgorithm("U' L' U L U F U' F'");
						break;
					}
				}
				// check if edge on left needs to move to right
				Cubelet::color_t downLeftEdgeColor = face[DOWN]->cface[CENTER][0].color;
				Cubelet::color_t leftBottomEdgeColor = face[LEFT]->cface[CUBE_SIZE - 1][CENTER].color;
				if ((downLeftEdgeColor == downColor) && (leftBottomEdgeColor == rightColor)) {
					//move 
					performAlgorithm("U R U' R' U' F' U F");
					rotateCubeSpinCW();
					performAlgorithm("L' U L U F U' F'");
					break;
				}
				// check flip case also
				if ((downLeftEdgeColor == rightColor) && (leftBottomEdgeColor == downColor)) {
					//move 
					performAlgorithm("U' L' U L U F U' F'");
					performAlgorithm("U' R U' R' U' F' U F");
					break;
				}

				// rotate the top
				performAlgorithm("U");
			}
			// rotate the cube
			rotateCubeSpinCW();
		}
		return timeout != 0;
	}

	void solve3x3LastLayerCross() {
		Cubelet::color_t frontColor = face[FRONT]->faceColor();
		while (true) {
			int top = face[FRONT]->cface[0][CENTER].color == frontColor ? 1 : 0;
			int left = face[FRONT]->cface[CENTER][0].color == frontColor ? 2 : 0;
			int right = face[FRONT]->cface[CENTER][CUBE_SIZE-1].color == frontColor ? 4 : 0;
			int bottom = face[FRONT]->cface[CUBE_SIZE - 1][CENTER].color == frontColor ? 8 : 0;

			switch (top + left + right + bottom) {
			case 0: // none - go once and reevaluate
				performAlgorithm("F R U R' U' F'");
				break;

			case 9: // top and bottom
				performAlgorithm("U"); // transform to left and right
			case 6: // left and right
				performAlgorithm("F R U R' U' F'");
				return;

			case 10: // left and bottom
				performAlgorithm("U'"); // transform to right and bottom
			case 12: // right and bottom
				performAlgorithm("U'"); // transform to top and right
			case 5: // top and right
				performAlgorithm("U'"); // transform to top and left
			case 3: // top and left
				performAlgorithm("F R U R' U' F'");
				performAlgorithm("F R U R' U' F'");
				return;

			case 15: // all 4!
				return; // done!

			case 1: // top only
			case 2: // left only
			case 4: // right only
			case 7: // top left and right
			case 8: // bottom only
			case 11: // top, left and bottom
			case 13: // top, right and bottom
			case 14: // left, right and bottom
				return;
			}

			if (top && left && right && bottom) {
				return;
			}
			if (left && top) {
			}
			if (top && right) {
			}
		}
	}

	void solve3x3LastLayerCornerOrientation() {
		Cubelet::color_t frontColor = face[FRONT]->faceColor();
		while (!face[FRONT]->isSolved()) {
			int count = 0;
			for (int s = 4; s--;) {
				if (face[FRONT]->cface[0][0].color == frontColor) {
					++count;
				}
				rotateSliceCW(0);
			}
			switch (count) {
			case 0:
				while (face[LEFT]->cface[0][CUBE_SIZE - 1].color != frontColor) {
					rotateSliceCW(0);
				}
				break;
			case 1:
				while (face[FRONT]->cface[CUBE_SIZE - 1][0].color != frontColor) {
					rotateSliceCW(0);
				}
				break;
			case 2:
				while (face[DOWN]->cface[0][0].color != frontColor) {
					rotateSliceCW(0);
				}
				break;
			}
			performAlgorithm("R U R' U R U2 R'");
		}
	}

	bool areCornersSolved() {
		// see if corners are solved
		for (int s = 4; s--;) {
			Cubelet::color_t frontColor = face[FRONT]->faceColor();
			Cubelet::color_t downColor = face[DOWN]->faceColor();
			Cubelet::color_t rightColor = face[RIGHT]->faceColor();
			Cubelet::color_t frontBottomRightCornerColor = face[FRONT]->cface[CUBE_SIZE - 1][CUBE_SIZE - 1].color;
			Cubelet::color_t downTopRightCornerColor = face[DOWN]->cface[0][CUBE_SIZE - 1].color;
			Cubelet::color_t rightTopLeftCornerColor = face[RIGHT]->cface[0][0].color;

			// corner solved?
			if ((frontColor != frontBottomRightCornerColor) ||
				(downColor != downTopRightCornerColor) ||
				(rightColor != rightTopLeftCornerColor)) {
				return false;
			}
			rotateCubeSpinCW();
		}
		return true;
	}

	void solve3x3LastLayerCornerPermutation() {
		bool found = false;
		
		while (!areCornersSolved()) {
			for (int s = 4; s--;) {
				if (face[LEFT]->cface[CUBE_SIZE - 1][CUBE_SIZE - 1].color == face[LEFT]->cface[0][CUBE_SIZE - 1].color) {
					found = true;
					break;
				}
				rotateSliceCW(0);
			}
			if (found) {
				while (face[LEFT]->cface[CUBE_SIZE - 1][CUBE_SIZE - 1].color != face[LEFT]->faceColor()) {
					rotateCubeSpinCW();
					rotateSliceCCW(0);
				}
			}
			performAlgorithm("R U R' U' R' F R2 U' R' U' R U R' F'");
		}
	}

	void solve3x3LastLayerEdgePermutation() {
		while (!isSolved()) {
			for (int s = 4; s--;) {
				if (face[UP]->cface[CUBE_SIZE - 1][0].color == face[UP]->cface[CUBE_SIZE - 1][CENTER].color) {
					break;
				}
				rotateCubeSpinCW();
			}
			performAlgorithm("R U' R U R U R U' R' U' R2");
		}
	}

	// This solves any size cube like a 3x3. It assumes all the centers and edges are complete for cubes greater than 3x3.
	bool solve3x3() {
		bool result;
		std::cout << "  solve3x3FirstLayerCross\n";
		result = solve3x3FirstLayerCross();
		if (!result) {
			std::cout << "solve3x3FirstLayerCross() FAILED!\n";
			print(std::cout);
			return false;
		}
		std::cout << "  solve3x3FirstLayerCorners\n";
		result = solve3x3FirstLayerCorners();
		if (!result) {
			std::cout << "solve3x3FirstLayerCorners() FAILED!\n";
			print(std::cout);
			return false;
		}
		std::cout << "  solve3x3SecondLayer\n";
		result = solve3x3SecondLayer();
		if (!result) {
			std::cout << "solve3x3SecondLayer() FAILED!\n";
			print(std::cout);
			return false;
		}
		std::cout << "  solve3x3LastLayerCross\n";
		solve3x3LastLayerCross();
		std::cout << "  solve3x3LastLayerCornerOrientation\n";
		solve3x3LastLayerCornerOrientation();
		std::cout << "  solve3x3LastLayerCornerPermutation\n";
		solve3x3LastLayerCornerPermutation();
		std::cout << "  solve3x3LastLayerEdgePermutation\n";
		solve3x3LastLayerEdgePermutation();
		std::cout << "\n";

		return true;
	}

	void printRow(std::ostream& s, Face* face, int row) const {
		for (int col = 0; col < CUBE_SIZE; ++col) {
			s << face->cface[row][col].color << ' ';
		}
	}

	void printRowPos(std::ostream& s, Face* face, int row) const {
		int w = (CUBE_SIZE > 3) ? 2 : 1;
		for (int col = 0; col < CUBE_SIZE; ++col) {
			s << face->cface[row][col].rot << face->cface[row][col].color << std::setw(w) << face->cface[row][col].pos << ' ';
		}
	}

	void print(std::ostream& s) const {
		std::string spacing(CUBE_SIZE * 2 + 1, ' ');
		s << spacing << face[UP]->faceColor() << ' ' << face[UP]->m_rotation << "\n";
		for (int row = 0; row < CUBE_SIZE; ++row) {
			s << spacing;
			printRow(s, face[UP], row);
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
		s << spacing << face[DOWN]->faceColor() << ' ' << face[DOWN]->m_rotation << "\n";
		for (int row = 0; row < CUBE_SIZE; ++row) {
			s << spacing;
			printRow(s, face[DOWN], row);
			s << '\n';
		}
		s << '\n';
	}

	void printPos(std::ostream& s) const {
		int w = (CUBE_SIZE > 3) ? 2 : 1;
		std::string spacing(CUBE_SIZE * (2 + w + 1) + 1, ' ');
		s << spacing << face[UP]->faceColor() << ' ' << face[UP]->m_rotation << "\n";
		for (int row = 0; row < CUBE_SIZE; ++row) {
			s << spacing;
			printRowPos(s, face[UP], row);
			s << '\n';
		}
		s << '\n';
		s << face[LEFT]->faceColor() << ' ' << face[LEFT]->m_rotation << std::string((CUBE_SIZE * (2 + w + 1) + 1) - 3, ' ');
		s << face[FRONT]->faceColor() << ' ' << face[FRONT]->m_rotation << std::string((CUBE_SIZE * (2 + w + 1) + 1) - 3, ' ');
		s << face[RIGHT]->faceColor() << ' ' << face[RIGHT]->m_rotation << std::string((CUBE_SIZE * (2 + w + 1) + 1) - 3, ' ');
		s << face[BACK]->faceColor() << ' ' << face[BACK]->m_rotation << "\n";
		for (int row = 0; row < CUBE_SIZE; ++row) {
			printRowPos(s, face[LEFT], row);
			s << ' ';
			printRowPos(s, face[FRONT], row);
			s << ' ';
			printRowPos(s, face[RIGHT], row);
			s << ' ';
			printRowPos(s, face[BACK], row);
			s << '\n';
		}
		s << '\n';
		s << spacing << face[DOWN]->faceColor() << ' ' << face[DOWN]->m_rotation << "\n";
		for (int row = 0; row < CUBE_SIZE; ++row) {
			s << spacing;
			printRowPos(s, face[DOWN], row);
			s << '\n';
		}
		s << '\n';
	}

	Face* face[6];
	const int CENTER = CUBE_SIZE / 2;
	std::ostream* m_con;
};
