
#include <algorithm> // std::swap
#include <iomanip> // std::setw
#include <cstdlib>
#include <ctime>
#include "Tokenize.h"
#include "Face.h"
#include "Cube.h"

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

//constexpr auto FRONT = 0;
//constexpr auto UP = 1;
//constexpr auto DOWN = 2;
//constexpr auto LEFT = 3;
//constexpr auto RIGHT = 4;
//constexpr auto BACK = 5;

Cube::Cube(unsigned size)
	:CUBE_SIZE(size)
{
	if ((CUBE_SIZE & 1) == 0) {
		std::cerr << "cube dimension must be odd\n";
		throw std::exception("cube dimension must be odd");
	}
	CENTER = CUBE_SIZE / 2;
	m_con = 0;

	for (int i = 6; i--;) {
		Face* f = new Face(CUBE_SIZE);
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

Cube::~Cube() {
	for (int i = 6; i--;) {
		delete face[i];
	}
}

void Cube::setcon(std::ostream* console) {
	m_con = console;
}

Face& Cube::getFace(unsigned side) const {
	return *face[side];
}

void Cube::rotateCubeUp() {
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "\n";
	if (m_con) print(*m_con);
}

void Cube::rotateCubeDown() {
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "\n";
	if (m_con) print(*m_con);
}

void Cube::rotateCubeLeft() {
	Face* front = face[FRONT];
	face[FRONT] = face[RIGHT];
	face[RIGHT] = face[BACK];
	face[BACK] = face[LEFT];
	face[LEFT] = front;
	face[UP]->rotateCW();
	face[DOWN]->rotateCCW();

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "\n";
	if (m_con) print(*m_con);
}

void Cube::rotateCubeRight() {
	Face* front = face[FRONT];
	face[FRONT] = face[LEFT];
	face[LEFT] = face[BACK];
	face[BACK] = face[RIGHT];
	face[RIGHT] = front;
	face[UP]->rotateCCW();
	face[DOWN]->rotateCW();

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "\n";
	if (m_con) print(*m_con);
}

void Cube::rotateCubeSpinCW() {
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "\n";
	if (m_con) print(*m_con);
}

void Cube::rotateCubeSpinCCW() {
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "\n";
	if (m_con) print(*m_con);
}

void Cube::rotateCubeUp2() {
	// FIXME: optimize
	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "\n";
	rotateCubeUp();
	rotateCubeUp();
}

void Cube::rotateCubeLeft2() {
	// FIXME: optimize
	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "\n";
	rotateCubeLeft();
	rotateCubeLeft();
}

void Cube::rotateCubeSpin2() {
	// FIXME: optimize
	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "\n";
	rotateCubeSpinCW();
	rotateCubeSpinCW();
}

// rotates specified cube face to the front
void Cube::rotateCubeToFront(int side) {
	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << side << ")\n";
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
void Cube::rotateCubeFaceToPos(int side, int pos) {
	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << side << ", " << pos << ")\n";
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
int Cube::findCubeByColor(Cubelet::color_t color) {
	for (int f = 0; f < 6; ++f) {
		if (face[f]->faceColor() == color) {
			return f;
		}
	}
	return -1;
}

// rotates cube to place specified face to the front based on face color
void Cube::rotateCubeToFrontByColor(Cubelet::color_t color) {
	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << color << ")\n";
	rotateCubeToFront(findCubeByColor(color));
}

void Cube::rotateColumnUp(int col) {
	for (int i = CUBE_SIZE; i--;) {
		Cubelet::rotate4(
			face[FRONT]->getC(i, col),
			face[UP]->getC(i, col),
			//face[BACK]->getC(i, col),
			face[BACK]->getC(CUBE_SIZE - 1 - i, CUBE_SIZE - 1 - col),
			face[DOWN]->getC(i, col));
		face[BACK]->getC(CUBE_SIZE - 1 - i, CUBE_SIZE - 1 - col).adjustRotation(2);
		face[DOWN]->getC(i, col).adjustRotation(2);
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << col << ")\n";
	if (m_con) print(*m_con);
}

void Cube::rotateColumnDown(int col) {
	for (int i = CUBE_SIZE; i--;) {
		Cubelet::rotate4(
			face[FRONT]->getC(i, col),
			face[DOWN]->getC(i, col),
			//face[BACK]->getC(i, col),
			face[BACK]->getC(CUBE_SIZE - 1 - i, CUBE_SIZE - 1 - col),
			face[UP]->getC(i, col));
		face[BACK]->getC(CUBE_SIZE - 1 - i, CUBE_SIZE - 1 - col).adjustRotation(2);
		face[UP]->getC(i, col).adjustRotation(2);
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << col << ")\n";
	if (m_con) print(*m_con);
}

void Cube::rotateColumnTwice(int col) {
	for (int i = CUBE_SIZE; i--;) {
		std::swap(
			face[FRONT]->getC(i, col),
			face[BACK]->getC(CUBE_SIZE - 1 - i, CUBE_SIZE - 1 - col));
		std::swap(
			face[UP]->getC(i, col),
			face[DOWN]->getC(i, col));
		face[BACK]->getC(CUBE_SIZE - 1 - i, CUBE_SIZE - 1 - col).adjustRotation(2);
		face[FRONT]->getC(i, col).adjustRotation(2);
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << col << ")\n";
	if (m_con) print(*m_con);
}

void Cube::rotateRowLeft(int row) {
	for (int i = CUBE_SIZE; i--;) {
		Cubelet::rotate4(
			face[FRONT]->getC(row, i),
			face[LEFT]->getC(row, i),
			face[BACK]->getC(row, i),
			face[RIGHT]->getC(row, i));
	}
	if (row == 0) {
		face[UP]->rotateCW();
	}
	else if (row == CUBE_SIZE - 1) {
		face[DOWN]->rotateCCW();
	}

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << row << ")\n";
	if (m_con) print(*m_con);
}

void Cube::rotateRowRight(int row) {
	for (int i = CUBE_SIZE; i--;) {
		Cubelet::rotate4(
			face[FRONT]->getC(row, i),
			face[RIGHT]->getC(row, i),
			face[BACK]->getC(row, i),
			face[LEFT]->getC(row, i));
	}
	if (row == 0) {
		face[UP]->rotateCCW();
	}
	else if (row == CUBE_SIZE - 1) {
		face[DOWN]->rotateCW();
	}

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << row << ")\n";
	if (m_con) print(*m_con);
}

void Cube::rotateRowTwice(int row) {
	for (int i = CUBE_SIZE; i--;) {
		std::swap(
			face[FRONT]->getC(row, i),
			face[BACK]->getC(row, i));
		std::swap(
			face[RIGHT]->getC(row, i),
			face[LEFT]->getC(row, i));
	}
	if (row == 0) {
		face[UP]->rotateTwice();
	}
	else if (row == CUBE_SIZE - 1) {
		face[DOWN]->rotateTwice();
	}

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << row << ")\n";
	if (m_con) print(*m_con);
}

// rotate slice clockwise (slice=0 is top layer)
void Cube::rotateSliceCW(int slice) {
	// (equvilant to rotateCubeLeft, rotateColumnDown(slice), rotateCubeRight)
	for (int i = CUBE_SIZE; i--;) {
		Cubelet::rotate4(
			face[LEFT]->getC(i, CUBE_SIZE - slice - 1),
			face[UP]->getC(CUBE_SIZE - slice - 1, CUBE_SIZE - i - 1),
			face[RIGHT]->getC(CUBE_SIZE - i - 1, slice),
			face[DOWN]->getC(slice, i));
		face[LEFT]->getC(i, CUBE_SIZE - slice - 1).adjustRotation(1);
		face[UP]->getC(CUBE_SIZE - slice - 1, CUBE_SIZE - i - 1).adjustRotation(1);
		face[RIGHT]->getC(CUBE_SIZE - i - 1, slice).adjustRotation(1);
		face[DOWN]->getC(slice, i).adjustRotation(1);
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << slice << ")\n";
	if (m_con) print(*m_con);
}

// rotate slice counter-clockwise (slice=0 is top layer)
void Cube::rotateSliceCCW(int slice) {
	// (equvilant to rotateCubeLeft, rotateColumnUp(slice), rotateCubeRight)
	for (int i = CUBE_SIZE; i--;) {
		Cubelet::rotate4(
			face[LEFT]->getC(i, CUBE_SIZE - slice - 1),
			face[DOWN]->getC(slice, i),
			face[RIGHT]->getC(CUBE_SIZE - i - 1, slice),
			face[UP]->getC(CUBE_SIZE - slice - 1, CUBE_SIZE - i - 1));
		face[LEFT]->getC(i, CUBE_SIZE - slice - 1).adjustRotation(-1);
		face[UP]->getC(CUBE_SIZE - slice - 1, CUBE_SIZE - i - 1).adjustRotation(-1);
		face[RIGHT]->getC(CUBE_SIZE - i - 1, slice).adjustRotation(-1);
		face[DOWN]->getC(slice, i).adjustRotation(-1);
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << slice << ")\n";
	if (m_con) print(*m_con);
}

// rotate slice twice (slice=0 is top layer)
void Cube::rotateSliceTwice(int slice) {
	// (equvilant to rotateCubeLeft, rotateColumnTwice(slice), rotateCubeRight)
	for (int i = CUBE_SIZE; i--;) {
		std::swap(
			face[LEFT]->getC(i, CUBE_SIZE - slice - 1),
			face[RIGHT]->getC(CUBE_SIZE - i - 1, slice));
		std::swap(
			face[UP]->getC(CUBE_SIZE - slice - 1, CUBE_SIZE - i - 1),
			face[DOWN]->getC(slice, i));
		face[LEFT]->getC(i, CUBE_SIZE - slice - 1).adjustRotation(2);
		face[UP]->getC(CUBE_SIZE - slice - 1, CUBE_SIZE - i - 1).adjustRotation(2);
		face[RIGHT]->getC(CUBE_SIZE - i - 1, slice).adjustRotation(2);
		face[DOWN]->getC(slice, i).adjustRotation(2);
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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << slice << ")\n";
	if (m_con) print(*m_con);
}

// rotate the specified face clockwise
void Cube::rotateFaceCW(int side) {
	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << side << ")\n";
	switch (side) {
	case FRONT:
		rotateSliceCW(0); // U
		break;
	case BACK:
		rotateSliceCW(CUBE_SIZE - 1); // D'
		break;
	case UP:
		rotateRowLeft(0); // B
		break;
	case DOWN:
		rotateRowRight(CUBE_SIZE - 1); // F'
		break;
	case LEFT:
		rotateColumnDown(0); // L
		break;
	case RIGHT:
		rotateColumnUp(CUBE_SIZE - 1); // R
		break;
	}
}

// rotate front slice to the rotation specified
void Cube::restoreFrontRotation(int rot) {
	// rot = new rotation
	// faceRotation() = current rotation
	if (m_con)*m_con << "Cube::" << __FUNCTION__ << "(" << rot << ") (was " << face[FRONT]->faceRotation() << ")\n";
	int delta = rot - face[FRONT]->faceRotation();
	while (delta < -3) {
		delta += 4;
	}
	while (delta > 3) {
		delta -= 4;
	}
	switch (rot - face[FRONT]->faceRotation()) {
	case 0:
		break;
	case 1:
	case -3:
		rotateSliceCW(0); // U
		break;
	case 2:
	case -2:
		rotateSliceTwice(0); // U2
		break;
	case 3:
	case -1:
		rotateSliceCCW(0); // U'
		break;
	}
}

// repeatedly and randomly call various move functions to scramble the cube
void Cube::scramble(int iterations, bool limitTo3x3) {
	if (m_con)*m_con << "Cube::" << __FUNCTION__ << " STARTED\n";
	int layer;

	//std::srand((unsigned)std::time(nullptr));
	std::srand(0);

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

	if (m_con)*m_con << "Cube::" << __FUNCTION__ << " COMPLETE\n";
}

// Is the cube solved?
bool Cube::isSolved() const {
	for (int f = 6; f--;) {
		if (!face[f]->isSolved()) {
			return false;
		}
	}
	return true;
}

// searches for an unsolved center and returns face index
// returns -1 if none are found
int Cube::findUnsolvedCenter() {
	for (int f = 6; f--;) {
		if (!face[f]->isCenterSolved()) {
			return f;
		}
	}
	return -1;
}

// searches for an unsolved center (excluding the front and the specified position) and returns face index
// returns -1 if none are found
int Cube::findUnsolvedCenterExcludingPosAndFront(int pos) {
	for (int f = 1; f < 6; ++f) {
		if ((f != pos) && !face[f]->isSolved()) {
			return f;
		}
	}
	return -1;
}

// if the specified face is solved or the specified color, rotate cube until it is not
// returns true if successful, or false if not
bool Cube::rotateUnsolvedAdjacentToPos(Cubelet::color_t excludeColor, int pos) {
	for (int i = 4; i--;) {
		if ((face[pos]->faceColor() != excludeColor) && !face[pos]->isCenterSolved()) {
			return true;
		}
		rotateCubeSpinCW();
		rotateSliceCCW(0); // U'
	}
	return false;
}

// returns number of unsolved centers
unsigned Cube::countUnsolvedCenters() {
	int count = 0;
	for (int f = 6; f--;) {
		if (!face[f]->isSolved()) {
			++count;
		}
	}
	return count;
}

// 00 01 02 03 04 05 06
// 10 11 12 13 14 15 16
// 20 21 22 23 24 25 26
// 30 31 32 33 34 35 36
// 40 41 42 43 44 45 46
// 50 51 52 53 54 55 56
// 60 61 62 63 64 65 66


// move cubelet(s) to form part 1 of center
// this part is always center column, but can be many rows (from top to bottom edge, not inclusive)
// 41-53 cubelets on a 7x7
bool Cube::solveFaceCenterPart1() {
	int timeout = 20;
	unsigned start = 1;
	unsigned end = CUBE_SIZE - 2;
	Cubelet::color_t color = face[FRONT]->faceColor();
	unsigned rotation = face[FRONT]->faceRotation();

	for (unsigned row = start; row <= end; ++row) {
		if (timeout-- == 0) break;
		// is cubelet the color we want?
		if (face[FRONT]->getColor(row, CENTER) != color) {
			// find a cubelet the correct color and in the correct position and move it to here
			// search all the faces
			bool found = false;
			// for (int f = 6; f--;)
			for (unsigned f = 0; f < 6; ++f) {
				// rotate each face up to 4 times
				for (unsigned s = 4; s--;) {
					if ((face[f]->getColor(row, CENTER) != color)
						// special case where we find parts of the column we have already built
					|| ((row > CENTER) && (f == FRONT) && (s == 1))) {
						rotateFaceCW(f);
						// turn to that face, rotate the face, then move back.
						//rotateCubeToFront(f);
						//rotateSliceCW(0); // U
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
							rotateSliceCCW(0); // U'
							rotateSliceCW(CUBE_SIZE - 1); // D'
							rotateColumnTwice(row);
							rotateSliceCW(0); // U
							rotateColumnTwice(row);
							break;
						case UP:
							rotateSliceCCW(0); // U'
							rotateRowRight(0); // B' // B'
							rotateColumnDown(row);
							rotateSliceCW(0); // U
							rotateColumnUp(row);
							break;
						case DOWN:
							rotateSliceCCW(0); // U'
							rotateRowLeft(0); // B
							rotateColumnUp(row);
							rotateSliceCW(0); // U
							rotateColumnDown(row);
							break;
						case LEFT:
							rotateRowRight(row);
							rotateSliceCCW(0); // U'
							rotateRowLeft(row);
							rotateSliceCW(0); // U
							break;
						case RIGHT:
							rotateRowLeft(row);
							rotateSliceCCW(0); // U'
							rotateRowRight(row);
							rotateSliceCW(0); // U
							break;
						}
						break;
					}
				}
				if (found) break;
			}
		}
	}

	return timeout != 0;
}

bool Cube::solveFaceCenterPart2() {
	int timeout = 20;
	unsigned start = 1;
	unsigned end = CUBE_SIZE - 2;
	unsigned col;
	unsigned coll = CENTER - 1;
	unsigned colr = CENTER + 1;
	Cubelet::color_t origColor = face[FRONT]->faceColor();
	unsigned origRotation = face[FRONT]->faceRotation();
	unsigned rotation = origRotation;

	// for each column in part 2 & 3...
	for (unsigned colcount = 1; colcount <= CUBE_SIZE - 2; ++colcount) {
		if ((colcount & 1) == 1) {
			col = coll--;
		}
		else {
			col = colr++;
		}

		if (timeout-- == 0) break;
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
			for (unsigned row = start; row <= end; ++row) {
				if (face[FRONT]->getColor(row, col) != origColor) {
					// find a cubelet the correct color and in the correct position and move it to here
					// search all the faces
					bool found = false;
					// for (int f = 6; f--;)
					for (unsigned f = 0; f < 6; ++f) {
						// FIXME: for now, don't search for blocks on the face we are trying to solve.
						// (need to make sure we don't take blocks from the parts that we have already solved.)
						if (face[f]->faceColor() == origColor) {
							continue;
						}
						// rotate each face up to 4 times
						for (int s = 4; s--;) {
							if (face[f]->getColor(row, col) != origColor) {
								rotateFaceCW(f);
								// turn to that face, rotate the face, then move back.
								//Cubelet::color_t saveColor = face[FRONT]->faceColor();
								//rotateCubeToFront(f);
								//rotateSliceCW(0); // U
								//rotateCubeToFrontByColor(saveColor);
							}
							else {
								// found a match! Now move it to the working face
								found = true;
								switch (f) {
								case BACK:
									// I don't know what this part is for
									//if (row == CENTER) {
									//	rotateColumnTwice(col);
									//	performAlgorithm("U");
									//	//rotateSliceCW(0); // U
									//	rotateColumnTwice(col);
									//	performAlgorithm("U'");
									//	//rotateSliceCCW(0); // U'
									//}
									//else {
								  {
										rotateRowTwice(row);
										if (col > CENTER) {
											performAlgorithm("U'");
											//rotateSliceCCW(0); // U'
										}
										else {
											performAlgorithm("U");
											//rotateSliceCW(0); // U
										}
										rotateRowTwice(row);
										if (col > CENTER) {
											performAlgorithm("U");
											//rotateSliceCW(0); // U
										}
										else {
											performAlgorithm("U'");
											//rotateSliceCCW(0); // U'
										}
									}
									break;

								case DOWN:
									// spin and then do left
									rotateCubeSpinCW();
									performAlgorithm("U'");
									//rotateSliceCCW(0); // U'
									rotateColumnUp(0);
									// YES, I want to drop down to LEFT
								case LEFT:
									if (row == CENTER) {
										performAlgorithm("U L");
										//rotateSliceCW(0); // U
										//rotateColumnDown(0); // L
										rotateRowRight(col);
										performAlgorithm("U'");
										//rotateSliceCCW(0); // U'
										rotateRowLeft(col);
									}
									else {
										rotateRowRight(row);
										if (col > CENTER) {
											performAlgorithm("U'");
										}
										else {
											performAlgorithm("U");
										}
										rotateRowLeft(row);
										if (col > CENTER) {
											performAlgorithm("U");
										}
										else {
											performAlgorithm("U'");
										}
									}
									break;
								case FRONT:
									if (row == start) {
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
										//		rotateSliceCW(0); // U
										//	}
										//	else {
										//		rotateSliceCCW(0); // U'
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
									performAlgorithm("U' R'");
									//rotateColumnDown(CUBE_SIZE - 1); // R'
								// YES, I want to drop down to RIGHT
								case RIGHT:
									if (row == start) {
										performAlgorithm("U R");
										//rotateColumnUp(CUBE_SIZE - 1); // R
										rotateRowLeft(col);
										performAlgorithm("U'");
										rotateRowRight(col);
									}
									else {
										rotateRowLeft(row);
										if (col < CENTER) {
											performAlgorithm("U'");
										}
										else {
											performAlgorithm("U");
										}
										rotateRowRight(row);
										if (col < CENTER) {
											performAlgorithm("U");
										}
										else {
											performAlgorithm("U'");
										}
									}
									break;
								}
								if (row == start) {
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
				rotateSliceTwice(0); // U2
				rotateColumnTwice(col);
				rotateSliceTwice(0); // U2
				break;
			case LEFT:
				// spin and then do top
				rotateCubeSpinCW();
				performAlgorithm("U'");
				//rotateSliceCCW(0); // U'
				rotateRowRight(0); // B'
				// YES, I want to drop down to UP
			case UP:
				rotateColumnDown(col);
				if (col > CENTER) {
					performAlgorithm("U");
					//rotateSliceCW(0); // U
				}
				else {
					performAlgorithm("U'");
					//rotateSliceCCW(0); // U'
				}
				rotateColumnUp(col);
				if (col > CENTER) {
					performAlgorithm("U'");
					//rotateSliceCCW(0); // U'
				}
				else {
					performAlgorithm("U");
					//rotateSliceCW(0); // U
				}
				break;
			case RIGHT:
				// spin and then do bottom
				rotateCubeSpinCW();
				performAlgorithm("U'");
				//rotateSliceCCW(0); // U'
				rotateRowLeft(CUBE_SIZE - 1);
				// YES, I want to drop down to DOWN
			case DOWN:
				rotateColumnUp(col);
				if (col > CENTER) {
					performAlgorithm("U");
					//rotateSliceCW(0); // U
				}
				else {
					performAlgorithm("U'");
					//rotateSliceCCW(0); // U'
				}
				rotateColumnDown(col);
				if (col > CENTER) {
					performAlgorithm("U'");
					//rotateSliceCCW(0); // U'
				}
				else {
					performAlgorithm("U");
					//rotateSliceCW(0); // U
				}
				break;
			}

		}
	}
	//restoreFrontRotation(origRotation);
	return timeout != 0;
}

bool Cube::solveFaceCenterPart3() {

	return true;
}

bool Cube::solveFinal2Centers() {
	return true;
}

// center parts for 7x7 example:
// part 1: 43-53
// part 2: 44-55
// part 3: 41-52
// part 4: 11-25

// move cubelet(s) to form part 1 of center
// this part is always 1 column, but can be many rows (from center to edge, not inclusive)
bool Cube::solveFaceCenter() {
	bool result;
	result = solveFaceCenterPart1();
	if (!result) {
		if (m_con)*m_con << "solveFaceCenterPart1() FAILED!\n";
		if (m_con) print(*m_con);
		return false;
	}
	
	result = solveFaceCenterPart2();
	if (!result) {
		if (m_con)*m_con << "solveFaceCenterPart2() FAILED!\n";
		if (m_con) print(*m_con);
		return false;
	}

	result = solveFaceCenterPart3();
	if (!result) {
		if (m_con)*m_con << "solveFaceCenterPart3() FAILED!\n";
		if (m_con) print(*m_con);
		return false;
	}

	solveFaceCenterPart2();

	//solveFaceCenterPart3();

	//solveFaceCenterPart4();

	return true;
}

// solve the front face center
bool Cube::solveFaceCenters() {
	bool result = false;
	while (countUnsolvedCenters() > 2) {
		// find an unsolved face center
		int f = findUnsolvedCenter();

		// if there are none, get out
		if (f == -1) {
			break;
		}

		// bring unsolved face to front
		rotateCubeToFront(f);

		// do steps to solve the center of current face
		result = solveFaceCenter();
		break;//debugging
	}
	if (result && (countUnsolvedCenters() == 2)) {
		// find an unsolved face center
		int f = findUnsolvedCenter();
		result = solveFinal2Centers();
	}

	return result;
}

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
void Cube::performAlgorithm(const std::string& s) {
	if (m_con)*m_con << "performAlgorithm(" << s << ")\n";
	std::vector<std::string> tokens(tokenize(s, " \t\n\r()"));
	for (std::string move : tokens) {
		if (m_con)*m_con << "performAlgorithm move " << move << "\n";
		int width = 1;
		bool reverse = false;
		int interations = 1;
		if (move[0] == '3') {
			width = 3;
			move.erase(0, 1);
		}
		if (move[move.size() - 1] == 'w') {
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
		else if (move == "x") {
			for (int i = interations; i--;) {
				if (reverse) {
					rotateCubeDown();
				}
				else {
					rotateCubeUp();
				}
			}
		}
		else if (move == "y") {
			for (int i = interations; i--;) {
				if (reverse) {
					rotateCubeSpinCCW();
				}
				else {
					rotateCubeSpinCW();
				}
			}
		}
		else if (move == "z") {
			for (int i = interations; i--;) {
				if (reverse) {
					rotateCubeLeft();
				}
				else {
					rotateCubeRight();
				}
			}
		}
		else {
			// unknown move... ignore it
		}
	}
}

bool Cube::isFrontCrossSolved() {
	Cubelet::color_t frontColor = face[FRONT]->faceColor();
	bool solved = (frontColor == face[FRONT]->getTopMiddleColor())
		&& (frontColor == face[FRONT]->getMiddleLeftColor())
		&& (frontColor == face[FRONT]->getMiddleRightColor())
		&& (frontColor == face[FRONT]->getBottomMiddleColor())
		&& (face[UP]->faceColor() == face[UP]->getBottomMiddleColor())
		&& (face[LEFT]->faceColor() == face[LEFT]->getMiddleRightColor())
		&& (face[RIGHT]->faceColor() == face[RIGHT]->getMiddleLeftColor())
		&& (face[DOWN]->faceColor() == face[DOWN]->getTopMiddleColor())
		;
	return solved;
}

// Solve the 2st later cross on FRONT layer
bool Cube::solve3x3FirstLayerCross() {
	// start at top center of face and rotate clockwise
	Cubelet::color_t frontColor = face[FRONT]->faceColor();
	Cubelet::color_t frontBottomEdgeColor;
	Cubelet::color_t downTopEdgeColor;
	Cubelet::color_t downLeftEdgeColor;
	Cubelet::color_t leftBottomEdgeColor;
	Cubelet::color_t downRightEdgeColor;
	Cubelet::color_t rightBottomEdgeColor;
	Cubelet::color_t downBottomEdgeColor;
	Cubelet::color_t backBottomEdgeColor;
	Cubelet::color_t downColor;
	int timeout = 10;

	// may have to make multiple passes
	while (!isFrontCrossSolved() && --timeout) {
		int rot = face[FRONT]->faceRotation();
		bool found = false;

		downColor = face[DOWN]->faceColor();
		if (m_con)*m_con << "Looking for " << frontColor << downColor << " edge\n";

		// search 4 edges on top
		for (int s = 4; s--;) {
			frontBottomEdgeColor = face[FRONT]->getBottomMiddleColor();
			downTopEdgeColor = face[DOWN]->getTopMiddleColor();

			if (m_con) *m_con << "  checking " << frontBottomEdgeColor << downTopEdgeColor << " already solved\n";
			// is this edge peice solved?
			if ((frontBottomEdgeColor == frontColor) && (downTopEdgeColor == downColor)) {
				if (rot != face[FRONT]->faceRotation()) {
					// move down, rotate, them move back
					performAlgorithm("F'");
					restoreFrontRotation(rot);
					performAlgorithm("F");
				}
				found = true;
				break;
			}

			if (m_con) *m_con << "  checking " << downTopEdgeColor << frontBottomEdgeColor << " top reversed\n";
			// check if piece is on top, but needs to be flipped
			if (!found && (frontBottomEdgeColor == downColor) &&
				(downTopEdgeColor == frontColor)) {
				// F U' R U
				performAlgorithm("F");
				restoreFrontRotation(rot);
				performAlgorithm("U' R U");
				found = true;
				break;
			}

			performAlgorithm("U");
		}

		if (!found) {
			for (int s = 0; s < 4; s++) {
				// check middle for the edge piece we are looking for (on the DOWN side)
				downLeftEdgeColor = face[DOWN]->getMiddleLeftColor();
				leftBottomEdgeColor = face[LEFT]->getBottomMiddleColor();
				if (m_con)*m_con << "  checking " << leftBottomEdgeColor << downLeftEdgeColor << " left\n";
				// check if left center of down side matches
				if ((downLeftEdgeColor == downColor) && (leftBottomEdgeColor == frontColor)) {
					restoreFrontRotation(rot);
					performAlgorithm("F");
					found = true;
					break;
				}

				downRightEdgeColor = face[DOWN]->getMiddleRightColor();
				rightBottomEdgeColor = face[RIGHT]->getBottomMiddleColor();
				if (m_con)*m_con << "  checking " << rightBottomEdgeColor << downRightEdgeColor << " right\n";
				// check if right center of down side matches
				if ((downRightEdgeColor == downColor) && (rightBottomEdgeColor == frontColor)) {
					restoreFrontRotation(rot);
					performAlgorithm("F'");
					found = true;
					break;
				}

				// check bottom for the edge piece we are looking for (on the down side)
				downBottomEdgeColor = face[DOWN]->getBottomMiddleColor();
				backBottomEdgeColor = face[BACK]->getBottomMiddleColor();
				if (m_con)*m_con << "  checking " << backBottomEdgeColor << downBottomEdgeColor << " bottom\n";
				// check if right center of down side matches
				if ((downBottomEdgeColor == downColor) && (backBottomEdgeColor == frontColor)) {
					restoreFrontRotation(rot);
					performAlgorithm("F2");
					found = true;
					break;
				}

				if (m_con)*m_con << "  checking " << downBottomEdgeColor << backBottomEdgeColor << " bottom reversed\n";
				// check if bottom peice needs to be flipped
				if ((downBottomEdgeColor == frontColor) && (backBottomEdgeColor == downColor)) {
					restoreFrontRotation(rot);
					performAlgorithm("F' U' R U");
					found = true;
					break;
				}

				// not solved yet - rotate cube except FRONT
				rotateCubeSpinCW();
				rotateSliceCCW(0); // U'
			}
		}

		if (found) {
			if (m_con)*m_con << "  solved!\n";
			while (downColor != face[DOWN]->faceColor()) {
				rotateCubeSpinCW();
				rotateSliceCCW(0); // U'
			}
		}
		// rotate cube
		rotateCubeSpinCW();
	}
	return timeout != 0;
}

bool Cube::isFirstLayerSolved() {
	Cubelet::color_t frontColor = face[FRONT]->faceColor();
	Cubelet::color_t upColor = face[UP]->faceColor();
	Cubelet::color_t downColor = face[DOWN]->faceColor();
	Cubelet::color_t leftColor = face[LEFT]->faceColor();
	Cubelet::color_t rightColor = face[RIGHT]->faceColor();
	bool solved = face[FRONT]->isSolved()
		&& (upColor == face[UP]->getBottomLeftColor())
		&& (upColor == face[UP]->getBottomMiddleColor())
		&& (upColor == face[UP]->getBottomRightColor())
		&& (leftColor == face[LEFT]->getTopRightColor())
		&& (leftColor == face[LEFT]->getMiddleRightColor())
		&& (leftColor == face[LEFT]->getBottomRightColor())
		&& (rightColor == face[RIGHT]->getTopLeftColor())
		&& (rightColor == face[RIGHT]->getMiddleLeftColor())
		&& (rightColor == face[RIGHT]->getBottomLeftColor())
		&& (downColor == face[DOWN]->getTopLeftColor())
		&& (downColor == face[DOWN]->getTopMiddleColor())
		&& (downColor == face[DOWN]->getTopRightColor())
		;
	return solved;
}

bool Cube::solve3x3FirstLayerCorners() {
	int timeout = 10;
	bool found = false;

	while (!isFirstLayerSolved() && --timeout) {
		found = false;
		Cubelet::color_t frontColor = face[FRONT]->faceColor();
		Cubelet::color_t downColor = face[DOWN]->faceColor();
		Cubelet::color_t rightColor = face[RIGHT]->faceColor();
		Cubelet::color_t frontBottomRightCornerColor;
		Cubelet::color_t downTopRightCornerColor;
		Cubelet::color_t rightBottomLeftCornerColor;
		Cubelet::color_t downBottomRightCornerColor;
		Cubelet::color_t rightBottomRightCornerColor;
		Cubelet::color_t backBottomLeftCornerColor;
		int rot = face[FRONT]->faceRotation();

		if (m_con)*m_con << "Looking for match to " << frontColor << downColor << rightColor << " corner\n";

		// look at the top 4 corners
		for (int s = 4; s--;) {
			frontBottomRightCornerColor = face[FRONT]->getBottomRightColor();
			downTopRightCornerColor = face[DOWN]->getTopRightColor();
			rightBottomLeftCornerColor = face[RIGHT]->getBottomLeftColor();
			//int rot2;

			if (m_con)*m_con << "  checking " << frontBottomRightCornerColor << downTopRightCornerColor << rightBottomLeftCornerColor << "\n";
			if ((frontColor == frontBottomRightCornerColor) &&
				(downColor == downTopRightCornerColor) &&
				(rightColor == rightBottomLeftCornerColor)) {
				if (s != 3) {
					//rot2 = face[FRONT]->faceRotation();
					performAlgorithm("R' D' R D");
					//restoreFrontRotation(rot);
					while (face[LEFT]->faceColor() != downColor) {
						rotateCubeSpinCW();
						performAlgorithm("D");
					}
					performAlgorithm("D'");
					performAlgorithm("L D L' D'");
					//restoreFrontRotation(rot2);
				}
				found = true;
				break;
			}
			if (m_con)*m_con << "  checking " << downTopRightCornerColor << rightBottomLeftCornerColor << frontBottomRightCornerColor << "\n";
			// check if correct corner, but wrong rotation, rotate
			if ((frontColor == downTopRightCornerColor) &&
				(downColor == rightBottomLeftCornerColor) &&
				(rightColor == frontBottomRightCornerColor)) {
				rotateCubeSpinCW();
				performAlgorithm("L D L' D'");
				while (face[LEFT]->faceColor() != downColor) {
					rotateCubeSpinCW();
					performAlgorithm("D");
				}
				performAlgorithm("L D L' D'");
				rotateCubeSpinCCW();
				found = true;
				break;
			}

			if (m_con)*m_con << "  checking " << rightBottomLeftCornerColor << frontBottomRightCornerColor << downTopRightCornerColor << "\n";
			if ((frontColor == rightBottomLeftCornerColor) &&
				(downColor == frontBottomRightCornerColor) &&
				(rightColor == downTopRightCornerColor)) {
				performAlgorithm("R' D' R D");
				while (face[DOWN]->faceColor() != downColor) {
					rotateCubeSpinCW();
					performAlgorithm("D");
				}
				performAlgorithm("R' D' R D");
				found = true;
				break;
			}

			rotateCubeSpinCW();
			//performAlgorithm("U");
		}
		//restoreFrontRotation(rot);

		if (!found) {
			// look at the bottom 4 corners
			for (int s = 4; s--;) {
				frontBottomRightCornerColor = face[FRONT]->getBottomRightColor();
				downTopRightCornerColor = face[DOWN]->getTopRightColor();
				rightBottomLeftCornerColor = face[RIGHT]->getBottomLeftColor();

				downBottomRightCornerColor = face[DOWN]->getBottomRightColor();
				rightBottomRightCornerColor = face[RIGHT]->getBottomRightColor();
				backBottomLeftCornerColor = face[BACK]->getBottomLeftColor();

				if (m_con)*m_con << "  checking " << downBottomRightCornerColor << backBottomLeftCornerColor << rightBottomRightCornerColor << "\n";

				// check down bottom right corner
				if ((frontColor == downBottomRightCornerColor) &&
					(downColor == backBottomLeftCornerColor) &&
					(rightColor == rightBottomRightCornerColor)) {
					rotateCubeSpinCW();
					performAlgorithm("L D L' D'");
					rotateCubeSpinCCW();
					break;
				}
				if (m_con)*m_con << "  checking " << rightBottomRightCornerColor << downBottomRightCornerColor << backBottomLeftCornerColor << "\n";
				if ((frontColor == rightBottomRightCornerColor) &&
					(downColor == downBottomRightCornerColor) &&
					(rightColor == backBottomLeftCornerColor)) {
					performAlgorithm("R' D' R D");
					break;
				}
				if (m_con)*m_con << "  checking " << backBottomLeftCornerColor << rightBottomRightCornerColor << downBottomRightCornerColor << "\n";
				if ((frontColor == backBottomLeftCornerColor) &&
					(downColor == rightBottomRightCornerColor) &&
					(rightColor == downBottomRightCornerColor)) {
					performAlgorithm("R' D' R D");
					performAlgorithm("R' D' R D");
					performAlgorithm("R' D' R D");
					break;
				}
				rotateSliceCW(CUBE_SIZE - 1); // D' // D
			}
		}
		rotateCubeSpinCW();
	}

	//while (face[DOWN]->getTopMiddleColor() != face[DOWN]->faceColor()) {
	//	rotateCubeSpinCW();
	//	rotateSliceCCW(0); // U'
	//}

	return timeout != 0;
}

bool Cube::isSecondLayerSolved() {
	Cubelet::color_t leftColor = face[LEFT]->faceColor();
	Cubelet::color_t upColor = face[UP]->faceColor();
	Cubelet::color_t rightColor = face[RIGHT]->faceColor();
	Cubelet::color_t downColor = face[DOWN]->faceColor();

	for (int i = CUBE_SIZE; i--;) {
		if ((face[LEFT]->getColor(i, CENTER) != leftColor) ||
			(face[UP]->getColor(CENTER, CUBE_SIZE - i - 1) != upColor) ||
			(face[RIGHT]->getColor(CUBE_SIZE - i - 1, CENTER) != rightColor) ||
			(face[DOWN]->getColor(CENTER, i) != downColor)) {
			return false;
		}
	}
	return true;
}

bool Cube::solve3x3SecondLayer() {
	int timeout = 20;
	bool found = false;
	if (face[FRONT]->isSolved()) {
		rotateCubeLeft2();
	}
	else {
		if (m_con)*m_con << "FRONT is not solved!!!\n";
		return false; // this should not happen if the last step worked
	}
	Cubelet::color_t frontColor = face[FRONT]->faceColor();

	while (!isSecondLayerSolved() && --timeout) {
		found = false;
		Cubelet::color_t downColor = face[DOWN]->faceColor();
		Cubelet::color_t rightColor = face[RIGHT]->faceColor();
		Cubelet::color_t leftColor = face[LEFT]->faceColor();

		Cubelet::color_t downLeftEdgeColor = face[DOWN]->getMiddleLeftColor();
		Cubelet::color_t leftBottomEdgeColor = face[LEFT]->getBottomMiddleColor();

		for (int s = 4; s--;) {
			Cubelet::color_t frontBottomEdgeColor = face[FRONT]->getBottomMiddleColor();
			Cubelet::color_t downTopEdgeColor = face[DOWN]->getTopMiddleColor();
			if (downColor == downTopEdgeColor) {
				if (rightColor == frontBottomEdgeColor) {
					if (m_con)*m_con << "match to right edge\n";
					performAlgorithm("U R U' R' U' F' U F");
					found = true;
					break;
				}
				if (leftColor == frontBottomEdgeColor) {
					if (m_con)*m_con << "match to left edge\n";
					performAlgorithm("U' L' U L U F U' F'");
					found = true;
					break;
				}
			}
			if (downColor == frontBottomEdgeColor) {
				if (rightColor == downTopEdgeColor) {
					if (m_con)*m_con << "match to right edge with flip\n";
					rotateCubeSpinCW();
					performAlgorithm("U'");
					performAlgorithm("U' L' U L U F U' F'");
					found = true;
					break;
				}
				if (leftColor == downTopEdgeColor) {
					if (m_con)*m_con << "match to left edge with flip\n";
					rotateCubeSpinCCW();
					performAlgorithm("U");
					performAlgorithm("U R U' R' U' F' U F");
					found = true;
					break;
				}
			}
			// rotate the top
			performAlgorithm("U");
		}
		if (!found) {
			// if left edge is not solved, bring it up
			if ((downLeftEdgeColor != downColor) || (leftBottomEdgeColor != leftColor)) {
				if (m_con)*m_con << "left edge needs to come up\n";
				performAlgorithm("U' L' U L U F U' F'");
			}
		}
		// rotate the cube
		rotateCubeSpinCW();
	}
	return timeout != 0;
}

void Cube::solve3x3LastLayerCross() {
	Cubelet::color_t frontColor = face[FRONT]->faceColor();
	while (true) {
		int top = face[FRONT]->getTopMiddleColor() == frontColor ? 1 : 0;
		int left = face[FRONT]->getMiddleLeftColor() == frontColor ? 2 : 0;
		int right = face[FRONT]->getMiddleRightColor() == frontColor ? 4 : 0;
		int bottom = face[FRONT]->getBottomMiddleColor() == frontColor ? 8 : 0;

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

void Cube::solve3x3LastLayerCornerOrientation() {
	Cubelet::color_t frontColor = face[FRONT]->faceColor();
	while (!face[FRONT]->isSolved()) {
		int count = 0;
		for (int s = 4; s--;) {
			if (face[FRONT]->getTopLeftColor() == frontColor) {
				++count;
			}
			rotateSliceCW(0); // U
		}
		switch (count) {
		case 0:
			while (face[LEFT]->getTopRightColor() != frontColor) {
				rotateSliceCW(0); // U
			}
			break;
		case 1:
			while (face[FRONT]->getBottomLeftColor() != frontColor) {
				rotateSliceCW(0); // U
			}
			break;
		case 2:
			while (face[DOWN]->getTopLeftColor() != frontColor) {
				rotateSliceCW(0); // U
			}
			break;
		}
		performAlgorithm("R U R' U R U2 R'");
	}
}

bool Cube::areCornersSolved() {
	// see if corners are solved
	Cubelet::color_t frontColor = face[FRONT]->faceColor();
	for (int s = 4; s--;) {
		// corner solved?
		if ((frontColor != face[FRONT]->getBottomRightColor()) ||
			(face[DOWN]->faceColor() != face[DOWN]->getTopRightColor()) ||
			(face[RIGHT]->faceColor() != face[RIGHT]->getBottomLeftColor())) {
			return false;
		}
		rotateCubeSpinCW();
	}
	return true;
}

void Cube::solve3x3LastLayerCornerPermutation() {
	bool found = false;

	while (!areCornersSolved()) {
		for (int s = 4; s--;) {
			if (face[LEFT]->getBottomRightColor() == face[LEFT]->getTopRightColor()) {
				found = true;
				break;
			}
			rotateSliceCW(0); // U
		}
		if (found) {
			while (face[LEFT]->getBottomRightColor() != face[LEFT]->faceColor()) {
				rotateCubeSpinCW();
				rotateSliceCCW(0); // U'
			}
		}
		performAlgorithm("R U R' U' R' F R2 U' R' U' R U R' F'");
	}
}

bool Cube::solve3x3LastLayerEdgePermutation() {
	int timeout = 20;
	while (!isSolved() && --timeout) {
		for (int s = 4; s--;) {
			// find solid bar if it is there
			if (face[UP]->getBottomLeftColor() == face[UP]->getBottomMiddleColor()) {
				break;
			}
			rotateCubeSpinCW();
		}
		performAlgorithm("R U' R U R U R U' R' U' R2");
	}
	return timeout != 0;
}

// This solves any size cube like a 3x3. It assumes all the centers and edges are complete for cubes greater than 3x3.
bool Cube::solve3x3() {
	bool result;
	result = solve3x3FirstLayerCross();
	if (!result) {
		if (m_con)*m_con << "solve3x3FirstLayerCross() FAILED!\n";
		if (m_con) print(*m_con);
		return false;
	}
	result = solve3x3FirstLayerCorners();
	if (!result) {
		if (m_con)*m_con << "solve3x3FirstLayerCorners() FAILED!\n";
		if (m_con) print(*m_con);
		return false;
	}
	result = solve3x3SecondLayer();
	if (!result) {
		if (m_con)*m_con << "solve3x3SecondLayer() FAILED!\n";
		if (m_con) print(*m_con);
		return false;
	}
	solve3x3LastLayerCross();
	solve3x3LastLayerCornerOrientation();
	solve3x3LastLayerCornerPermutation();
	result = solve3x3LastLayerEdgePermutation();
	if (!result) {
		if (m_con)*m_con << "solve3x3LastLayerEdgePermutation() FAILED!\n";
		if (m_con) print(*m_con);
		return false;
	}

	return true;
}

void Cube::printRow(std::ostream& s, Face* face, int row) const {
	for (unsigned col = 0; col < CUBE_SIZE; ++col) {
		s << face->getColor(row, col) << ' ';
	}
}

void Cube::printRowPos(std::ostream& s, Face* face, int row) const {
	int w = (CUBE_SIZE > 3) ? 2 : 1;
	for (unsigned col = 0; col < CUBE_SIZE; ++col) {
		s << face->getC(row, col).rot << face->getColor(row, col) << std::setw(w) << face->getC(row, col).pos << ' ';
	}
}

void Cube::print(std::ostream& s) const {
	std::string spacing(CUBE_SIZE * 2 + 1, ' ');
	s << spacing << face[UP]->faceColor() << ' ' << face[UP]->faceRotation() << "\n";
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
		s << spacing;
		printRow(s, face[UP], row);
		s << '\n';
	}
	s << '\n';
	s << face[LEFT]->faceColor() << ' ' << face[LEFT]->faceRotation() << std::string((CUBE_SIZE * 2 + 1) - 3, ' ');
	s << face[FRONT]->faceColor() << ' ' << face[FRONT]->faceRotation() << std::string((CUBE_SIZE * 2 + 1) - 3, ' ');
	s << face[RIGHT]->faceColor() << ' ' << face[RIGHT]->faceRotation() << std::string((CUBE_SIZE * 2 + 1) - 3, ' ');
	s << face[BACK]->faceColor() << ' ' << face[BACK]->faceRotation() << "\n";
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
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
	s << spacing << face[DOWN]->faceColor() << ' ' << face[DOWN]->faceRotation() << "\n";
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
		s << spacing;
		printRow(s, face[DOWN], row);
		s << '\n';
	}
	s << '\n';
}

void Cube::print2(std::ostream& s) const {
	/* Make a display that looks like this:
							R
		Y                   B
		 +------G B R------+
		 | +----B G G----+ |
		 | | +--W G G--+ | |
		 | | |         | | |
		 R W O  G O O  Y R Y     B R Y
	Y  B W W  O O O  Y Y W  R  R R Y
		 G R W  O O B  O Y B     R W R
		 | | |         | | |
		 | | +--B B Y--+ | |
		 | +----Y B G----+ |
		 +------W G W------+
		R                   R
							W
	*/

	std::string spacing(CUBE_SIZE * 2 + 1, ' ');
	s << std::string(12, ' ') << 'R' << "\n";
	s << "  " << 'Y' << std::string(13 + CUBE_SIZE * 2, ' ') << 'B' << "\n";
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
		s << "   +" << std::string(2 + (CUBE_SIZE - 1 - row) * 2, '-');
		printRow(s, face[UP], row);
		s << std::string(2 + (CUBE_SIZE - 1 - row) * 2, '-') << "+\n";
	}
	s << '\n';
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
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
	s << spacing << face[DOWN]->faceColor() << ' ' << face[DOWN]->faceRotation() << "\n";
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
		s << spacing;
		printRow(s, face[DOWN], row);
		s << '\n';
	}
	s << '\n';
}

void Cube::printPos(std::ostream& s) const {
	std::string::size_type w = (CUBE_SIZE > 3) ? 2 : 1;
	std::string spacing(CUBE_SIZE * (2 + w + 1) + 1, ' ');
	s << spacing << face[UP]->faceColor() << ' ' << face[UP]->faceRotation() << "\n";
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
		s << spacing;
		printRowPos(s, face[UP], row);
		s << '\n';
	}
	s << '\n';
	s << face[LEFT]->faceColor() << ' ' << face[LEFT]->faceRotation() << std::string((CUBE_SIZE * (2 + w + 1) + 1) - 3, ' ');
	s << face[FRONT]->faceColor() << ' ' << face[FRONT]->faceRotation() << std::string((CUBE_SIZE * (2 + w + 1) + 1) - 3, ' ');
	s << face[RIGHT]->faceColor() << ' ' << face[RIGHT]->faceRotation() << std::string((CUBE_SIZE * (2 + w + 1) + 1) - 3, ' ');
	s << face[BACK]->faceColor() << ' ' << face[BACK]->faceRotation() << "\n";
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
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
	s << spacing << face[DOWN]->faceColor() << ' ' << face[DOWN]->faceRotation() << "\n";
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
		s << spacing;
		printRowPos(s, face[DOWN], row);
		s << '\n';
	}
	s << '\n';
}
