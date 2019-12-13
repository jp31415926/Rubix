#pragma once
#include <iostream>
#include <ostream>
#include <algorithm> // std::swap
#include "Cubelet.h"

template<int dim = 5>
class Face {

public:
	const int CENTER = dim / 2;
	Cubelet cface[dim][dim];
	int faceColor; // color that this side should be

	Face() {
		initColor(0);
	};

	void initColor(int color) {
		for (int row = dim; row--;) {
			for (int col = dim; col--;) {
				cface[row][col].color = color;
				cface[row][col].pos = row * dim + col;
			}
		}
		faceColor = color;
	}

	int centerColor() const {
		return faceColor;
	}

	bool isSolved() const {
		for (int row = dim; row--;) {
			for (int col = dim; col--;) {
				if ((cface[row][col].color) != faceColor) {
					return false;
				}
			}
		}
		return true;
	}

	bool isCenterSolved() const {
		for (int row = 1; row < dim - 1; ++row) {
			for (int col = 1; col < dim - 1; ++col) {
				if ((cface[row][col].color) != faceColor) {
					return false;
				}
			}
		}
		return true;
	}

	bool checkRangeColor(int startCol, int startRow, int endCol, int endRow) {
		for (int r = startRow; r < endRow; ++r) {
			for (int c = startCol; c < endCol; ++c) {
				if (cface[r][c].color != faceColor)
					return false;
			}
		}
		return true;
	}

	// searches for cubelet with given color at the location given, and the other
	// 3 locations that can be rotated there
	// returns 0 if not found, or 1-4 to indicate rotation required
	// rotate clockwise n-1 times
	int findCubeletWithRotate(int row, int col, int color) {
		for (int r = 1; r < 4; ++r) {
			if (cface[row][col].color == color) {
				return r;
			}
			rotateCW();
		}
	}

	/// Rotate front face clockwise
	void rotateCW() {

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
		// 2. rotate edges (dim-2 * 2)
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

		for (int start = 0, end = dim - 1; start != end; ++start, --end) {
			Cubelet::rotate4(cface[start][start], cface[start][end], cface[end][end], cface[end][start]);
			for (int x = start + 1; x <= end - 1; ++x) {
				Cubelet::rotate4(cface[start][x], cface[x][end], cface[end][end + start - x], cface[end + start - x][start]);
			}
		}
	}

	/// Rotate front face counter-clockwise
	void rotateCCW() {

		// 00 01 02 03 04      04 14 24 34 44
		// 10 11 12 13 14      03 13 23 33 43
		// 20 21 22 23 24  --> 02 12 22 32 42
		// 30 31 32 33 34      01 11 21 31 41
		// 40 41 42 43 44      00 10 20 30 40

		for (int start = 0, end = dim - 1; start != end; ++start, --end) {
			Cubelet::rotate4(cface[start][start], cface[end][start], cface[end][end], cface[start][end]);
			for (int x = start + 1; x <= end - 1; ++x) {
				Cubelet::rotate4(cface[start][x], cface[end + start - x][start], cface[end][x], cface[end + start - x][end]);
			}
		}
	}

	/// Rotate front face twice (direction doesn't matter)
	void rotateTwice() {

		// 00 01 02 03 04      44 43 42 41 40
		// 10 11 12 13 14      34 33 32 31 30
		// 20 21 22 23 24  --> 24 23 22 21 20
		// 30 31 32 33 34      14 13 12 11 10
		// 40 41 42 43 44      04 03 02 01 00

		for (int start = 0, end = dim - 1; start != end; ++start, --end) {
			std::swap(cface[start][start], cface[end][end]);
			std::swap(cface[end][start], cface[start][end]);
			for (int x = start + 1; x <= end - 1; ++x) {
				std::swap(cface[start][x], cface[end][end + start - x]);
				std::swap(cface[end + start - x][start], cface[x][end]);
			}
		}
	}

	void print(std::ostream& s) const {
		for (int row = 0; row < dim; ++row) {
			for (int col = 0; col < dim; ++col) {
				//s << x << y << ':' << cface[x][y].color << ' ';
				s << cface[row][col].color * 100 + cface[row][col].pos << ' ';
			}
			s << '\n';
		}
	}

};
