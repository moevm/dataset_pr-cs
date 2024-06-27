import numpy as np

def check_crossroad(rb, p1, p2, p3, p4):
    if rb[0] >= p1[0] and rb[1] >= p1[1] and rb[0] <= p2[0] and rb[1] >= p2[1] and rb[0] <= p3[0] and rb[1] <= p3[1] and rb[0] >= p4[0] and rb[1] <= p4[1]:
        return True
    else:
        return False

def check_collision(cof):
    res = []
    for i in range(len(cof)):
        for j in range(len(cof)):
            if (i != j) and np.linalg.matrix_rank(np.array([[cof[i][0],cof[i][1]] , [cof[j][0],cof[j][1]]])) == 2:
                    res.append((i,j))
    return res

def check_path(pl):
    b = 0
    for i in range(len(pl)-1):
        b = b + ((pl[i+1][0]-pl[i][0])**2 + (pl[i+1][1]-pl[i][1])**2)**(1/2)
    return round(b,2)