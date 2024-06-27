import numpy as np

def check_collision(bot1, bot2):
    mat=np.array([[bot1[0],bot1[1]],[bot2[0],bot2[1]]])
    vec=np.array((-bot1[2],-bot2[2]))
    if np.linalg.matrix_rank(mat)==2:
        rez=np.linalg.solve(mat,vec)
        return (round(rez[0],2),round(rez[1],2))
    else:
        return None

def check_surface(point1, point2, point3):
    mat=np.array([[point1[0],point1[1],1],[point2[0],point2[1],1],[point3[0],point3[1],1]])
    vec=np.array((point1[2],point2[2],point3[2]))
    if np.linalg.matrix_rank(mat)==3:
        return (np.round(np.linalg.solve(mat,vec),2))
    else:
        return None

def check_rotation(vec, rad):
    mat=np.array([[np.cos(rad), -np.sin(rad), 0],[np.sin(rad), np.cos(rad), 0],[0, 0, 1]])
    rez=mat.dot(vec)
    return (np.round(rez,2))
