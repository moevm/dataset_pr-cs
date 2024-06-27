import numpy as np


def check_collision(bot1, bot2):
    a1, b1, c1 = bot1
    a2, b2, c2 = bot2
    g = a1*b2-a2*b1
    if g !=0:
        x = (c1*b2-c2*b1)/g
        y = (a1*c2-a2*c1)/g
        x = round(x, 2)
        y = round(y, 2)
        return (-x, -y)
    else:
        return None
def check_surface(point1, point2, point3):
    a1, b1, c1 = point1
    a2, b2, c2 = point2
    a3, b3, c3 = point3
    x = a2-a1
    y = b2-b1
    z = c2-c1
    xx = a3-a2
    yy = b3-b2
    zz = c3-c2
    if x == 0:
        return None
    if yy*x-xx*y ==0:
        return None
    b = (zz*x-z*xx)/(yy*x-xx*y)
    a = (z-(b)*y)/x
    c = c1 - a*a1-b*b1
    a = round(a, 2)
    b = round(b, 2)
    c = round(c, 2)
    k = np.array([a, b, c])
    return (k)
    
def check_rotation(vec, rad):
    p = [[np.cos(rad), -np.sin(rad), 0], [np.sin(rad), np.cos(rad), 0], [0, 0, 1]]
    p = np.dot(p, vec)
    a, b, c = p
    a = round(a, 2)
    b = round(b, 2)
    c = round(c, 2)
    k = np.array([a, b, c])
    return (k)