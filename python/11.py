# Day 11: Space Police

from santas_little_helpers import *
from intcode import Program

def get_color_and_rotation(robot_code, input_value):
    robot_code.inputs.append(input_value)
    try:
        color, rotation = (robot_code.run() for _ in range(2))
        return color, rotation
    except:
        return None, None

def paint_the_panel(robot_code):
    positions = set()
    position = 0+0j
    direction = 0+1j
    painted_at_least_once = set()
    while True:
        current_color = position in positions
        color, rotation = get_color_and_rotation(robot_code, current_color)
        if color == None and rotation == None:
            return positions, len(painted_at_least_once)
        if color:
            positions.add(position)
            painted_at_least_once.add(position)
        elif current_color:
            positions.remove(position)
        if rotation:
            direction *= 0+1j # rotate left
        else:
            direction *= 0-1j # rotate right
        position += direction


# initialize robot intcode program
robot_instructions = list(map(int, get_input('inputs/input11',',')))
robot_code = Program(robot_instructions)
robot_code.feedback_loop_mode = True

panel, party_1 = paint_the_panel(robot_code)
print_solutions(party_1)
