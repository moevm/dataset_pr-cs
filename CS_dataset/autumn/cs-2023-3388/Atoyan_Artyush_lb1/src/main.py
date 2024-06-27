import numpy as np


def check_crossroad(robot,A,B,C,D):
    return (robot[0]>=A[0]) and  (robot[0]<=B[0]) and (robot[1]>=A[1]) and  (robot[1]<=D[1])

def check_collision(M):
    cross = []
    N = M.shape[0]
    for i in range(N):
        for j in range(N):
            if i!=j:
                a = np.array([[M[i][0], M[i][1]],[M[j][0], M[j][1]]])
                det = np.linalg.det(a)
                if det!=0:
                    cross.append((i,j))
    return cross
    
def check_path(points_list):    
    s = 0
    N = len(points_list)
    for i in range(N-1):
        a = points_list[i]
        b = points_list[i+1]
        l = ((a[0]-b[0])**2 + (a[1]-b[1])**2)**0.5
        s+=l
    return round(s,2)
    