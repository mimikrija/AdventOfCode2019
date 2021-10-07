# Day 2: 1202 Program Alarm

from santas_little_helpers import *
from itertools import product


def operation(opcode, arguments=[]):
    first, second = arguments
    if opcode == 1:
        return first + second
    if opcode == 2:
        return first * second
    if opcode == 99:
        return

def parameters_count(opcode):
    if opcode == 1 or opcode == 2:
        return 3
    if opcode == 99:
        return 0
    else:
        raise ValueError('unknown opcode encountered!')

def reset_memory(prog, address, value):
    prog[address] = value
    return prog

def get_parameters(prog, opcode, address):
    if opcode == 99:
        return None, None
    param_positions = prog[address+1:address+parameters_count(opcode)+1]
    parameters = [prog[pos] for pos in param_positions[:-1]]
    return parameters, param_positions[-1]

def intcode(prog, address=0):
    opcode = prog[address]
    arguments, result_position = get_parameters(prog, opcode, address)
    if arguments:
        return reset_memory(prog, result_position, operation(opcode, arguments)), address + parameters_count(opcode) + 1
    # no args: code 99 we are done with the program
    return prog, None

def run_program(program):
    position = 0
    while True:
        program, position = intcode(program, position)
        if position == None:
            return program



program = list(map(int, get_input('inputs/02',',')))
program_part_1 = list(program)
# To do this, before running the program, replace position 1
# with the value 12 and replace position 2 with the value 2.
program_part_1 = reset_memory(program_part_1, 1, 12)
program_part_1 = reset_memory(program_part_1, 2, 2)

party_1 = run_program(program_part_1)[0]


for noun, verb in product(range(0, 100), repeat=2):
    program_part_2 = list(program)
    program_part_2 = reset_memory(program_part_2, 1, noun)
    program_part_2 = reset_memory(program_part_2, 2, verb)
    if run_program(program_part_2)[0] == 19690720:
        party_2 = 100 * noun + verb
        break

print_solutions(party_1, party_2)
