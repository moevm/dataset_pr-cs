def check_for_lin_dep(eq1, eq2):
    if (eq1[1] == 0) and (eq2[1] == 0):
        return (eq1[0] == 0) and (eq1[0] == 0)
    elif eq1[1] == 0:
        return (eq1[0] == 0) and (eq2[0] != 0)
    elif eq2[1] == 0:
        return (eq2[0] == 0) and (eq1[0] != 0)
    else:
        return (eq1[0] / eq1[1]) == (eq2[0] / eq2[1])


def check_crossroad(robot, point1, point2, point3, point4):
    return ((point1[0] <= robot[0]) and (point3[0] >= robot[0])
            and (point1[1] <= robot[1]) and (point3[1] >= robot[1]))


def check_collision(coefficients):
    to_return = []
    for i in range(0, len(coefficients)):
        for j in range(0, len(coefficients)):
            if not check_for_lin_dep(coefficients[i], coefficients[j]):
                to_return.append((i,j))

    return to_return


def check_path(points_list):
    sum_len = 0
    for i in range(1, len(points_list)):
        point = points_list[i]
        pre_point = points_list[i-1]
        sum_len += (((point[0] - pre_point[0])**2 + (point[1] - pre_point[1])**2) ** (1/2))

    return round(sum_len, 2)
