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

template<int dim = 5>
class Cube {
public:
	Cube() {
		std::srand((unsigned)std::time(nullptr));
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
		Face<dim>* p = face[0];
		face[0] = face[2];
		face[2] = face[1];
		face[1] = p;
	}

	void rotateCubeDown() {
		Face<dim>* p = face[0];
		face[0] = face[1];
		face[1] = face[2];
		face[2] = p;
	}

	void rotateCubeLeft() {
		Face<dim>* p = face[0];
		face[0] = face[4];
		face[4] = face[5];
		face[5] = p;
	}

	void rotateCubeRight() {
		Face<dim>* p = face[0];
		face[0] = face[5];
		face[5] = face[4];
		face[4] = p;
	}

	void rotateCubeTwice() {
		std::swap(face[0], face[5]);
		std::swap(face[1], face[2]);
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
			int r = std::rand() % 11;
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
				rotateCubeTwice();
				break;
			case 5:
				rotateColumnUp(std::rand() % dim);
				break;
			case 6:
				rotateColumnDown(std::rand() % dim);
				break;
			case 7:
				rotateColumnTwice(std::rand() % dim);
				break;
			case 8:
				rotateRowLeft(std::rand() % dim);
				break;
			case 9:
				rotateRowRight(std::rand() % dim);
				break;
			case 10:
				rotateRowTwice(std::rand() % dim);
				break;
			}
		}
	}

	void printRow(std::ostream& s, Face<dim>* face, int row) {
		for (int col = 0; col < dim; ++col) {
			s << face->cface[row][col].color << ' ';
		}
	}

	void print(std::ostream& s) {
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
};
