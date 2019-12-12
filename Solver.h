#pragma once
#include "Cube.h"

template<int dim>
class Solver {
public:
	Solver(Cube& cube) 
		: m_cube(cube)
	{};


	void solve() {
		// check if all centers are solved, and if not, work on that
		Face<dim>* f = m_cube.findUnsolvedCenter();
		if (f) {

		}
	}

private:
	Cube& m_cube;
};
