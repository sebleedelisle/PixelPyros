#pragma once
#include "ofxTSP/Solver.h"

namespace ofxTSP {
	//strictly NOT a TSP solver
	//but works on same data set

	/**
	RouteFind

	find the cheapest route between 2 nodes on the graph
	**/
	class RouteFind : public Solver {
	public:
		RouteFind(int start, int end);
		Route solve(const Problem & problem);
	protected:
		void step(const Problem & problem, Route visited);
		int start, end;
		Route bestSolution;
	};
};