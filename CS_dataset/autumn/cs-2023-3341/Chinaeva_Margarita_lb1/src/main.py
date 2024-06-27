import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    x, y=(robot)
    x1, y1=(point1)
    x3, y3=(point3)
    return x1<=x and x<=x3 and y1<=y and y<=y3


def check_collision(coefficients):
    crash=[]
    for i in range(0, coefficients.shape[0]):
        for j in range(0, coefficients.shape[0]):
            if i != j:
                matrix=np.vstack([np.array(coefficients[i]), np.array(coefficients[j])])
                check_matrix=np.delete(matrix, 2, axis=1)
                if np.linalg.matrix_rank(check_matrix)==2:
                    crash.append((i,j))
    return crash


def check_path(points_list):
    distance=0
    for i in range(0, len(points_list)-1):
        point1=np.array(points_list[i])
        point2=np.array(points_list[i+1])
        local_distance=np.linalg.norm(point2 - point1)
        distance+=float(local_distance)
    return round(distance, 2)
