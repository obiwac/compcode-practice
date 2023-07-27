# observations:
# - b gives us the height of the hill
# - a gives us the centre of the hill
# - we can find the left/right points of the hill with 0 = -(x - a)^2 + b <=> +/- sqrt(b) + a
# - the area of a hill over the interval i, j is A = -(j^3)/3 + a(j^2)/2 + j(b - a^2) + (i^3)/3 - a(i^2)/2 - i(b - a^2) = (i^3 - j^3)/3 + a(j^2 - i^2)/2 + (j - i)(b - a^2)
# - thanks to linearity, the integral of the sum of hills is the same as the sum of the integrals

import math

n = int(input())
hills = []
EPS = 1e-9

for _ in range(n):
	a, b = map(int, input().split())

	# ignore small values for b, as they'll never contribute to the hilliness and their ends get sorted before their starts

	if b < EPS:
		continue

	left = -math.sqrt(b) + a
	right = math.sqrt(b) + a

	hills.append((a, b, left, right))

# thanks to https://stackoverflow.com/questions/4542892/possible-interview-question-how-to-find-all-overlapping-intervals ❤️

endpoints = []

for i in range(len(hills)):
	a, b, left, right = hills[i]

	endpoints.append((left, True, i))
	endpoints.append((right, False, i))

endpoints.sort(key=lambda x: x[0] + (EPS if x[1] else 0))

def integral(a, b, i, j):
	return 1 / 3 * (i - j) * (3 * a ** 2 - 3 * a * (i + j) - 3 * b + i ** 2 + i * j + j ** 2)

hilliness = 0
depth = 0
on_hills = set() # which hills are we currently on?
prev_x = 0

for x, t, i in endpoints:
	prev = depth
	depth += t - (not t)

	if prev >= 2 and prev_x != x: # is an interval of interest (from prev_x to x)
		for j in on_hills:
			a, b, left, right = hills[j]
			hilliness += integral(a, b, prev_x, x)

	if t:
		on_hills.add(i)

	if not t:
		on_hills.remove(i)

	prev_x = x

# -x^2 - a^2 + xa + b = -x^2 + xa + (b - a^2)
# -(x^3)/3 + a(x^2)/2 + x(b - a^2) + C

print(hilliness)
