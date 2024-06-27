import pytest
from main import *


def test_check_colision():
    assert check_collision(np.array([-3, -6, 9]), np.array([8, -7, 0])) == (0.91, 1.04)


def test_check_surface():
    assert np.array_equal(
        check_surface(
            np.array([1, -6, 1]), np.array([0, -3, 2]), np.array([-3, 0, -1])
        ),  # type: ignore
        np.array([2, 1, 5]),
    )


def test_check_rotarion():
    assert np.array_equal(
        check_rotation(np.array([1, -2, 3]), 1.57),
        np.array([2, 1, 3]),
    )
