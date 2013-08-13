#pragma once
#include "ofxTSP/Problem.h"
#include "ofxTSP/Route.h"

#include <vector>

using namespace std;

namespace ofxTSP {
	/** A solver solves a ofxTSP::Problem
	**/
	class Solver {
	public:
		virtual Route solve(const Problem & problem) = 0;
	};
}