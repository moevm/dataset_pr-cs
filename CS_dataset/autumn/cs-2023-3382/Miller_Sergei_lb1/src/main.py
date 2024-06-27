def check_crossroad(robot, point1, point2, point3, point4):
    return point1[0] <= robot[0] <= point3[0] and point1[1] <= robot[1] <= point3[1]
    

def check_collision(coefficients):
    lenght = len(coefficients)
    ans = []
    for i in range(lenght):
        for j in range(lenght):
            k1 = coefficients[i][0] / coefficients[i][1]
            k2 = coefficients[j][0] / coefficients[j][1]
            if k1 != k2:
                ans.append((i, j))
    return ans


def check_path(points_list):
    ans = 0
    for i in range(1, len(points_list)):
        x1 = points_list[i - 1][0]
        y1 = points_list[i - 1][1]
        x2 = points_list[i][0]
        y2 = points_list[i][1]
        ans += ((x1 - x2)**2 + (y1 - y2)**2)**0.5 
    return round(ans, 2)

