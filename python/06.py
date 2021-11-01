# Day 6: Universal Orbit Map

from santas_little_helpers import *

def generate_orbit(planet, orbit=None):
    center = orbits[planet]
    if orbit:
        orbit.append(center)
    else:
        orbit = [center]
    if center == 'COM':
        return orbit
    else:
        return generate_orbit(center, orbit)

orbits = {planet: center for center, planet in (line.split(')') for line in get_input('inputs/input06'))}
planets = orbits.keys()

party_1 = sum(len(generate_orbit(planet)) for planet in planets)

print_solutions(party_1)
