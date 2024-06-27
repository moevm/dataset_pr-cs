from numpy import array
from numpy.linalg import matrix_rank

def check_crossroad(robot, point1, point2, point3, point4):
    return robot[0] >= point1[0] and robot[1] >= point1[1] and robot[0] <= point3[0] and robot[1] <= point3[1]

def check_collision(coefficients):
    mas = []
    l = []
    for i in range(coefficients.shape[0]):
        for j in range(coefficients.shape[0]):
            if j != i:
                l += [coefficients[i][:2],coefficients[j][:2]]
                if matrix_rank(l) == 2:
                    mas.append((i,j))
                l = []
    return mas


def check_path(points_list):
    cnt = 0
    for i in range(len(points_list)-1):
        cnt += ((points_list[i+1][0] - points_list[i][0])**2 + (points_list[i+1][1] - points_list[i][1])**2)**0.5
    return round(cnt, 2)
