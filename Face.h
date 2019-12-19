#pragma once
#include <iostream>
#include <ostream>
#include <vector>
#include "Cubelet.h"

class Face {

public:
	Face(unsigned size);

	void initColor(Cubelet::color_t color);

	Cubelet::color_t faceColor() const;

	Cubelet& getC(unsigned row, unsigned col) {
		return cface[row][col];
	}

	Cubelet::color_t getColor(unsigned row, unsigned col) const {
		return cface[row][col].color;
	}

	Cubelet::color_t getTopLeftColor() const {
		return cface[0][0].color;
	}

	Cubelet::color_t getTopRightColor() const {
		return cface[0][MAX].color;
	}

	Cubelet::color_t getBottomLeftColor() const {
		return cface[MAX][0].color;
	}

	Cubelet::color_t getBottomRightColor() const {
		return cface[MAX][MAX].color;
	}

	Cubelet::color_t getTopMiddleColor() const {
		return cface[0][CENTER].color;
	}

	Cubelet::color_t getMiddleLeftColor() const {
		return cface[CENTER][0].color;
	}

	Cubelet::color_t getMiddleRightColor() const {
		return cface[CENTER][MAX].color;
	}

	Cubelet::color_t getMiddleBottomColor() const {
		return cface[MAX][CENTER].color;
	}

	Cubelet::color_t getCenterColor() const {
		return cface[CENTER][CENTER].color;
	}

	int faceRotation() const;

	void adjustRotation(int rot);

	bool isSolved(Cubelet::color_t color = -1) const;

	bool isCenterSolved() const;

	bool isRangeSolved(int startRow, int startCol, int endRow, int endCol) const;

	/// Rotate front face clockwise
	void rotateCW();

	/// Rotate front face counter-clockwise
	void rotateCCW();

	/// Rotate front face twice (direction doesn't matter)
	void rotateTwice();

	void print(std::ostream& s) const;

private:
	std::vector<std::vector<Cubelet>> cface;
	unsigned CUBE_SIZE;
	unsigned MAX;
	unsigned CENTER;
	Cubelet::color_t m_faceColor;
	unsigned m_rotation;
};
