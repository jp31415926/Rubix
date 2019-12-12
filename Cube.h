#pragma once

#include <algorithm> // std::swap
#include <cstdlib>
#include <ctime>
#include "Face.h"

//                           1
//                           00:2 01:2 02:2 03:2 04:2
//                           10:2 11:2 12:2 13:2 14:2
//                           20:2 21:2 22:2 23:2 24:2
//                           30:2 31:2 32:2 33:2 34:2
//                           40:2 41:2 42:2 43:2 44:2
// 3                         0                         4                         5
// 00:4 01:4 02:4 03:4 04:4  00:1 01:1 02:1 03:1 04:1  00:5 01:5 02:5 03:5 04:5  00:6 01:6 02:6 03:6 04:6
// 10:4 11:4 12:4 13:4 14:4  10:1 11:1 12:1 13:1 14:1	 10:5 11:5 12:5 13:5 14:5	 10:6 11:6 12:6 13:6 14:6
// 20:4 21:4 22:4 23:4 24:4  20:1 21:1 22:1 23:1 24:1	 20:5 21:5 22:5 23:5 24:5	 20:6 21:6 22:6 23:6 24:6
// 30:4 31:4 32:4 33:4 34:4  30:1 31:1 32:1 33:1 34:1	 30:5 31:5 32:5 33:5 34:5	 30:6 31:6 32:6 33:6 34:6
// 40:4 41:4 42:4 43:4 44:4  40:1 41:1 42:1 43:1 44:1	 40:5 41:5 42:5 43:5 44:5	 40:6 41:6 42:6 43:6 44:6
//                           2
//                           00:3 01:3 02:3 03:3 04:3
//                           10:3 11:3 12:3 13:3 14:3
//                           20:3 21:3 22:3 23:3 24:3
//                           30:3 31:3 32:3 33:3 34:3
//                           40:3 41:3 42:3 43:3 44:3

constexpr auto FRONT  = 0;
constexpr auto LEFT   = 3;
constexpr auto RIGHT  = 4;
constexpr auto TOP    = 1;
constexpr auto BOTTOM = 2;
constexpr auto BACK   = 5;

template<int dim = 5>
class Cube {
public:
	Cube() {
		if ((dim & 1) == 0) {
			std::cerr << "cube dimension must be odd\n";
			throw std::exception("cube dimension must be odd");
		}

		//std::srand((unsigned)std::time(nullptr));
		for (int i = 6; i--;) {
			Face<dim>* f = new Face<dim>;
			f->initColor(i+1);
			face[i] = f;
		}
	}

	~Cube() {
		for (int i = 6; i--;) {
			delete face[i];
		}
	}

	void rotateCubeUp() {
		Face<dim>* front = face[FRONT];
		face[FRONT] = face[BOTTOM];
		face[BOTTOM] = face[BACK];
		face[BACK] = face[TOP];
		face[TOP] = front;
		face[LEFT]->rotateCCW();
		face[RIGHT]->rotateCW();
	}

	void rotateCubeDown() {
		Face<dim>* front = face[FRONT];
		face[FRONT] = face[TOP];
		face[TOP] = face[BACK];
		face[BACK] = face[BOTTOM];
		face[BOTTOM] = front;
		face[LEFT]->rotateCW();
		face[RIGHT]->rotateCCW();
	}

	void rotateCubeLeft() {
		Face<dim>* front = face[FRONT];
		face[FRONT] = face[RIGHT];
		face[RIGHT] = face[BACK];
		face[BACK] = face[LEFT];
		face[LEFT] = front;
		face[TOP]->rotateCW();
		face[BOTTOM]->rotateCCW();
	}

	void rotateCubeRight() {
		Face<dim>* front = face[FRONT];
		face[FRONT] = face[LEFT];
		face[LEFT] = face[BACK];
		face[BACK] = face[RIGHT];
		face[RIGHT] = front;
		face[TOP]->rotateCCW();
		face[BOTTOM]->rotateCW();
	}

	void rotateCubeUp2() {
		//std::swap(face[0], face[5]);
		//std::swap(face[1], face[2]);
		rotateCubeUp();
		rotateCubeUp();
	}

	void rotateCubeLeft2() {
		//std::swap(face[0], face[5]);
		//std::swap(face[1], face[2]);
		rotateCubeLeft();
		rotateCubeLeft();
	}

	// rotate a column up
	void rotateColumnUp(int col) {
		for (int i = dim; i--;) {
			Cubelet::rotate4(
				face[0]->cface[i][col],
				face[1]->cface[i][col],
				face[5]->cface[i][col],
				face[2]->cface[i][col]);
		}
		if (col == 0) {
			face[3]->rotateCCW();
		}
		else if (col == dim - 1) {
			face[4]->rotateCW();
		}
	}

	void rotateColumnDown(int col) {
		for (int i = dim; i--;) {
			Cubelet::rotate4(
				face[0]->cface[i][col],
				face[2]->cface[i][col],
				face[5]->cface[i][col],
				face[1]->cface[i][col]);
		}
		if (col == 0) {
			face[3]->rotateCW();
		}
		else if (col == dim - 1) {
			face[4]->rotateCCW();
		}
	}

	void rotateColumnTwice(int col) {
		for (int i = dim; i--;) {
			std::swap(
				face[0]->cface[i][col],
				face[5]->cface[i][col]);
			std::swap(
				face[1]->cface[i][col],
				face[2]->cface[i][col]);
		}
		if (col == 0) {
			face[3]->rotateTwice();
		}
		else if (col == dim - 1) {
			face[4]->rotateTwice();
		}
	}

	void rotateRowLeft(int row) {
		for (int i = dim; i--;) {
			Cubelet::rotate4(
				face[0]->cface[row][i],
				face[3]->cface[row][i],
				face[5]->cface[row][i],
				face[4]->cface[row][i]);
		}
		if (row == 0) {
			face[1]->rotateCW();
		}
		else if (row == dim - 1) {
			face[2]->rotateCCW();
		}
	}

	void rotateRowRight(int row) {
		for (int i = dim; i--;) {
			Cubelet::rotate4(
				face[0]->cface[row][i],
				face[4]->cface[row][i],
				face[5]->cface[row][i],
				face[3]->cface[row][i]);
		}
		if (row == 0) {
			face[1]->rotateCCW();
		}
		else if (row == dim - 1) {
			face[2]->rotateCW();
		}
	}

	void rotateRowTwice(int row) {
		for (int i = dim; i--;) {
			std::swap(
				face[0]->cface[row][i],
				face[5]->cface[row][i]);
			std::swap(
				face[4]->cface[row][i],
				face[3]->cface[row][i]);
		}
		if (row == 0) {
			face[1]->rotateTwice();
		}
		else if (row == dim - 1) {
			face[2]->rotateTwice();
		}
	}

	void scramble(int iterations = 200) {
		for (int x = iterations; x--;) {
			int r = std::rand() % 6;
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
			}

			r = std::rand() % 6;
			switch (r) {
			case 0:
				rotateColumnUp(std::rand() % dim);
				break;
			case 1:
				rotateColumnDown(std::rand() % dim);
				break;
			case 2:
				rotateColumnTwice(std::rand() % dim);
				break;
			case 3:
				rotateRowLeft(std::rand() % dim);
				break;
			case 4:
				rotateRowRight(std::rand() % dim);
				break;
			case 5:
				rotateRowTwice(std::rand() % dim);
				break;
			}
		}
	}

	bool isSolved() const {
		for (int f = 6; f--;) {
			if (!face[f].isSolved()) {
				return false;
			}
		}
		return true;
	}

	/// rotates cube to place specified side to the front
	void rotateToFront(int side) {
		switch (side) {
		default:
		case FRONT:
			// already in front!
			break;
		case LEFT:
			rotateCubeRight();
			break;
		case RIGHT:
			rotateCubeRight();
			break;
		case TOP:
			rotateCubeDown();
			break;
		case BOTTOM:
			rotateCubeUp();
			break;
		case BACK:
			rotateRowTwice();
			break;
		}
	}

	/// searches for unsolved center and returns side index
	int findUnsolvedCenter() {
		for (int f = 6; f--;) {
			if (!face[f].isSolved()) {
				return f;
			}
		}
		return -1;
	}

	// move cubelet(s) to form part 1 of center
	// this part is always 1 column, but can be many rows (from center to edge, not inclusive)
	void solveFaceCenter1() {
		int start = CENTER + 1;
		int end = dim - 1;
		int color = face[FRONT].centerColor();

		for (int i = start; i < end; ++i) {
			// is cubelet the color we want?
			if (face[FRONT].cface[i][CENTER].color != color) {
				// find a cubelet the correct color and in the correct position and move it to here
			}
		}
	}


	// solve the front face center
	void solveFaceCenters() {
		while (true) {
			// find an unsolved face center
			int f = findUnsolvedCenter();

			// if there are none, get out
			if (f == 0) {
				break;
			}

			// bring unsolved face to front
			rotateToFront(f);

			// do steps to solve it.
			solveFaceCenter1();
		}
	}


	void printRow(std::ostream& s, Face<dim>* face, int row) const {
		for (int col = 0; col < dim; ++col) {
			s << face->cface[row][col].color << ' ';
		}
	}

	void print(std::ostream& s) const {
		for (int row = 0; row < dim; ++row) {
			for (int col = 0; col < dim; ++col) {
				s << "    ";
			}
			s << ' ';
			printRow(s, face[1], row);
			s << '\n';
		}
		s << '\n';
		for (int row = 0; row < dim; ++row) {
			printRow(s, face[3], row);
			s << ' ';
			printRow(s, face[0], row);
			s << ' ';
			printRow(s, face[4], row);
			s << ' ';
			printRow(s, face[5], row);
			s << '\n';
		}
		s << '\n';
		for (int row = 0; row < dim; ++row) {
			for (int col = 0; col < dim; ++col) {
				s << "    ";
			}
			s << ' ';
			printRow(s, face[2], row);
			s << '\n';
		}
	}

	Face<dim>* face[6];
	const int CENTER = dim / 2;
};
