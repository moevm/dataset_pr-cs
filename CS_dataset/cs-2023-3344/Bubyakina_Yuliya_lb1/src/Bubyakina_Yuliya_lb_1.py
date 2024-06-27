import numpy as np

def check_collision(bot1, bot2):
    variables=np.array([[bot1[0],bot1[1]],[bot2[0],bot2[1]]])
    values=np.array([-1*bot1[2],-1*bot2[2]])
    if np.linalg.matrix_rank(variables)>=2:
        return tuple(np.round(np.linalg.solve(variables,values),2))
    else:
        return "None"

def check_surface(point1, point2, point3):
    ratio = np.array([[point1[0],point1[1],1],[point2[0],point2[1],1],[point3[0],point3[1],1]])
    vector = np.array([point1[2],point2[2],point3[2]])
    if np.linalg.matrix_rank(ratio)>=3:
        surface = np.linalg.solve(ratio,vector)
        return np.round(surface,2)
    else:
        return "None"

def check_rotation(vec, rad):
    rotation_matrix=np.array([[np.cos(rad),-1*np.sin(rad)],[np.sin(rad),np.cos(rad)]])
    coordinates=np.array(vec[:2])
    rotated=np.dot(rotation_matrix,coordinates)
    rotated=np.append(rotated,vec[2])
    return np.round(rotated,2)