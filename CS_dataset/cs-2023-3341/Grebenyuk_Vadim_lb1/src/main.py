import numpy as np


def check_collision(bot1: np.ndarray, bot2: np.ndarray):
    return tuple(
        np.linalg.solve(
            np.array([bot1[:2], bot2[:2]]),
            [-bot1[2], -bot2[2]],
        ).round(2)
    )


def check_surface(point1: np.ndarray, point2: np.ndarray, point3: np.ndarray):
    try:
        return np.linalg.solve(
            np.column_stack(([point1[:2], point2[:2], point3[:2]], [1, 1, 1])),
            np.array([point1[2], point2[2], point3[2]]),
        ).round(2)
    except np.linalg.LinAlgError:
        # no solutions linalg.det is 0 or it unsolvable i dunno why
        return None


def check_rotation(vec: np.ndarray, rad: float):
    return np.dot(
        [
            [np.cos(rad), -np.sin(rad), 0],
            [np.sin(rad), np.cos(rad), 0],
            [0, 0, 1],
        ],
        vec,
    ).round(2)
