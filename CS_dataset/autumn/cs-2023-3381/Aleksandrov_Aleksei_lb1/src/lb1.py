import numpy as np


def check_crossroad(robot, point1, point2, point3, point4):
	return ((robot[0] >= point1[0]) and (robot[0] <= point2[0]) and (robot[1] >= point1[1]) and (robot[1] <= point4[1]))


def check_collision(coefficients):
	answer = []
	for i in range (len(coefficients)):
		for j in range (i + 1, len(coefficients)):
			Matrix = np.array([coefficients[i][:2], coefficients[j][:2]])
			if (np.linalg.det(Matrix) != 0):
				answer.append((i, j))
				answer.append((j, i))
	answer.sort()
	return answer


def check_path(points_list):
	answer = 0
	for i in range (1, len(points_list)):
		answer += ((points_list[i][0] - points_list[i - 1][0])**2 + abs(points_list[i][1] - points_list[i - 1][1])**2)**0.5
	answer = round(answer, 2)
	return answer
