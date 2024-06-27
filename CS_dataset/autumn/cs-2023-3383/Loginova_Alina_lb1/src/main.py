import math
import numpy


def vector_length(point1, point2):
    return numpy.linalg.norm(numpy.array((point1)) - numpy.array((point2)))


def triangle_area(side1, side2, side3):
    s = (side1 + side2 + side3) / 2
    area = math.sqrt(s * (s - side1) * (s - side2) * (s - side3))
    return area


def check_crossroad(robot, point1, point2, point3, point4):
    ab = vector_length(point1, point2)
    bc = vector_length(point2, point3)
    cd = ab
    da = bc
    
    rect_area = ab * bc

    ar = vector_length(robot, point1)
    br = vector_length(robot, point2)
    cr = vector_length(robot, point3)
    dr = vector_length(robot, point4)

    arb = triangle_area(ar, br, ab)
    brc = triangle_area(br, cr, bc)
    crd = triangle_area(cr, dr, cd)
    dra = triangle_area(dr, ar, da)

    tri_area = round(arb + brc + crd + dra)

    if tri_area == rect_area:
        return True
    else:
        return False


def check_collision(coefficients):
    unknown = numpy.array([(line[0], line[1]) for line in coefficients])
    solution = numpy.array([(-elem[2]) for elem in coefficients])
    collisions = []

    for i in range(unknown.shape[0]):
        for k in range(unknown.shape[0]):
            try:
                numpy.linalg.solve((unknown[i], unknown[k]), (solution[i], solution[k]))
                found = True
            except numpy.linalg.LinAlgError:
                found = False

            if found:
                collisions.append((i, k))
    return collisions


def check_path(points_list):
    path = 0
    for i in range(len(points_list) - 1):
        path += vector_length(points_list[i], points_list[i+1])
    return round(path, 2)
