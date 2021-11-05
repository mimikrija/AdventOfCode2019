# Day 10: Monitoring Station

from santas_little_helpers import *
from cmath import phase

asteroids = {complex(x, y) for y, row in enumerate(get_input('inputs/input10'))
                            for x, col in enumerate(row) if col=='#'}

def detected(station, asteroids):
    angles = {phase(station-asteroid) for asteroid in asteroids if asteroid != station}
    return angles



best_station, best_angles = max(((station, detected(station, asteroids)) for station in asteroids),
                                key=lambda x: len(x[1]))
party_1 = len(best_angles)
print_solutions(party_1)
