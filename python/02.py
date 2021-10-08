# Day 2: 1202 Program Alarm

from santas_little_helpers import *
from itertools import product
from intcode import Program


original_program = list(map(int, get_input('inputs/02',',')))

program_part_1 = Program(original_program)
program_part_1.set(1, 12)
program_part_1.set(2, 2)
program_part_1.run()
party_1 = program_part_1.get(0)

for noun, verb in product(range(0, 100), repeat=2):
    program_part_2 = Program(original_program)
    program_part_2.set(1, noun)
    program_part_2.set(2, verb)
    program_part_2.run()
    if program_part_2.get(0) == 19690720:
        party_2 = 100 * noun + verb
        break

print_solutions(party_1, party_2)
