#include <cmath>
#include <iostream>
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

struct Graph {
	int vert_len;
	vector<Edge> edges;

	Graph(int vert_len, vector<Edge> edges) {
		this->vert_len = vert_len;
		this->edges = edges;
	}
};

ostream& operator<<(ostream& stream, Graph& graph) {
	stream << "Graph("
		<< graph.vert_len << " vertices, "
		<< graph.edges.size() << " edges, "
		<< graph.edges << ")";

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

void dijkstra(Graph& graph, int start, int dest) {
}

int main(void) {
	vector<City> cities = {
		City("Brussels", 0, 0, 0),
		City("Antwerp", 0, 0, 0),
	};

	// build graph from cities
	// weights are simply the distances between cities

	vector<Edge> edges;

	for (size_t i = 0; i < cities.size(); i++) {
		for (size_t j = i + 1; j < cities.size(); j++) {
			auto city1 = cities[i];
			auto city2 = cities[j];

			float weight = city1.dist(city2);
			edges.push_back(Edge(i, j, weight));
		}
	}

	Graph graph(cities.size(), edges);
	cout << graph << endl;

	return 0;
}
