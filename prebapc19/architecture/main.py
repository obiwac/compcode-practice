r, c = map(int, input().split())
*e, = map(int, input().split())
*n, = map(int, input().split())

print("possible" if max(e) == max(n) else "impossible")
