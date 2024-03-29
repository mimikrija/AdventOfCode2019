# Day 4: Secure Container

from santas_little_helpers import *
from collections import Counter

def is_valid(password):
    password = str(password)
    if len(password) != 6:
        return False
    if any(first > second for first, second in zip(password[:-1], password[1:])):
        return False
    if any(first == second for first, second in zip(password[:-1], password[1:])):
        return True
    return False

def new_rule(password):
    password = str(password)
    return 2 in Counter(password).values()

low, high = map(int, get_input('inputs/input04','-'))


party_1 = sum(is_valid(password) for password in range(low, high+1))
party_2 = sum(is_valid(password) and new_rule(password) for password in range(low, high+1))
print_solutions(party_1, party_2)
