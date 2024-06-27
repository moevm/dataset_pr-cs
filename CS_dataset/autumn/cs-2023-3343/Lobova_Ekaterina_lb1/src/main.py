import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0]<=robot[0]<=point2[0] and point2[1]<=robot[1]<=point3[1]:
        return True
    return False


def check_collision(coefficients):
    pairs_of_colliding_bots =[]
    for i in range(len(coefficients)):
        for j in range(len(coefficients)):
            if i!=j:
                a_i,b_i=coefficients[i][0],coefficients[i][1]
                a_j,b_j=coefficients[j][0],coefficients[j][1]
                coeff_matrix=np.array([[a_i,b_i],[a_j,b_j]])
                if np.linalg.matrix_rank(coeff_matrix)==2:
                    pairs_of_colliding_bots.append((i,j))
    return pairs_of_colliding_bots


def check_path(points_list):
    lenght=0;
    for i in range(len(points_list)-1):
        vector=(points_list[i+1][0]-points_list[i][0],points_list[i+1][1]-points_list[i][1])
        lenght+=np.linalg.norm(vector)
    return round(lenght,2)
