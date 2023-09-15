r, c, zr, zc = map(int, input().split())

for _ in range(r):
	row = input()

	for _ in range(zr):
		for i in range(c):
			print(row[i] * zc, end="")

		print()
