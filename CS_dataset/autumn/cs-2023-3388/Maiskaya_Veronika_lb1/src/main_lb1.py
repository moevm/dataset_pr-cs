import numpy as np
import math

def check_collision(bot1, bot2):
    a1, b1, c1 = bot1[0], bot1[1], bot1[2]
    a2, b2, c2 = bot2[0], bot2[1], bot2[2]

    try:
        y = (a2*c1-c2*a1)/(b2*a1-a2*b1)
        x = (-c1 - b1*y)/a1
        return (round(x,2),round(y,2))
    except Exception as e:
        return None

def check_surface(point1, point2, point3):
    x1, x2, x3 = point1[0], point2[0], point3[0]
    y1, y2, y3 = point1[1], point2[1], point3[1]

    matrix = np.array([
        [x1, y1, 1],
        [x2, y2, 1],
        [x3, y3, 1]
    ])
    vec = np.array([point1[2],point2[2],point3[2]])

    try:
        result = np.array([round(x, 2) for x in np.linalg.solve(matrix, vec)])
        return result
    except Exception as e:
        return None


def check_rotation(vec, rad):
    x_old, y_old, z_old = vec[0], vec[1], vec[2]
    x_new = x_old*math.cos(rad) - y_old*math.sin(rad)
    y_new = x_old*math.sin(rad) + y_old*math.cos(rad)

    return np.array([round(x_new,2), round(y_new,2), round(z_old,2)])