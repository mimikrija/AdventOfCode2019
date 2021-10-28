# Day 7: Amplification Circuit

from santas_little_helpers import *
from intcode import Program
from itertools import permutations

def run_amplifiers(in_program, phases):
    start=0
    for phase in phases:
        amplifier = Program(in_program,[phase, start])
        amplifier.run()
        start = amplifier.output[0]
    return start

def amplifier_feedback_loop(in_program, phases):
    # initialize amplifiers
    amplifiers = [Program(in_program,[phase]) for phase in phases]
    for amp in amplifiers:
        amp.feedback_loop_mode = True
    # initialize input for first amplifier
    result = 0

    while result is not None:
        for amp in amplifiers:
            amp.inputs.append(result)
            result = amp.run()
    # last solution of the last amplifier is the solution
    return amplifiers[-1].output[-1]


original_program = list(map(int, get_input('inputs/input07',',')))

party_1 = max(run_amplifiers(original_program, combo) for combo in permutations(range(5)))
party_2 = max(amplifier_feedback_loop(original_program, combo) for combo in permutations(range(5,10)))

print_solutions(party_1, party_2)
