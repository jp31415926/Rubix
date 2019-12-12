#pragma once

class Cubelet {
public:
	Cubelet() {
		color = 0;
	}

	static void rotate4(Cubelet& s1, Cubelet& s2, Cubelet& s3, Cubelet& s4) {
		Cubelet s1temp = s1;
		s1 = s4;
		s4 = s3;
		s3 = s2;
		s2 = s1temp;
	}


	int color;
};
