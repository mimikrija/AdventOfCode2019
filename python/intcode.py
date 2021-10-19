from functools import reduce
from operator import mod, mul

class Program:
    VALUES_IN_INSTRUCTION = {
        1: 3,
        2: 3,
        99: 0,
    }

    def __init__(self, input):
        self.memory = list(input)
        self.instr_pointer = 0

    def get(self, address):
        return self.memory[address]
    
    def set(self, address, value):
        self.memory[address] = value

    def get_parameters(self, address):
        num_of_parameters = self.VALUES_IN_INSTRUCTION[self.memory[address]]
        return self.memory[address+1:address+num_of_parameters+1]

    def get_arguments(self, parameters, modes):
        arguments = []
        for parameter, mode in zip(parameters[:-1], modes):
            if mode == 0: # position mode
                argument = self.memory[parameter]
            else: # immediate mode
                argument = parameter
            arguments.append(argument)
        return arguments

    def operation(self, opcode, arguments):
        first, second = arguments
        if opcode == 1:
            return first + second
        if opcode == 2:
            return first * second

    def parse_opcode(self, address):
        opcode_and_modes = str(self.memory[address]).zfill(5)
        return int(opcode_and_modes[-2:]), list(map(int, opcode_and_modes[2::-1]))

    def run(self):
        while True:
            opcode, parameter_modes = self.parse_opcode(self.instr_pointer)
            if opcode == 99:
                return
            parameters = self.get_parameters(self.instr_pointer)
            arguments = self.get_arguments(parameters, parameter_modes)
            # Parameters that an instruction writes to will never be in immediate mode:
            result_position = parameters[-1]
            self.set(result_position, self.operation(opcode, arguments))
            self.instr_pointer += len(parameters) + 1