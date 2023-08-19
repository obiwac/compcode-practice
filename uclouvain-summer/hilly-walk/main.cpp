#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <algorithm>

using namespace std;

#define EPS (1e-9)

struct Hill {
	double a, b;
	double left, right;
};

struct Endpoint {
	double x;
	bool is_end;
	int hill;
};

static double integral(double a, double b, double i, double j) {
	return 1. / 3 * (i - j) * (3 * a * a - 3 * a * (i + j) - 3 * b + i * i + i * j + j * j);
}

int main(void) {
	int n;
	cin >> n;

	vector<Hill> hills(n);
	vector<Endpoint> endpoints;

	for (int i = 0; i < n; i++) {
		Hill* const hill = &hills[i];
		cin >> hill->a >> hill->b;

		hill->left = -sqrt(hill->b) + hill->a;
		hill->right = sqrt(hill->b) + hill->a;

		if (hill->b < EPS) {
			continue;
		}

		endpoints.push_back(Endpoint { hill->left, false, i });
		endpoints.push_back(Endpoint { hill->right, true, i });
	}

	sort(endpoints.begin(), endpoints.end(), [](Endpoint const& a, Endpoint const& b) -> bool {
		if (a.x == b.x) {
			return a.is_end;
		}

		return a.x < b.x;
	});

	double hilliness = 0;
	int depth = 0;
	unordered_set<int> on_hills;
	double prev_x = 0;

	for (auto& endpoint : endpoints) {
		int const prev = depth;
		depth += !endpoint.is_end - endpoint.is_end;

		if (prev >= 2 && prev_x != endpoint.x) {
			for (int i : on_hills) {
				Hill* const hill = &hills[i];
				hilliness += integral(hill->a, hill->b, prev_x, endpoint.x);
			}
		}

		if (!endpoint.is_end) {
			on_hills.insert(endpoint.hill);
		}

		if (endpoint.is_end) {
			on_hills.erase(endpoint.hill);
		}

		prev_x = endpoint.x;
	}

	cout << hilliness << endl;
}
