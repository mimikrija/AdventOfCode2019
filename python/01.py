# Day 1: The Tyranny of the Rocket Equation

from santas_little_helpers import *

def calculate_fuel(in_mass):
    return in_mass//3-2

def recursive_fuel(in_mass):
    mass = in_mass
    fuel = calculate_fuel(mass)
    if fuel <= 0:
        return mass
    else:
        mass += recursive_fuel(fuel)

def recursive_fuel(in_mass):
    mass = in_mass
    fuel = 0
    while True:
        mass = calculate_fuel(mass)
        if mass > 0:
            fuel += mass
        else:
            return fuel


masses = list(map(int, get_input('inputs/01')))

party_1 = sum(calculate_fuel(mass) for mass in masses)
party_2 = sum(recursive_fuel(mass) for mass in masses)

print_solutions(party_1, party_2)
