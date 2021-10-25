from functools import reduce
from operator import mod, mul

class Program:
    VALUES_IN_INSTRUCTION = {
        1: 3,
        2: 3,
        3: 1,
        99: 0,
    }

    def __init__(self, input, input_value=0):
        self.memory = list(input)
        self.instr_pointer = 0
        self.input_value = input_value
        self.output = []

    def get(self, address):
        return self.memory[address]
    
    def set(self, address, value):
        self.memory[address] = value

    def get_argument(self, arg_pos):
        modes = self.get(self.instr_pointer) // 100
        immediate_mode = (modes // 10**(arg_pos-1)) % 10
        print(arg_pos, immediate_mode)
        parameter = self.memory[self.instr_pointer+arg_pos]
        if immediate_mode:
            return parameter
        else: # position mode
            return self.memory[parameter]

    def binary_operation(self, opcode):
        first, second = [self.get_argument(pos) for pos in {1,2}]
        print(first, second)
        if opcode == 1:
            return first + second
        if opcode == 2:
            return first * second

    def run(self):
        while True:
            opcode = self.get(self.instr_pointer) % 100
            print(opcode, self.memory)
            if opcode == 99:
                return
            if opcode <= 2:
                result_value = self.binary_operation(opcode)
            if opcode == 3:
                result_value = self.input_value
            if opcode == 4:
                self.output.append(self.get_argument(1))
                continue
            result_position = self.get(self.instr_pointer+self.VALUES_IN_INSTRUCTION[opcode])
            self.set(result_position, result_value)
            # increment pointer
            self.instr_pointer += self.VALUES_IN_INSTRUCTION[opcode] + 1
