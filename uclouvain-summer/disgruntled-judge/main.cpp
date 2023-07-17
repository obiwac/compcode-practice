#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	size_t t;
	cin >> t;

	int odd_x[t];

	for (size_t i = 0; i < t; i++) {
		cin >> odd_x[i];
	}

	int const x_1 = odd_x[0];
	int const x_3 = odd_x[1];
	int const x_5 = odd_x[2];

	size_t const m = 10001;
	vector<pair<int, int>> possibilities;

	// first pass

	for (size_t a = 0; a < m; a++) {
		for (size_t b = 0; b < m; b++) {
			int const first = (a * ((a * x_1 + b) % m) + b) % m;

			if (first == x_3) {
				int const second = (a * ((a * x_3 + b) % m) + b) % m;

				if (second == x_5) {
					for (auto x : odd_x) {
						cout << (a * x + b) % m << endl;
					}

					return 0;
				}
			}
		}
	}
}
