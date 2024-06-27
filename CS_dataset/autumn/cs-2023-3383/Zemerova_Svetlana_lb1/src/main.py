import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    if point1[0]<=robot[0]<=point2[0]:
        if point1[1]<=robot[1]<=point3[1]:
            return True
    return False

def check_collision(coefficients):
    matr=coefficients[:,:2]
    kol_bot=coefficients.shape[0]
    vect=coefficients[:,2].reshape(kol_bot,1)
    stolk=[]
    for i in range(0,kol_bot):
        for j in range(i+1,kol_bot):
            matr1=np.vstack((matr[i,:],matr[j,:]))
            vect1=np.vstack((vect[i,:],vect[j,:]))
            if np.linalg.matrix_rank(matr1)==np.linalg.matrix_rank(np.concatenate((matr1,vect1),axis=1)):
                stolk.append((i,j))
                stolk.append((j,i))
    stolk.sort()
    return(stolk)

def check_path(points_list):
    vector=np.array([[points_list[i][0]-points_list[i-1][0],points_list[i][1]-points_list[i-1][1]] for i in range (1,len(points_list))])
    s=0
    for i in range(len(vector)):
        s+=np.linalg.norm(vector[i])
    return round(s,2)
