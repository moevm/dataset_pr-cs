def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0] != point4[0]:
        k1 = (point4[0] - point1[0])/(point4[1]-point1[1])
        k3 = k1
        k2 = -1/k1
        k4 = k2
        b1 = point1[1] - k1*point1[0]
        b2 = point2[1] - k2*point2[0]
        b3 = point3[1] - k3 * point3[0]
        b4 = point4[1] - k4 * point4[0]
        if b1 > b3:
            if robot[1] <= k1*robot[0] + b1 and robot[1] <= k4*robot[0] + b4 and robot[1] >= k3*robot[0] + b3 and robot[1] >= k2*robot[0] + b2:
                return True
        else:
            if robot[1] >= k1 * robot[0] + b1 and robot[1] <= k4 * robot[0] + b4 and robot[1] <= k3 * robot[0] + b3 and robot[1] >= k2 * robot[0] + b2:
                return True
    else:
        if robot[1] <= point3[1] and robot[1] >= point1[1] and robot[0] >= point1[0] and robot[0] <= point3[0]:
            return True
    return False


def check_collision(coefficients):
    result = []
    for i in range(len(coefficients)):
        k1 = -coefficients[i][0]/coefficients[i][1]
        for j in range(len(coefficients)):
            if i == j:
                continue
            k2 = -coefficients[j][0]/coefficients[j][1]
            if k1 != k2:
                result.append((i, j))
    return result


def check_path(points_list):
    result = 0
    for i in range(len(points_list)-1):
        result += ((points_list[i][0] - points_list[i+1][0])**2 + (points_list[i][1] - points_list[i+1][1])**2) ** (1/2)
    return round(result, 2) 
