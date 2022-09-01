#include <iostream>
#include <vector>

using namespace std;

// "classes" (really structs, so things are public by default)

struct Vertex {
	float x = 0, y = 0;

	Vertex(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vertex operator+(Vertex other) {
		Vertex vert(this->x + other.x, this->y + other.y);
		return vert;
	}

	void operator+=(Vertex other) {
		this->x += other.x;
		this->y += other.y;
	}
};

struct Polygon {
	vector<Vertex> verts;
	vector<pair<int, int>> edges;

	Polygon(vector<Vertex> verts) {
		this->verts = verts;

		// find centre of mass of all vertices

		Vertex sum(0, 0);

		for (auto& vert : verts) {
			sum += vert;
		}
	}
};

// stream overloads

template<class T> ostream& operator<<(ostream& stream, vector<T> vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		stream << (i ? " " : "") << vec[i];
	}

	return stream;
}

ostream& operator<<(ostream& stream, Vertex vert) {
	stream << "Vertex<" << vert.x << ", " << "vert.y" << ">";
	return stream;
}

ostream& operator<<(ostream& stream, Polygon poly) {
	stream << "Polygon<" << poly.verts << ">";
	return stream;
}

int main(void) {
	vector<Vertex> verts = {
		Vertex(0, 0),
		Vertex(0, 1),
		Vertex(1, 1),
		Vertex(1, 0),
	};

	Polygon poly(verts);

	cout << poly << endl;
	return 0;
}
