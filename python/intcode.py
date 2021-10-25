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

    def get_argument(self, arg_pos):
        immediate_mode = self.memory[self.instr_pointer] // 10**(2+arg_pos)
        parameter = self.memory[self.instr_pointer+arg_pos]
        if immediate_mode:
            return parameter
        else: # position mode
            return self.memory[parameter]

    def binary_operation(self, opcode):
        first, second = [self.get_argument(pos) for pos in {1,2}]
        if opcode == 1:
            return first + second
        if opcode == 2:
            return first * second

    def run(self):
        while True:
            opcode = self.get(self.instr_pointer)
            if opcode == 99:
                return
            if opcode <= 2:
                result_value = self.binary_operation(opcode)
            result_position = self.get(self.instr_pointer+self.VALUES_IN_INSTRUCTION[opcode])
            self.set(result_position, result_value)
            # increment pointer
            self.instr_pointer += self.VALUES_IN_INSTRUCTION[opcode] + 1
