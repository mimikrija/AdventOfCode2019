# Day 10: Monitoring Station

from santas_little_helpers import *
from cmath import phase, pi, sqrt
from math import atan2
from collections import defaultdict

asteroids = {complex(x,y) for y, row in enumerate(get_input('inputs/input10'))
                            for x, col in enumerate(row) if col=='#'}

def angle(num):
    return atan2(num.real, num.imag)

def detected(station, asteroids):
    angles = defaultdict(list)
    for asteroid in asteroids:
        if asteroid != station:
            angles[angle(asteroid-station)].append(asteroid-station)
    return angles

best_station, best_angles = max(((station, detected(station, asteroids)) for station in asteroids),
                                key=lambda x: len(x[1]))
party_1 = len(best_angles)

magnitude = lambda x: sqrt(x.real**2 + x.imag**2).real

angle_200 = sorted(best_angles.keys(),reverse=True)[199]
asteroid_200 = min(best_angles[angle_200], key=magnitude) + best_station

party_2 = int(asteroid_200.real*100 + asteroid_200.imag)
print_solutions(party_1, party_2)
