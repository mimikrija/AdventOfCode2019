# Day 5: 1202 Program Alarm

from santas_little_helpers import *
from intcode import Program


original_program = list(map(int, get_input('inputs/input05',',')))

program_part_1 = Program(original_program, 1)
program_part_1.run()
party_1 = next(c for c in program_part_1.output if c != 0)
print_solutions(party_1)
