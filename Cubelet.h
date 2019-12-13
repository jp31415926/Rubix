#pragma once

class Cubelet {
public:
	Cubelet() {
		color = 0;
		pos = 0;
		rot = 0;
	}

	static void rotate4(Cubelet& s1, Cubelet& s2, Cubelet& s3, Cubelet& s4, int faceRotation = 0) {
		Cubelet s1temp = s1;
		s1 = s4;
		s4 = s3;
		s3 = s2;
		s2 = s1temp;
		if (faceRotation) {
			s1.rot = (s1.rot + faceRotation) & 3;
			s2.rot = (s2.rot + faceRotation) & 3;
			s3.rot = (s3.rot + faceRotation) & 3;
			s4.rot = (s4.rot + faceRotation) & 3;
		}
	}
	
	int color;
	int pos;
	unsigned rot;
};
