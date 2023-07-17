import math

t = int(input())

val = 0
a = 0
b = 0

# modular arithmetic!
# x_2 = a * x_1 + b (mod 10001)
# x_3 = a * x_2 + b (mod 10001)
# => a = (x_2 - x_3) / (x_1 - x_2) (mod 10001)
# => b = x_2 - a * x_1 (mod 10001)
# this means that our sample's 'a' value is:
# x_1 = 17, x_2 = 9727, x_3 = 822
# a = (9727 - 822) / (17 - 9727) (mod 10001) = 10000.08290422245
# problem: we don't have access to x_2, as it's in the output
# x_3 = a * (a * x_1 + b) + b = aax_1 + b(a + 1) (mod 10001)
# x_5 = a * (a * x_3 + b) + b = aax_3 + b(a + 1) (mod 10001)
# x_3 - x_5 = aax_1 - aax_3 (mod 10001)
# => (x_3 - x_5) / (x_1 - x_3) = aa (mod 10001)
# => (x_3 - aax_1) / (a + 1) = b (mod 10001)
# this doesn't seem to work directly however, so in lieu of that just iterate over possible values for a's idk

odd_x = []

for _ in range(t):
	odd_x.append(int(input()))

x_1 = odd_x[0]
x_3 = odd_x[1]
x_5 = odd_x[2]

expected_aa = ((x_3 - x_5) % 10001) / ((x_1 - x_3) % 10001) % 10001

for a in range(10001): # TODO correct bound?
	aa = a ** 2 % 10001
	print(aa, expected_aa)

	if aa == expected_aa:
		print(a)

aa = (x_3 - x_5) / (x_1 - x_3) % 10001
a = math.sqrt(aa)
b = (x_3 - aa * x_1) / (a + 1) % 10001

print((a * x_1 + b) % 10001)
