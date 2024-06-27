import numpy as np

def check_collision(x,y):
    vec = np.array([-x[-1], -y[-1]])
    matr = np.array([x[0:2],y[0:2]])
    if np.linalg.det(matr) != 0:
        res = np.linalg.solve(matr,vec)
        return tuple(np.round([res[0], res[1]], 2))
    else:
        return None
    
def check_surface(point1, point2, point3):
    points = np.array([point1[0:2], point2[0:2], point3[0:2]])
    vec = np.array([[point1[-1]], [point2[-1]], [point3[-1]]])
    one = np.ones((3, 1))
    points2 = np.hstack((points, one))
    if np.linalg.det(points2) != 0:
        res = np.linalg.solve(points2, vec)
        return np.round([res[0][0], res[1][0], res[2][0]], 2)
    else:
        return None

def check_rotation(vec, rad):
    x = vec[0] * np.cos(rad) - vec[1] * np.sin(rad)
    y = vec[0] * np.sin(rad) + vec[1] * np.cos(rad)
    return np.round([x,y,vec[2]], 2)
