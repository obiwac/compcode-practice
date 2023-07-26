import math

EARTH_R = 6371
C = 299792.458

n = int(input())
lon, lat = map(float, input().split())

# let's assume we're working on a unit sphere to make the math simpler
# then, we just need to compensate for the Earth's radius at the end

def sphere_to_cart(lat, lon):
	lat, lon = map(math.radians, (lat, lon))
	return (math.cos(lat) * math.cos(lon), math.cos(lat) * math.sin(lon), math.sin(lat))

mx, my, mz = sphere_to_cart(lat, lon)

for _ in range(n):
	phi, psi, r, x = map(float, input().split())
	r /= EARTH_R # compensate for our previous simplification
	x = 360 * (x if x <= 0.5 else x - 1) # what the hell is this input lol 
	phi, psi = map(math.radians, (phi, psi))

	# phi is the longitude at which the orbit intersects the equator
	# start our satellite out at its correct position, but on the equator

	sat_pos = sphere_to_cart(0, x)

	# now, rotate the satellite up/down along the X-axis by psi degrees

	sat_pos = (
		sat_pos[0],
		sat_pos[1] * math.cos(psi) - sat_pos[2] * math.sin(psi),
		sat_pos[1] * math.sin(psi) + sat_pos[2] * math.cos(psi),
	)

	# finally, rotate the satellite along it's latitude line by phi degrees
	# also move satellite outwards by its radius while we're at it

	x = r * (sat_pos[0] * math.cos(phi) - sat_pos[1] * math.sin(phi))
	y = r * (sat_pos[0] * math.sin(phi) + sat_pos[1] * math.cos(phi))
	z = r * sat_pos[2]

	# determine if we have to pass through the earth

	if x * mx + y * my + z * mz < 1:
		print("no signal")
		continue

	dist = math.sqrt((x - mx) ** 2 + (y - my) ** 2 + (z - mz) ** 2)
	print(dist * EARTH_R / C)
