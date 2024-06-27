import numpy as np


def check_collision(bot1, bot2):
    c=np.array([-bot1[2],-bot2[2]])
    ab=np.array([[bot1[0],bot1[1]],[bot2[0],bot2[1]]])
    if np.linalg.matrix_rank(ab)>=2:
        return tuple(np.round(np.linalg.solve(ab,c),2))
    else:
        return None


def check_surface(point1, point2, point3):
    ab=np.array([[point1[0],point1[1]],[point2[0],point2[1]],[point3[0],point3[1]]])
    z=np.array([point1[2],point2[2],point3[2]])
    abc=np.hstack((ab,(([1],[1],[1]))))
    if np.linalg.matrix_rank(abc)>=3:
        return np.round(np.linalg.solve(abc,z),2)
    else:
        return None


def check_rotation(vec, rad):
    x=vec[0]
    y=vec[1]
    z=vec[2]
    q=rad
    x1=x*np.cos(q)-y*np.sin(q)
    y1=y*np.cos(q)+x*np.sin(q)
    arr=np.array([x1,y1,z],dtype='float64')
    return np.round(arr,2)
