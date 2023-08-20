n = int(input())
a = []

for _ in range(n):
	a.append(int(input()))

s = sum(a)
squares = 0
v = []

for i in range(n):
	s -= a[i]
	squares += a[i] ** 2
	v.append(s * squares)

print(max(v))
