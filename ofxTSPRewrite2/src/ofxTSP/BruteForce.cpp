#include "ofxTSP/BruteForce.h"
namespace ofxTSP {
	//---------
	Route BruteForce::solve(const Problem & problem) {
		this->solutions.clear();
		Route visited;
		this->bestSolution.cost = std::numeric_limits<float>::infinity();
		step(problem, visited);
		ofLogNotice("ofxTSP::BruteForce") << "Traversed " << solutions.size() << " possible routes (assymetric).";

		return this->bestSolution;
	}

	//---------
	bool hasVisited(int i, const vector<int> & visited) {
		Route::const_iterator it;
		for (it = visited.begin(); it != visited.end(); it++) {
			if (*it == i)
				return true;
		}
		return false;
	}

	//---------
	void BruteForce::step(const Problem & problem, Route visited) {
		//check whether we're already losing. If so don't continue to step down this branch
		if (visited.cost > bestSolution.cost)
			return;

		if (visited.size() == problem.nodeCount) {
			//we've visited all destinations
			//if we're better let's add this solution
			if(visited.cost < bestSolution.cost) {
				bestSolution = visited;
			}
			return;
		}

		for (int i=0; i<problem.nodeCount; i++) {
			if (!hasVisited(i, visited)) {
				if (visited.size() == 0) {
					Route visitBranch;
					visitBranch.push_back(i);
					step(problem, visitBranch);
				} else {
					Journey j(visited.back(), i);
					float cost = problem.getSymmetricCost(j);
					if (cost == -1)
						continue; //no journey found
					else {
						Route visitBranch(visited);
						visitBranch.addStep(i, cost);
						step(problem, visitBranch);
					}
				}
			}
		}
	}

}