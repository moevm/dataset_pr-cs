import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
	return (point1[0] <= robot[0] <= point2[0]) and (point1[1] <= robot[1] <= point4[1])


def check_collision(coefficients):
	n = coefficients.shape[0]
	result = []
	for i in range(n):
		for j in range(i + 1, n):
			m = \
			[
				[coefficients[i][0], coefficients[i][1]],
				[coefficients[j][0], coefficients[j][1]]
			]
			v = [[-coefficients[i][2]], [-coefficients[j][2]]]

			is_collision = True
			try:
				np.linalg.solve(m, v)
			except np.linalg.LinAlgError:
				is_collision = False
			if is_collision:
				result += [(i, j), (j, i)]
	return sorted(result)


def check_path(points_list):
	length = 0
	x = [a[0] for a in points_list]
	y = [a[1] for a in points_list]
	n = len(points_list)
	for i in range(1, n):
		length += ((x[i] - x[i - 1]) ** 2 + (y[i] - y[i - 1]) ** 2) ** 0.5
	return round(length, 2)
