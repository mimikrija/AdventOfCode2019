# Day 4: Secure Container

from santas_little_helpers import *

def is_valid(password):
    if len(password) != 6:
        return False
    if any(first > second for first, second in zip(password[:-1], password[1:])):
        return False
    if any(first == second for first, second in zip(password[:-1], password[1:])):
        return True
    return False

low, high = map(int, get_input('inputs/input04','-'))

party_1 = sum(is_valid(str(password)) for password in range(low, high+1))

print_solutions(party_1)

