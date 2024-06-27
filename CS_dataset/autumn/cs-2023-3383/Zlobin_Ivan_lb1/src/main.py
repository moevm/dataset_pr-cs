import numpy as np

def check_collision(bot1, bot2):
    arr=np.vstack((bot1,bot2))
    if np.linalg.matrix_rank(arr)!=2:
        return None
    arr=np.hsplit(arr,3)
    vec=np.array(arr[2]*-1)
    vec=np.hstack(vec)
    arr=np.hstack(arr)
    arr=np.delete(arr, 2, axis=1)
    return tuple(np.round(np.linalg.solve(arr,vec),2))

def check_surface(point1, point2, point3):
    vec=np.array([point1[2],point2[2],point3[2]])
    arr=np.vstack((point1,point2,point3))
    arr=np.insert(arr, 2, 1, axis=1)
    if np.linalg.matrix_rank(arr)!=3:
        return None
    arr=np.delete(arr, 3, axis=1)
    return np.round(np.array(np.linalg.solve(arr,vec)),2)

def check_rotation(vec, rad):
    cos=np.cos(rad)
    sin=np.sin(rad)
    matrix=np.array([[cos, sin*(-1), 0], [sin, cos, 0], [0, 0, 1]])
    return np.round(np.dot(matrix,vec),2)
