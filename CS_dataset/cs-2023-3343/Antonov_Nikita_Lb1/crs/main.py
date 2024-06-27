import numpy as np

def check_crossroad(robot, tk1, tk2, tk3, tk4) -> bool:
    return ( robot[0] >= tk1[0] and robot[1] >= tk1[1] and robot[0] <= tk2[0] and robot[1] >= tk2[1] and robot[0] <= tk3[0] and robot[1] <= tk3[1] and robot[0] >= tk4[0] and robot[1] <= tk4[1])


def check_collision(koef) -> list:
    korp = []
    for i in range(len(koef)):
        for j in range(i + 1, len(koef)):
            x1, y1, z1 = koef[i]
            x2, y2, z2 = koef[j]
            matr = np.array([[x1, y1], [x2, y2]])
            if np.linalg.matrix_rank(matr) == 2:
                korp.append((i, j))
                korp.append((j, i))
    korp.sort()
    return korp


def check_path(tk) -> float:
    if len(tk) < 2:
        return 0.0
    tksp = np.array(tk)
    dels = np.diff(tksp, axis=0)
    distances = np.linalg.norm(dels, axis=1)
    distance = np.sum(distances)
    return round(distance, 2)