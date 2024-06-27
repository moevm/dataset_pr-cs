import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    return (((robot[0]<=point2[0]) and (robot[0]>=point1[0])) and ((robot[1]>=point2[1]) and (robot[1]<=point3[1])))

def check_collision(coefficients):
    res = []
    for i in range(np.shape(coefficients)[0]):
        for k in range(np.shape(coefficients)[0]):
            aux = np.array([coefficients[i, 0], coefficients[i, 1]])
            aux = np.vstack([aux, [coefficients[k, 0], coefficients[k, 1]]])
            if (np.shape(aux[0])==np.linalg.matrix_rank(aux) or np.shape(aux[1])==np.linalg.matrix_rank(aux)):
                res.append((i,k))
    return res

def check_path(points_list):
    res = 0
    for i in range(1, len(points_list)):
        x = points_list[i][0]-points_list[i-1][0]
        y = points_list[i][1]-points_list[i-1][1]
        vect = [x, y]
        res+=np.linalg.norm(vect)
    return(round((res),2))
