from numpy import array
from numpy.linalg import matrix_rank
from math import sqrt

def check_crossroad(robot, point1, point2, point3, point4):
    return (robot[0] <= point3[0] and robot[1] <= point3[1] and robot[0] >= point1[0] and robot[1] >= point1[1])


def check_collision(coefficients):
    mas = []
    mn = []
    for i in range(coefficients.shape[0]):
        for j in range(coefficients.shape[0]):
            if j != i:
                mn += [coefficients[i][:2],coefficients[j][:2]]
                if matrix_rank(mn) == 2:
                    mas.append((i,j))
                mn = []
    return mas


def check_path(points_list):
    counter = 0
    for i in range(len(points_list)-1):
        counter += sqrt(pow(points_list[i+1][0] - points_list[i][0], 2) + pow(points_list[i+1][1] - points_list[i][1], 2))
    return round(counter, 2)
