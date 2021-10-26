# Day 7: Amplification Circuit

from santas_little_helpers import *
from intcode import Program
from itertools import permutations

def run_amplifiers(in_program, phases):
    start=0
    for phase in phases:
        amplifier = Program(in_program,[phase, start])
        amplifier.run()
        start = amplifier.output[0]
    return start


original_program = list(map(int, get_input('inputs/input07',',')))

party_1 = max(run_amplifiers(original_program, combo) for combo in permutations(range(5)))

print_solutions(party_1)
