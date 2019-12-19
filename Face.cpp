#include "Face.h"

Face::Face(unsigned size)
	:CUBE_SIZE(size)
{
	CENTER = CUBE_SIZE / 2;
	MAX = CUBE_SIZE - 1;
	cface.reserve(CUBE_SIZE);
	cface.resize(CUBE_SIZE);
	for (unsigned row = CUBE_SIZE; row--;) {
		cface[row].reserve(CUBE_SIZE);
		cface[row].resize(CUBE_SIZE);
	}
	initColor(0);
	m_rotation = 0;
};

void Face::initColor(Cubelet::color_t color) {
	for (unsigned row = CUBE_SIZE; row--;) {
		for (unsigned col = CUBE_SIZE; col--;) {
			cface[row][col].color = color;
			cface[row][col].pos = row * CUBE_SIZE + col;
		}
	}
	m_faceColor = color;
}

Cubelet::color_t Face::faceColor() const {
	if (CUBE_SIZE % 2 == 1) {
		return cface[CENTER][CENTER].color;
	}
	return m_faceColor;
}

int Face::faceRotation() const {
	return m_rotation;
}

void Face::adjustRotation(int rot) {
	m_rotation = (m_rotation + rot) & 3;
}

bool Face::isSolved(Cubelet::color_t color) const {
	if (color == -1) {
		color = faceColor();
	}
	for (int row = CUBE_SIZE; row--;) {
		for (int col = CUBE_SIZE; col--;) {
			if ((cface[row][col].color) != color) {
				return false;
			}
		}
	}
	return true;
}

bool Face::isCenterSolved() const {
	for (unsigned row = 1; row < CUBE_SIZE - 1; ++row) {
		for (unsigned col = 1; col < CUBE_SIZE - 1; ++col) {
			if ((cface[row][col].color) != faceColor()) {
				return false;
			}
		}
	}
	return true;
}

bool Face::isRangeSolved(int startRow, int startCol, int endRow, int endCol) const {
	Cubelet::color_t color = faceColor();
	for (int r = startRow; r <= endRow; ++r) {
		for (int c = startCol; c <= endCol; ++c) {
			if (cface[r][c].color != color)
				return false;
		}
	}
	return true;
}

/// Rotate front face clockwise
void Face::rotateCW() {

	// 00 01 02 03 04 05 06      
	// 10 11 12 13 14 15 16      
	// 20 21 22 23 24 25 26      
	// 30 31 32 33 34 35 36  --> 
	// 40 41 42 43 44 45 46      
	// 50 51 52 53 54 55 56      
	// 60 61 62 63 64 65 66      

	// 00 01 02 03 04      40 30 20 10 00
	// 10 11 12 13 14      41 31 21 11 01
	// 20 21 22 23 24  --> 42 32 22 12 02
	// 30 31 32 33 34      43 33 23 13 03
	// 40 41 42 43 44      44 34 24 14 04

	// steps:
	// 1. rotate corners (always 4)
	//   00 -> 04
	//   04 -> 44
	//   44 -> 40
	//   40 -> 00
	// 2. rotate edges (CUBE_SIZE-2 * 2)
	//   01 02 03 -> 14 24 34
	//   14 24 34 -> 43 42 41
	//   43 42 41 -> 30 20 10
	//   30 20 10 -> 01 02 03
	// 3. repeat for inter "corners" and "edges"
	// corners:
	//   11 -> 13
	//   13 -> 33
	//   33 -> 31
	//   31 -> 11
	// edges:
	//   12 -> 23
	//   23 -> 32
	//   32 -> 21
	//   21 -> 12

	for (int start = 0, end = CUBE_SIZE - 1; start != end; ++start, --end) {
		// rotate corners
		Cubelet::rotate4(cface[start][start], cface[start][end], cface[end][end], cface[end][start], 1);
		for (int x = start + 1; x <= end - 1; ++x) {
			// rotate internal cubelets
			Cubelet::rotate4(cface[start][x], cface[x][end], cface[end][end + start - x], cface[end + start - x][start], 1);
		}
		cface[CENTER][CENTER].rot = (cface[CENTER][CENTER].rot + 1) & 3;
	}
	m_rotation = (m_rotation + 1) & 3;
}

/// Rotate front face counter-clockwise
void Face::rotateCCW() {

	// 00 01 02 03 04      04 14 24 34 44
	// 10 11 12 13 14      03 13 23 33 43
	// 20 21 22 23 24  --> 02 12 22 32 42
	// 30 31 32 33 34      01 11 21 31 41
	// 40 41 42 43 44      00 10 20 30 40

	for (int start = 0, end = CUBE_SIZE - 1; start != end; ++start, --end) {
		Cubelet::rotate4(cface[start][start], cface[end][start], cface[end][end], cface[start][end], -1);
		for (int x = start + 1; x <= end - 1; ++x) {
			// Cubelet::rotate4(cface[start][x], cface[end + start - x][start], cface[end][x], cface[end + start - x][end], -1);
			Cubelet::rotate4(cface[start][x], cface[end + start - x][start], cface[end][end + start - x], cface[x][end], -1);
		}
		cface[CENTER][CENTER].rot = (cface[CENTER][CENTER].rot - 1) & 3;
	}
	m_rotation = (m_rotation - 1) & 3;
}

/// Rotate front face twice (direction doesn't matter)
void Face::rotateTwice() {
	for (unsigned start = 0, end = CUBE_SIZE - 1; start != end; ++start, --end) {
		Cubelet::swap(cface[start][start], cface[end][end], 2);
		Cubelet::swap(cface[end][start], cface[start][end], 2);
		for (unsigned x = start + 1; x <= end - 1; ++x) {
			Cubelet::swap(cface[start][x], cface[end][end + start - x], 2);
			Cubelet::swap(cface[end + start - x][start], cface[x][end], 2);
		}
		cface[CENTER][CENTER].rot = (cface[CENTER][CENTER].rot + 2) & 3;
	}
	m_rotation = (m_rotation + 2) & 3;
}

void Face::print(std::ostream& s) const {
	for (unsigned row = 0; row < CUBE_SIZE; ++row) {
		for (unsigned col = 0; col < CUBE_SIZE; ++col) {
			//s << x << y << ':' << cface[x][y].color << ' ';
			s << cface[row][col].color * 100 + cface[row][col].pos << ' ';
		}
		s << '\n';
	}
}
