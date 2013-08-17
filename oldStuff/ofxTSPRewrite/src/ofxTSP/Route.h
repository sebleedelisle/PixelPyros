#pragma once

#include <vector>
#include <sstream>
#include <ostream>

using namespace std;

namespace ofxTSP {
	class Route : public vector<int> {
	public:
		Route();
		Route(const vector<int> & vector, float cost);
		void addStep(int destination, float stepCost);

		friend ostream& operator<<(ostream& os, const Route& route);
		float cost;
	};

	inline ostream& operator<<(ostream& os, const Route& route) {
		os << "[";
		Route::const_iterator it;
		for (it = route.begin(); it != route.end(); it++) {
			if (it != route.begin())
				os << ", ";
			os << *it;
		}
		os << "], cost=" << route.cost;
		return os;
	}
}