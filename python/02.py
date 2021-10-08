# Day 2: 1202 Program Alarm

from santas_little_helpers import *
from itertools import product
from functools import reduce
from operator import mul

class Program:
    VALUES_IN_INSTRUCTION = {
        1: 3,
        2: 3,
        99: 0,
    }

    def __init__(self, input=[]):
        self.memory = list(input)
        self.address = 0

    def get(self, address):
        return self.memory[address]
    
    def set(self, address, value):
        self.memory[address] = value

    def get_parameters(self, address):
        num_of_parameters = self.VALUES_IN_INSTRUCTION[self.memory[address]]
        return self.memory[address+1:address+num_of_parameters+1]

    def operation(self, opcode, arguments):
        if opcode == 1:
            return sum(arguments)
        if opcode == 2:
            return reduce(mul, arguments)

    def run(self):
        current_address = 0
        while True:
            opcode = self.memory[current_address]
            if opcode == 99:
                return self
            parameters = self.get_parameters(current_address)
            arguments = [self.memory[num] for num in parameters[:-1]]
            result_position = parameters[-1]
            self.set(result_position, self.operation(opcode, arguments))
            current_address += len(parameters) + 1


original_program = list(map(int, get_input('inputs/02',',')))

program_part_1 = Program(original_program)
program_part_1.set(1, 12)
program_part_1.set(2, 2)
party_1 = program_part_1.run().get(0)

for noun, verb in product(range(0, 100), repeat=2):
    program_part_2 = Program(original_program)
    program_part_2.set(1, noun)
    program_part_2.set(2, verb)
    if program_part_2.run().get(0) == 19690720:
        party_2 = 100 * noun + verb
        break

print_solutions(party_1, party_2)
