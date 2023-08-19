t = int(input())

for _ in range(t):
	*pops, = map(int, input().split())
	s = 0

	for i in range(1, len(pops) - 1):
		delta = max(pops[i] - pops[i - 1] * 2, 0)
		s += delta

	print(s)
