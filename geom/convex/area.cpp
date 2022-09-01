#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// generic stream overload

template<class T> ostream& operator<<(ostream& stream, vector<T> vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		stream << (i ? " " : "") << vec[i];
	}

	return stream;
}

// "classes" (really structs, so things are public by default)

struct Vertex {
	float x = 0, y = 0;
	float theta = 0, dist = 0;

	Vertex(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vertex operator+(Vertex other) {
		return Vertex(x + other.x, y + other.y);
	}

	void operator+=(Vertex other) {
		x += other.x;
		y += other.y;
	}

	Vertex operator*(float factor) {
		return Vertex(x * factor, y * factor);
	}

	void polar(Vertex& centre) {
		Vertex delta = *this + centre * -1;

		theta = atan2(delta.y, delta.x);
		dist = sqrt(delta.x * delta.x + delta.y * delta.y);
	}
};

ostream& operator<<(ostream& stream, Vertex vert) {
	stream << "Vertex<" << vert.x << ", " << vert.y << ">";
	return stream;
}

struct Polygon {
	vector<Vertex> verts;
	vector<pair<int, int>> edges;

	Vertex centre;

	Polygon(vector<Vertex> verts) :
		centre(0, 0)
	{
		this->verts = verts;

		// find centre of mass of all vertices

		Vertex sum(0, 0);

		for (auto& vert : this->verts) {
			sum += vert;
		}

		centre = sum * (1. / this->verts.size());

		// find polar coords of all vertices in relation to the centre

		for (auto& vert : this->verts) {
			vert.polar(centre);
		}

		// sort all vertices by angle around centre

		auto key = [](const Vertex& a, const Vertex& b) -> bool {
			return b.theta > a.theta;
		};

		sort(this->verts.begin(), this->verts.end(), key);
	}
};

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
