#include "ofxTSP/Route.h"

namespace ofxTSP {
	//---------
	Route::Route() {
		this->cost = 0.0f;
	}

	//---------
	Route::Route(const vector<int> & vector, float cost) {
		this->assign(vector.begin(), vector.end());
		this->cost = cost;
	}

	//---------
	void Route::addStep(int destination, float stepCost) {
		this->push_back(destination);
		this->cost += stepCost;
	}
}