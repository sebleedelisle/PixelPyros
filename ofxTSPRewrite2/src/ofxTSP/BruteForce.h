#pragma once
#include "ofxTSP/Solver.h"
#include "ofMain.h"

#include <map>
#include <vector>
#include <set>

using namespace std;

namespace ofxTSP {
	/** Solve in a shitty but exact way.
	Presume all routes are symmetric (same cost in both directions)
	**/
	class BruteForce : public Solver {
	public:
		Route solve(const Problem & problem);
	protected:
		void step(const Problem & problem, Route visited);
		map<Route , float> solutions;
		Route bestSolution;
	};
}