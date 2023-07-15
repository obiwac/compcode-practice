t = int(input())

for i in range(t):
	tree = input()

	if tree.isdigit():
		print(0)
		continue

	counts = {}
	leaf_count = 0
	depth = 0
	parsing_leaf = False
	leaf = 0

	for j, c in enumerate(tree):
		if c.isdigit():
			parsing_leaf = True
			leaf *= 10
			leaf += int(c)

		elif c in "[],":
			if parsing_leaf:
				parsing_leaf = False

				# a 3 at depth 2 is basically the same as a 6 at depth 1

				k = leaf * 2 ** depth

				if k in counts:
					counts[k] += 1

				else:
					counts[k] = 1

				leaf_count += 1
				leaf = 0

			if c != ",":
				depth += (c == '[') - (c == ']')

	print(leaf_count - max(counts.values()))
