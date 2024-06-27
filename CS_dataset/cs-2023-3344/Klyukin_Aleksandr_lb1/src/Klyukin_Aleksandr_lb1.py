import numpy as np


def check_collision(bot1, bot2):
    res1 = bot1[-1]
    res2 = bot2[-1]
    second = np.array([-res1, -res2])
    first = np.array([[*bot1[0:2]], [*bot2[0:2]]])
    if np.linalg.matrix_rank(first) == 2:
        ans = np.linalg.solve(first, second)
        ans[0] = round(ans[0], 2)
        ans[1] = round(ans[1], 2)
        return tuple(ans)
    else:
        return None


def check_surface(point1, point2, point3):
    a = np.array([[point1[0], point1[1], 1], [point2[0], point2[1], 1], [point3[0], point3[1], 1]])
    b = np.array([point1[2], point2[2], point3[2]])
    if np.linalg.matrix_rank(a) == 3:
        ans = np.linalg.solve(a, b)
        for i in range(len(ans)):
            ans[i] = round(float(ans[i]), 2)
        return ans
    else:
        return None


def check_rotation(vec, rad):
    try:
        ans = np.array([round(vec[0] * np.cos(rad) - vec[1] * np.sin(rad), 2),
                        round(vec[0] * np.sin(rad) + vec[1] * np.cos(rad), 2), round(vec[2], 2)])
        return ans
    except ValueError:
        return None
