t = int(input())

for i in range(t):
	l, r = map(int, input().split())
	depth = l + r
	print(depth * (depth + 1) // 2 + r + 1)
