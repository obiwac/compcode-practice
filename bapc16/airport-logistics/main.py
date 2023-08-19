xa, ya, xb, yb = map(float, input())
n = int(input())

conveyors = []

for _ in range(n):
	x1, y1, x2, y2 = map(float, input())
	conveyors.append((x1, y1, x2, y2))

# observations:
# - the goal is to build a graph and run Dijkstra on it to find the shortest path
# - the conveyor belts are not necessarily axis-aligned
# - if we wanna leave a conveyor belt, there's always a single optimal angle to do so
# - what about crossing conveyor belts?
# - it never makes sense to walk immediately next to a conveyor belt
# - it never makes sense to leave a conveyor in the middle to join another
# - the edge costs are trivial to work out, what's tricky is determining the possible vertices of the graph
# - all beginnings/ends of conveyors may be considered as vertices (2N vertices)
# - all optimal leaving/joining points from each conveyor to each other conveyor may be considered a vertex (2N^2 vertices)
# - all intersections between conveyors may be considered as vertices (O(N) vertices)
# - our total complexity will be something like O(N^4) then (O(VE), with O(N^2) vertices and O(N^2) edges)
# - with a min-pqueue that drops down to O(N^2 + N^2 log(N^2)) or O(N^2 log(N))
