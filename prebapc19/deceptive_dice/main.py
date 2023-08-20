n, k = map(int, input().split())

# I guess optimal play is to re-roll if the last dice you've rolled is lower than the expected value

prev = 0

for i in range(k):
	cutoff = prev // 1
	e = ((n * (n + 1) - cutoff * (cutoff + 1)) / 2 + cutoff * prev) / n
	prev = e

print(prev)
