# Day 11: Space Police

from santas_little_helpers import *
from intcode import Program

def get_color_and_rotation(robot_code, input_value):
    robot_code.inputs.append(input_value)
    try:
        is_white, rotation = (robot_code.run() for _ in range(2))
        return is_white, rotation
    except:
        return None, None

def paint_the_panel(robot_instructions, first_white=False):
    # initialize robot intcode program
    robot_code = Program(robot_instructions)
    robot_code.feedback_loop_mode = True
    position = 0+0j
    white_fields = set()
    if first_white:
        white_fields.add(position)
    direction = 0-1j
    all_positions = set()
    while True:
        current_color = position in white_fields
        is_white, rotation = get_color_and_rotation(robot_code, current_color)
        if is_white == None and rotation == None:
            return all_positions, white_fields
        all_positions.add(position)
        if is_white:
            white_fields.add(position)
        elif current_color:
            white_fields.remove(position)
        if rotation:
            direction *= 0+1j # rotate left
        else:
            direction *= 0-1j # rotate right
        position += direction

def print_from_set(in_set):
    cr = lambda x: x.real
    ci = lambda y: y.imag
    width = int(cr(max(in_set, key=cr))) + 1
    heigth = int(ci(max(in_set, key=ci))) + 1
    hull = [width * [' '] for _ in range(heigth)]
    for position in in_set:
        x = int(position.real)
        y = int(position.imag)
        hull[y][x] = '#'

    for line in hull:
        print(''.join(c for c in line))


robot_instructions = list(map(int, get_input('inputs/input11',',')))

painted_at_least_once, _ = paint_the_panel(robot_instructions)
party_1 = len(painted_at_least_once)
print_solutions(party_1)

_, painted_hull = paint_the_panel(robot_instructions, True)
print('Part 2 solution is:\n')
print_from_set(painted_hull)
