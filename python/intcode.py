from collections import deque

class Program:
    VALUES_IN_INSTRUCTION = {
        1: 3,
        2: 3,
        3: 1,
        4: 1,
        5: 2,
        6: 2,
        7: 3,
        8: 3,
        9: 1,
        99: 0,
    }
    OPCODES_WHICH_WRITE_TO_MEMORY = {1, 2, 3, 7, 8}
    JUMP_OPCODES = {5, 6}

    def __init__(self, code, inputs=None):
        self.memory = {pos: code[pos] for pos in range(len(code))}
        self.instr_pointer = 0
        if type(inputs) == int:
            self.inputs = deque([inputs])
        elif inputs:
            self.inputs = deque(inputs)
        else:
            self.inputs = deque([])
        self.output = []
        self.pointer_increment = 0
        self.feedback_loop_mode = False
        self.relative_base = 0

    def get(self, address):
        return self.memory.get(address, 0)
    
    def set(self, address, value):
        self.memory[address] = value

    def get_argument(self, arg_pos, write_pos=False):
        modes = self.get(self.instr_pointer) // 100
        mode = (modes // 10**(arg_pos-1)) % 10
        parameter = self.get(self.instr_pointer+arg_pos)
        # writing modes!!
        if write_pos and mode <= 1:
            return parameter
        elif write_pos and mode == 2:
            return parameter + self.relative_base
        if mode == 0: # position mode
            return self.get(parameter)
        if mode == 1: # imediate mode
            return parameter
        if mode == 2: # relative mode
            return self.get(parameter+self.relative_base)


    def binary_operation(self, opcode):
        first, second = [self.get_argument(pos) for pos in {1,2}]
        if opcode == 1:
            return first + second
        if opcode == 2:
            return first * second
        if opcode == 7: # less than
            return int(first < second)
        if opcode == 8: # equal to
            return int(first == second)
    
    def jump_operation(self, opcode):
        first, second = [self.get_argument(pos) for pos in {1,2}]
        if opcode == 5: # jump-if-true
            if first:
                self.instr_pointer = second
                return
        if opcode == 6: # jump-if-false
            if not first:
                self.instr_pointer = second
                return
        # default if we don't jump:
        self.instr_pointer += self.VALUES_IN_INSTRUCTION[opcode] + 1


    def run(self):
        while True:
            opcode = self.get(self.instr_pointer) % 100
            if opcode == 99:
                return
            if opcode in self.OPCODES_WHICH_WRITE_TO_MEMORY:
                if opcode == 3:
                    result_value = self.inputs.popleft()
                else:
                    result_value = self.binary_operation(opcode)
                result_position = self.get_argument(self.VALUES_IN_INSTRUCTION[opcode], True)
                self.set(result_position, result_value)
            elif opcode == 4:
                self.output.append(self.get_argument(1))
            elif opcode == 9:
                self.relative_base += self.get_argument(1)
            # increment pointer
            if opcode in self.JUMP_OPCODES:
                self.jump_operation(opcode)
            else:
                self.instr_pointer += self.VALUES_IN_INSTRUCTION[opcode] + 1
            if self.feedback_loop_mode and opcode == 4:
                    return self.output[-1]
