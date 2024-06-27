import numpy as np
from numpy import linalg as la
def check_collision(bot1, bot2):
	a=np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
	c=la.matrix_rank(a)
	if c==2:
		v=np.array([-bot1[2], -bot2[2]])
		return tuple(la.solve(a,v).round(2))
	else:
		return None


def check_surface(point1, point2, point3):
    b=np.vstack((point1, point2, point3))
    b[0][2]=1
    b[1][2]=1
    b[2][2]=1
    h=np.array([point1[2], point2[2], point3[2]])
    if la.matrix_rank(b)==3:
        r=la.solve(b, h)
        p=np.round(r, 2)
        return p
    else:
        return None

        
def check_rotation(vec, rad):
    k=np.array([[np.cos(rad), -np.sin(rad), 0],[np.sin(rad), np.cos(rad), 0], [0,0,1],])
    return np.round(k.dot(vec), 2)