import numpy as np


def rotate(x, y, phi):
	rotation_matrix = np.array([[np.cos(phi), -1*np.sin(phi)], [np.sin(phi), np.cos(phi)]])
	values_matrix = np.array([[x], [y]])
	return rotation_matrix.dot(values_matrix).T[0]

def check_crossroad(robot, *points):
	points = list(points)
	delta_x = points[0][0]-points[1][0]
	delta_y = points[0][1]-points[1][1]
	angle = np.arctan(delta_y/delta_x)
	if(angle != 0):
		robot  = rotate(robot[0],  robot[1],  angle)
		for i in range(4):
			points[i] = rotate(points[i][0], points[i][1], angle)

	xmin = min(list(zip(*points))[0])
	xmax = max(list(zip(*points))[0])
	ymin = min(list(zip(*points))[1])
	ymax = max(list(zip(*points))[1])

	return (xmin <= robot[0] <= xmax and ymin <= robot[1] <= ymax)


def check_collision(coefficients):
    coefficients = np.delete(np.array(coefficients), 2, 1)
    output = []
    for i1,u1 in enumerate(coefficients):
    	for i2,u2 in enumerate(coefficients[i1+1:]):
    		i2 += (i1+1)
    		if(np.linalg.matrix_rank(np.vstack((u1, u2))) >= 2):
    			output.append((i1, i2))
    			output.append((i2, i1))
    output.sort()
    return output


def check_path(points_list):
    points_list = np.array(points_list)
    s = 0
    for i in range(len(points_list)-1):
    	s += np.linalg.norm(points_list[i]-points_list[i+1])
    return round(s, 2)
