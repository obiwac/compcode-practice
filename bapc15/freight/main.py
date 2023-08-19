import random

t = int(input())

for _ in range(t):
	n, w, l = map(int, input().split())
	*wagons, = map(int, input().split())

	def bs(lower, upper):
		if lower == upper:
			return lower

		mid = random.randint(lower, upper)

		# check for possibility

		val = 1
		i = 0
		loco = 0

		while val <= n:
			loco += 1

			if i >= len(wagons) or wagons[i] - val > mid:
				if i < len(wagons): val = wagons[i]
				else: val = n + 1

			else:
				val += mid

				while i < len(wagons) and wagons[i] < val:
					i += 1

		possible = loco <= l # maximum allowed locomotives

		# continue bs

		if possible:
			return bs(lower, mid)

		return bs(mid + 1, upper)

	# we know the minimum minimum length is 1 and the maximum minimum length is n

	print(bs(1, n))
