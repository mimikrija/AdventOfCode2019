# Day 9: Sensor Boost

from santas_little_helpers import *
from intcode import Program

original_program = list(map(int, get_input('inputs/input09',',')))

solutions = []
for part in (1,2):
    prog = Program(original_program, part)
    prog.run()
    solutions.append(prog.output[-1])

print_solutions(*solutions)
