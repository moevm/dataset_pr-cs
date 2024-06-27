import numpy as np
def check_collision(robot1, robot2):
    eq=[[robot1[0],robot1[1]],[robot2[0],robot2[1]]]
    end=[-robot1[2],-robot2[2]]
    solution1 = np.round(np.linalg.solve(eq,end),2)
    return tuple(solution1)
def check_surface(point1, point2, point3):
    eq1 = [point1[0], point1[1], 1]
    eq2 = [point2[0], point2[1], 1]
    eq3 = [point3[0], point3[1], 1]
    d = [point1[2], point2[2], point3[2]]
    if np.linalg.matrix_rank([eq1, eq2, eq3]) == 3:
        solution2= np.round(np.linalg.solve([eq1, eq2, eq3],d),2)
        return solution2
    return None
def check_rotation(vec, rad):
    line= np.vstack(([np.cos(rad),-np.sin(rad)],[np.sin(rad),np.cos(rad)]))
    vector = [vec[0],vec[1]]
    dm = np.round(np.dot(line,vector),2)
    tm = np.append(dm,vec[2])
    return tm
