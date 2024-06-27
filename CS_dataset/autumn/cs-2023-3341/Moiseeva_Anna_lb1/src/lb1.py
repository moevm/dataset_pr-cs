import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    robot_inside = False
    if point1[0] <= robot[0] <= point2[0] and point1[1] <= robot[1] <= point3[1]:
        robot_inside = True
    return robot_inside
    pass

def solve_system(equation1, equation2):
    coefficients = np.array([equation1[:2], equation2[:2]])
    constants = np.array([-equation1[-1], -equation2[-1]])
    try:
        solution = np.linalg.solve(coefficients, constants)
        return(True)
    except:
        return(False)

def check_collision(coefficients):
    size_line = coefficients.shape[0]
    result = []
    for i in range(size_line):
        system_loc = coefficients[i]
        for j in range(size_line):
            if i != j:
                system_new = coefficients[j]
                if solve_system(system_loc, system_new):
                    ans = (i, j)
                    result.append(ans)
    return result
    pass

def check_path(points_list):
    num_points = len(points_list)
    result = 0
    for i in range(num_points-1):
        len_path = ((points_list[i+1][0] - points_list[i][0])**2 + (points_list[i+1][1] - points_list[i][1])**2)**0.5
        result += len_path
   
    return round(result, 2)
    pass
