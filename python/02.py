# Day 2: 1202 Program Alarm

from santas_little_helpers import *

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

program = list(map(int, get_input('inputs/02',',')))
# To do this, before running the program, replace position 1
# with the value 12 and replace position 2 with the value 2.
program[1] = 12
program[2] = 2


position = 0
while True:
    program, position = intcode(program, position)
    if position == None:
        break

party_1 = program[0]
print_solutions(party_1)
