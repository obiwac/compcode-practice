from collections import deque

t = int(input())

for _ in range(t):
	d = int(input())
	links = []
	nodes = set()
	adjacency = {}

	for _ in range(d):
		link = input().split()
		nodes |= {*link}
		links.append(link)

	# make adjacency list

	for n in nodes:
		adjacency[n] = []

		for link in links:
			if n == link[0]:
				adjacency[n].append(link[1])
			if n == link[1]:
				adjacency[n].append(link[0])

	n = len(nodes)
	far = 0

	for node, neighbours in adjacency.items():
		# do BFS
		# basically, find the farthest away node to this one

		q = deque()
		discovered = {}
		q.append((0, node))

		while q: # if depth greater than 6, then we know we're too "far"
			dist, v = q.popleft()
			dist += 1

			for u in adjacency[v]:
				if u in discovered:
					continue

				discovered[u] = dist
				q.append((dist, u))

		farness = max(discovered.values())
		far += farness > 6

	ratio = far / n
	print("YES" if ratio < 0.05 else "NO")
