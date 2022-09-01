#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <queue>
#include <vector>

using namespace std;
#define TAU (M_PI * 2)

// generic stream overload for vectors

template<class T> ostream& operator<<(ostream& stream, vector<T> vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		stream << (i ? " " : "") << vec[i];
	}

	return stream;
}

// "classes" (really structs, so things are public by default)

struct Node {
	map<int, float> neighbours;

	void edge(int other, float weight) {
		map[other] = weight;
	}
};

ostream& operator<<(ostream& stream, Node& vert) {
	stream << "Node(" << vert.neighbours.size() << " neighbours)";
	return stream;
}

struct Graph {
	vector<Node*> nodes;

	template<class T> Graph(vector<T> nodes) {
		for (T& node : nodes) {
			this->nodes.push_back(&node);
		}
	}

	// TODO make these arguments Node&

	void dijkstra(int start, int dest) {
		// TODO make this is an operator of struct Node, like in https://en.cppreference.com/w/cpp/container/priority_queue/emplace

		auto lambda = [](pair<int, float> a, pair<int, float> b) -> bool {
			return a.second > b.second; // TODO are you sure this is the right way round?
		};

		priority_queue<pair<int, float>, vector<pair<int, float>>, decltype(lambda)> unvisited(lambda);
		float dists[nodes.size()];

		// we know the distance of the start node to itself though
		// it's zero incase you haven't figured it out yet

		dists[start] = 0;

		// add all other nodes to unvisited set (a priority queue to make things speedy)
		// also give them all an infinite distance from the start node to start off with
		// this will be refined in later steps of the algorithm

		for (size_t i = 0; i < nodes.size(); i++) {
			Node& node = nodes[i];

			if (i != start) {
				dists[i] = numeric_limits<float>::infinity();
			}

			unvisited.push({ i, dists[i] });
		}

		// we know the distance of the start node to itself though
		// it's zero incase you haven't figured it out yet

		dists[start] = 0;
		int current = start;

		// continue until there are no more unvisited nodes to visit

		while (!unvisited.empty()) {
			// get the unvisited node with the current minimum distance

			int i = unvisited.top().first;
			unvisited.pop();
			Node& node = *nodes[i];

			// go through all of its neighbours

			for (auto& [ neighbour, weight ] : node.neighbours) {
				float dist = dists[i] + weight;

				if (dist < dists[neighbour]) {
					dists[neighbour] = dist;
					// unvisited.
				}
			}
		}
	}
};

ostream& operator<<(ostream& stream, Graph& graph) {
	stream << "Graph(" << graph.nodes.size() << " nodes)";
	return stream;
}

struct City : Node {
	string name;
	int pop;
	float lat, lon;

	City(string name, int pop, float lat, float lon) {
		this->name = name;
		this->pop  = pop;
		this->lat  = lat;
		this->lon  = lon;
	}

	// this is only relative distance;
	// if we wanted real distance, we'd need to multiply the result by 2 * radius

	float dist(City& other) {
		float rad_per_deg = TAU / 360;

		float x = 1. / 2 -
			cos((this->lat - other.lat) * rad_per_deg) / 2 +
			cos(this->lat * rad_per_deg) *
			cos(other.lat * rad_per_deg) *
			(1 - cos((this->lon) * rad_per_deg)) / 2;

		return asin(sqrt(x));
	}
};

ostream& operator<<(ostream& stream, City& city) {
	stream << "City(" << city.name << ")";
	return stream;
}

int main(void) {
	map<string, int> table;
	vector<City> cities;

	// read cities CSV file

	ifstream file("be.csv");
	file.ignore(numeric_limits<streamsize>::max(), file.widen('\n')); // discard first row

	for (string row; getline(file, row);) {
		vector<string> bits;

		string tmp;
		stringstream stream(row);

		while (getline(stream, tmp, ',')) {
			bits.push_back(tmp);
		}

		string name = bits[0];
		int pop = stoi(bits[8]);
		float lat = stof(bits[1]);
		float lon = stof(bits[2]);

		table[name] = cities.size();
		cities.push_back(City(name, pop, lat, lon));
	}

	file.close();

	// build graph from cities
	// weights are simply the distances between cities

	for (auto& city : cities) {
		for (size_t i = 0; i < cities.size(); i++) {
			Node& other = cities[i];

			if (&city == &other) {
				continue;
			}

			float weight = city.dist(other); // TODO include city population in weight measurement (privilege larger cities)
			city.edge(i, weight);
		}
	}

	Graph graph(cities);

	// find shortest path between Knokke-Heist & Arlon

	graph.dijkstra(table["Gent"], table["Arlon"]);

	return 0;
}
