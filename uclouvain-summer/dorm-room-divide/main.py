n = int(input())
verts = []

for _ in range(n):
	verts.append(tuple(map(int, input().split())))

def shoelace(v):
	n = len(v)
	area = 0

	for i in range(0, n - 1):
		area += v[i][0] * v[i + 1][1] - v[i + 1][0] * v[i][1]

	area += v[-1][0] * v[0][1] - v[0][0] * v[-1][1]
	return abs(area) / 2

total = shoelace(verts)

# construct triangle fan with the door vertex (first vertex) as its origin

accum = 0
a = verts[0] # door

for i in range(1, n - 1):
	b, c = verts[i: i + 2]

	# get area of triangle
	# shoelace method too because I'm lazy

	area = shoelace((a,b , c))
	left = (total / 2 - accum) / area

	if left <= 1:
		# we now know that the answer must be on the b-c line
		# we can use linearity to assert that 'left' of the area IFF 'left' of the line

		x = b[0] + (c[0] - b[0]) * left
		y = b[1] + (c[1] - b[1]) * left

		print(x, y)
		break

	accum += area
