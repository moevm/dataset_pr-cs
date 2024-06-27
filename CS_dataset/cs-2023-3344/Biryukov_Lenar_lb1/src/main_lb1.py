import numpy as np

def check_collision(bot1,bot2):
    x = np.array([[bot1[0], bot1[1]], [bot2[0],bot2[1]]])
    y = np.array([-bot1[2], -bot2[2]])
    if np.linalg.matrix_rank(x)==2:
        intersection = np.linalg.solve(x,y)
        return (round(intersection[0], 2), round(intersection[1], 2))
    else:
        return None

def check_surface(point1, point2,point3):
    x = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    y = np.array([point1[2],point2[2],point3[2]])
    if np.linalg.matrix_rank(x)==3:
        k = np.linalg.solve(x,y)
        return np.array([round(k[0],2),round (k[1],2), round(k[2],2)])
    else:
        return None

def check_rotation(v, r):
    try:
        matrix = np.array([round(v[0]*np.cos(r)-v[1]*np.sin(r),2),
        round(v[0]*np.sin(r)+v[1]*np.cos(r),2), round(v[2],2)])
        return matrix
    except:
        pass
