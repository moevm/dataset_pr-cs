import numpy as np


def check_crossroad(rob, p1, p2, p3, p4):
    coord = sorted([p1, p2, p3, p4])
    if coord[0][0] <= rob[0] <= coord[-1][0] and coord[0][1] <= rob[1] <= coord[-1][1]:
        return True
    return False


def check_collision(coef):
    answer = []
    for i in range(len(coef)):
        k1 = -coef[i][0] / coef[i][1]
        b1 = -coef[i][2] / coef[i][1]
        for j in range(i + 1, len(coef)):
            k2 = -coef[j][0] / coef[j][1]
            b2 = -coef[j][2] / coef[j][1]
            if k1 != k2:
                answer.append((i, j))
                answer.append((j, i))
            else:
                if b1 == b2:
                    answer.append((i, j))
                    answer.append((j, i))
    return sorted(answer)


def check_path(p_l):
    answer = 0
    for i in range(1, len(p_l)):
        answer += np.linalg.norm((p_l[i][0] - p_l[i - 1][0], p_l[i][1] - p_l[i - 1][1]))
    return np.round(answer, 2)