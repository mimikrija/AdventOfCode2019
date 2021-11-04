# Day 10: Monitoring Station

from santas_little_helpers import *
from cmath import phase

asteroids = {complex(x, -y) for x, row in enumerate(get_input('inputs/input10'))
                           for y, col in enumerate(row) if col=='#'}

def detected(station, asteroids):
    angles = {phase(station-asteroid) for asteroid in asteroids if asteroid != station}
    return angles

party_1 = max(len(detected(station, asteroids)) for station in asteroids)
print_solutions(party_1)
