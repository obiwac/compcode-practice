#include <iostream>
#include <queue>
#include <vector>

using namespace std;

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

int main(void) {
	Graph graph(3, {
		Edge(0, 1, 1),
		Edge(1, 2, 2),
	});

	cout << graph << endl;

	return 0;
}
