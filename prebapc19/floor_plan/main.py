n = int(input())

# observations:
# - n = m^2 - k^2 <=> n = (m + k)(m - k)

if not n % 4:
	print(n // 4 + 1, n // 4 - 1)

elif n % 2:
	print((n + 1) // 2, (n - 1) // 2)

else:
	print("impossible")
