n, m = map(int, input().split())
adj_list = [set() for _ in range(n)]

for i in range(m):
	u, v = map(int, input().split())
	adj_list[u - 1].add((v - 1, i))

# the naive approach here would just be to start at every node, and when we encounter a cycle, we remove that corridor
# the issue is that I'm not sure we can reach all nodes like that

removed = set()

def dfs(s, visited = []):
	# we've found a cycle

	if s in visited:
		return True

	neighbours = set(adj_list[s])
	nvisited = visited + [s]

	for n, c in neighbours:
		if dfs(n, nvisited):
			removed.add(c)
			adj_list[s].remove((n, c))

	return False

dfs(0)

print(len(removed))

for r in removed:
	print(r + 1)
