# Day 5: 1202 Program Alarm

from santas_little_helpers import *
from intcode import Program


original_program = list(map(int, get_input('inputs/input05',',')))

program_part_1 = Program(original_program, 1)
program_part_1.run()
# valid solution: all outputs except last are zero
if all(c == 0 for c in program_part_1.output[:-1]):
    party_1 = program_part_1.output[-1]


program_part_2 = Program(original_program, 5)
program_part_2.run()
# valid solution: all outputs except last are zero
if all(c == 0 for c in program_part_1.output[:-1]):
    party_2 = program_part_2.output[-1]

print_solutions(party_1, party_2)
