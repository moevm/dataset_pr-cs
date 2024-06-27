import numpy as np



def check_collision(bot1, bot2):
    try:
        a = np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
        b = np.array([-bot1[2], -bot2[2]])
        res = np.linalg.solve(a, b)
        res = np.array([round(i, 2) for i in res])
        return tuple(res) 
    except Exception:
        return None
    


def check_surface(point1, point2, point3):
    try: 
       a = np.array([[point1[0], point1[1], 1], 
                     [point2[0], point2[1], 1],
                     [point3[0], point3[1], 1]])
       b = np.array([point1[2], point2[2], point3[2]])
       res = np.linalg.solve(a, b)
       res = np.array([round(i, 2) for i in res])
       return res
    except Exception:
        return None


def check_rotation(vec, rad):
    a = np.array([
            [np.cos(rad), -np.sin(rad), 0],
            [np.sin(rad), np.cos(rad), 0],
            [0, 0, 1],
            ])
    return np.round(a.dot(vec), 2)
