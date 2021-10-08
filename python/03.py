# Day 3: Crossed Wires

from santas_little_helpers import *

MOVE = {
    'R': 1+0j,
    'L': -1+0j,
    'U': 0+1j,
    'D': 0-1j,
}

def manhattan_distance(coordinate):
    return int(abs(coordinate.real) + abs(coordinate.imag))

def generate_path(wire):
    path = set()
    current = 0+0j
    for direction, amount in wire:
        for _ in range(amount):
            current += MOVE[direction]
            path.add(current)
    return path

wires = [[(c[0], int(c[1:])) for c in line.split(',')] for line in get_input('inputs/input03')]

path_1, path_2 = (generate_path(wire) for wire in wires)

intersections = path_1 & path_2
party_1 = min(manhattan_distance(intersection) for intersection in intersections)
print_solutions(party_1)
