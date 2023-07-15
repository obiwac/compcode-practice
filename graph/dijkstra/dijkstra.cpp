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

struct Edge {
	pair<int, int> verts;
	float weight;

	Edge(int vert1, int vert2, float weight) {
		verts = { vert1, vert2 };
		this->weight = weight;
	}
};

ostream& operator<<(ostream& stream, Edge& edge) {
	stream << "Edge(" << edge.weight << ", " << edge.verts.first << " -> " << edge.verts.second << ")";
	return stream;
}

struct City {
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

struct Graph {
	int vert_len;
	vector<Edge> edges;

	Graph(int vert_len, vector<Edge> edges) {
		this->vert_len = vert_len;
		this->edges = edges;
	}

	void dijkstra(Graph& graph, int start, int dest) {
		// add all vertices to unvisited set (a priority queue to make things speedy)
		// also give them all an infinite distance from the start vertex to start off with
		// this will be refined in later steps of the algorithm

		auto lambda = [](const Edge& a, const Edge& b) -> bool {
			return a.weight > b.weight;
		};

		priority_queue<Edge&, vector<Edge&>, decltype(lambda)> unvisited;

		unvisited.push();




		float dists[graph.vert_len];

		for (size_t i = 0; i < graph.vert_len; i++) {
			unvisited.push(i);
			dists[i] = numeric_limits<float>::infinity();
		}

		// we know the distance of the start vertex to itself though
		// it's zero incase you haven't figured it out yet

		dists[start] = 0;
		int current = start;

		// continue until there are no more unvisited vertices to visit:
		// TODO explain in comment

		while (!unvisited.empty()) {
			int vert = unvisited.pop();


		}
	}
};

ostream& operator<<(ostream& stream, Graph& graph) {
	stream << "Graph("
		<< graph.vert_len << " vertices, "
		<< graph.edges.size() << " edges, "
		<< graph.edges << ")";

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

	cout << cities << endl;

	// build graph from cities
	// weights are simply the distances between cities

	vector<Edge> edges;

	for (size_t i = 0; i < cities.size(); i++) {
		for (size_t j = i + 1; j < cities.size(); j++) {
			auto city1 = cities[i];
			auto city2 = cities[j];

			float weight = city1.dist(city2); // TODO include city population in weight measurement (privilege larger cities)
			edges.push_back(Edge(i, j, weight));
		}
	}

	Graph graph(cities.size(), edges);

	// find shortest path between Knokke-Heist & Arlon

	graph.dijkstra(table["Gent"], table["Arlon"]);

	return 0;
}
