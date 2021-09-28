# Day 1: The Tyranny of the Rocket Equation

from santas_little_helpers import *

def calculate_fuel(in_mass):
    return in_mass//3-2


masses = map(int, get_input('inputs/01'))

party_1 = sum(calculate_fuel(mass) for mass in masses)

print_solutions(party_1)
