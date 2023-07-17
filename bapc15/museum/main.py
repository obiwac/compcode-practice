t = int(input())

for _ in range(t):
	l, w = map(int, input().split())
	x, y, s = map(float, input().split())

	# centre pedestal coords

	x += s / 2
	y += s / 2

	# find all pillars

	pillars = set()

	j = 0

	for i in range(l + 1):
		pillars.add((i, j, 1))

	j = w

	for i in range(l + 1):
		pillars.add((i, j, 2))

	i = 0

	for j in range(1, w):
		pillars.add((i, j, 3))

	i = l - 1

	for j in range(1, w):
		pillars.add((i, j, 4))

	# go through all triangles

	triangles = set()

	for pillar in pillars:
		for other1 in pillars:
			if other1 == pillar:
				continue

			for other2 in pillars:
				if other2 == pillar or other2 == other1:
					continue

				# skip if triangle is degenerate

				if pillar[2] == other1[2] == other2[2]:
					continue

				triangles.add((pillar[:2], other1[:2], other2[:2]))

	# check which triangles intersect with our pedestal (i.e. are "impossible")

	possible_triangles = set()
	impossible_triangles = set()

	count = 0

	for tri in triangles:
		a, b, c = tri
		lines = ((a, b), (b, c), (c, a))

		intersection = 0

		for a, b in lines:
			# centre pedestal on origin

			ax = a[0] - x
			bx = b[0] - x

			ay = a[1] - y
			by = b[1] - y

			if ay - by == 0 or ax - bx == 0:
				continue

			slope = (ay - by) / (ax - bx)

			if -s / 2 <= slope * s / 2 <= s / 2:
				intersection = 1
				break

			if -s / 2 <= slope ** -1 * s / 2 <= s / 2:
				intersection = 1
				break

		count += not intersection

	print(count)
