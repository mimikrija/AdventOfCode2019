# Day 10: Monitoring Station

from santas_little_helpers import *

asteroids = {(x, y) for x, row in enumerate(get_input('inputs/input10'))
                              for y, col in enumerate(row) if col=='#'}
