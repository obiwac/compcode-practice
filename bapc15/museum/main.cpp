#include <iostream>
#include <vector>

using namespace std;

struct Tri {
	pair<int, int> a, b, c;

	bool operator==(Tri const& other) const {
		return a == other.a and b == other.b and c == other.c;
	}
};

int main(void) {
	size_t t;
	cin >> t;

	while (t --> 0) {
		size_t l, w;
		cin >> l >> w;

		double x, y, s;
		cin >> x >> y >> s;

		// move coordinates to centre of pedestal

		x += s / 2;
		y += s / 2;

		// get pillars

		vector<pair<int, int>> pillars;

		for (int i = 0; i < l + 1; i++) {
			pillars.push_back(make_pair(i, 0));
			pillars.push_back(make_pair(i, w));
		}

		for (int i = 1; i < w; i++) {
			pillars.push_back(make_pair(0, i));
			pillars.push_back(make_pair(l, i));
		}

		// form all possible triangles

		size_t possible = 0;

		for (size_t i = 0; i < pillars.size(); i++) {
			auto& pillar = pillars[i];

			for (size_t j = i; j < pillars.size(); j++) {
				auto& other = pillars[j];

				if (other == pillar) {
					continue;
				}

				for (size_t k = j; k < pillars.size(); k++) {
					auto& thing = pillars[k];

					if (thing == other or thing == pillar) continue;

					// don't add degenerate triangles

					if (pillar.first == other.first and other.first == thing.first) continue;
					if (pillar.second == other.second and other.second == thing.second) continue;

					pair<pair<int, int>, pair<int, int>> lines[] = {
						{pillar, other},
						{other, thing},
						{thing, pillar},
					};

					bool obs = false;
					double eps = 10e-8;

					for (auto [a, b] : lines) {
						double ax = a.first - x;
						double ay = a.second - y;

						double bx = b.first - x;
						double by = b.second - y;

						double vx = bx - ax, vy = by - ay;

						if (vy) {
							double inter_px = ( s / 2 - ay) / vy * (bx - ax) + ax;
							double inter_nx = (-s / 2 - ay) / vy * (bx - ax) + ax;

							if (abs(inter_px) < s / 2 + eps or abs(inter_nx) < s / 2 + eps) {
								obs = true;
								break;
							}
						}

						if (vx) {
							double inter_py = ( s / 2 - ax) / vx * (by - ay) + ay;
							double inter_ny = (-s / 2 - ax) / vx * (by - ay) + ay;

							if (abs(inter_py) < s / 2 + eps or abs(inter_ny) < s / 2 + eps) {
								obs = true;
								break;
							}
						}
					}

					possible += !obs;
				}
			}
		}

		cout << possible << endl;
	}
}
