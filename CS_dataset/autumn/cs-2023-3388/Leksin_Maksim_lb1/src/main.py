import math
import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    return (point1[0] <= robot[0] <= point2[0]) and (point1[1] <= robot[1] <= point4[1])

def solve_system(bim, bam):
    coefficients = np.array([bim[:2], bam[:2]])
    const = np.array([-bim[-1], -bam[-1]])
    try:
        solution = np.linalg.solve(coefficients, const)
        return True
    except:
        return False

def check_collision(ndarray):
    ans = []
    for i in range(ndarray.shape[0]):
        system_loc = ndarray[i]
        for j in range(ndarray.shape[0]):
            if i != j:
                system_new = ndarray[j]
                if solve_system(system_loc, system_new):
                    temp = (i, j)
                    ans.append(temp)
    return ans

def check_path(point_list):
    len_path = 0
    for i in range(len(point_list) - 1):
        len_path += math.sqrt((point_list[i+1][0] - point_list[i][0])**2 +
                (point_list[i+1][1] - point_list[i][1])**2)
    return round(len_path, 2)
