# Day 8: Space Image Format

from santas_little_helpers import *

width = 25
height = 6
size = width * height

whole_image = get_input('inputs/input08')[0]
layers = [whole_image[num:num+size] for num in range(0, len(whole_image), size)]

fewest_zeros_layer = min(layers, key=lambda x: x.count('0'))
party_1 = fewest_zeros_layer.count('1') * fewest_zeros_layer.count('2')

print_solutions(party_1)
