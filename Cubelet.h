#pragma once

#include <algorithm> // std::swap

class Cubelet {
public:
	typedef char color_t;

	Cubelet() {
		color = 0;
		pos = 0;
		rot = 0;
	}

	// Rotates 4 cubelets s1->s2, s2->s3, s3->s4, s4->s1
	// if faceRotation is non-zero, adjust rotation for all 4 cubelets
	static void rotate4(Cubelet& s1, Cubelet& s2, Cubelet& s3, Cubelet& s4, int faceRotation = 0) {
		Cubelet s1temp = s1;
		s1 = s4;
		s4 = s3;
		s3 = s2;
		s2 = s1temp;
		s1.rot = (s1.rot + faceRotation) & 3;
		s2.rot = (s2.rot + faceRotation) & 3;
		s3.rot = (s3.rot + faceRotation) & 3;
		s4.rot = (s4.rot + faceRotation) & 3;
	}

	void adjustRotation(int delta) {
		rot = (rot + delta) & 3;
	}

	static void swap(Cubelet& s1, Cubelet& s2, int faceRotation = 0) {
		std::swap(s1, s2);
		s1.rot = (s1.rot + faceRotation) & 3;
		s2.rot = (s2.rot + faceRotation) & 3;
	}

	// color
	color_t color;

	// position ID (for debugging)
	int pos;

	// rotation (for future use on puzzles where we care about cubelet rotation)
	unsigned rot;
};
