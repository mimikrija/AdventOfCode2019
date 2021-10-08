from functools import reduce
from operator import mul

class Program:
    VALUES_IN_INSTRUCTION = {
        1: 3,
        2: 3,
        99: 0,
    }

    def __init__(self, input):
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
        instruction_pointer = 0
        while True:
            opcode = self.memory[instruction_pointer]
            if opcode == 99:
                return
            parameters = self.get_parameters(instruction_pointer)
            arguments = [self.memory[num] for num in parameters[:-1]]
            result_position = parameters[-1]
            self.set(result_position, self.operation(opcode, arguments))
            instruction_pointer += len(parameters) + 1