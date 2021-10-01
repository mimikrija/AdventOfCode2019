# Day 2: 1202 Program Alarm

from santas_little_helpers import *
from itertools import product, repeat

def operation(first, second, opcode):
    if opcode == 1:
        return first + second
    if opcode == 2:
        return first * second

def intcode(prog, position=0):
    opcode = prog[position]
    if opcode == 1 or opcode ==2:
        first = prog[prog[position+1]]
        second = prog[prog[position+2]]
        result = prog[position+3]
        prog[result] = operation(first, second, opcode)
        # do stuff
    elif opcode == 99:
        # halt program
        return prog, None
    else:
        raise ValueError('unknown opcode encountered!')
    return prog, position + 4

def reset_memory(in_program, value1, value2, pos1=1, pos2=2):
    out_program = list(in_program)
    out_program[pos1] = value1
    out_program[pos2] = value2
    return out_program

program = list(map(int, get_input('inputs/02',',')))
fresh_program = list(program)
# To do this, before running the program, replace position 1
# with the value 12 and replace position 2 with the value 2.
program_part_1 = reset_memory(program, 12, 2)

def run_program(program):
    position = 0
    while True:
        program, position = intcode(program, position)
        if position == None:
            return program

party_1 = run_program(program_part_1)[0]

for noun, verb in product(range(0, 100), repeat=2):
    program_part_2 = reset_memory(program, noun, verb)
    if run_program(program_part_2)[0] == 19690720:
        party_2 = 100 * noun + verb
        break

print_solutions(party_1, party_2)
