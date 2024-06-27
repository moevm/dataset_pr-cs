import numpy as np

def check_collision(bot1, bot2):
    matrix=np.array([[bot1[0], bot1[1]], [bot2[0], bot2[1]]])
    free_prt=np.array([bot1[2],bot2[2]])
    general_matrix=np.vstack((matrix,free_prt))
    a=np.linalg.matrix_rank(matrix)
    b=np.linalg.matrix_rank(free_prt)
    if(a<b):
        return None
    else:
        x,y=np.linalg.solve(matrix,free_prt)
        x=round(x,2)
        y=round(y,2)
        return(-(x),-(y))

def check_surface(point1, point2, point3):
    matrix=np.array([[point1[0],point1[1], 1], [point2[0],point2[1], 1], [point3[0],point3[1], 1]])
    free_prt=np.array([point1[2],point2[2],point3[2]])
    general_matrix=np.vstack((matrix,free_prt))
    a=np.linalg.matrix_rank(matrix)
    b=np.linalg.matrix_rank(general_matrix)
    if(a<b):
        return None
    else:
        x,y,z=np.linalg.solve(matrix,free_prt)
        x=round(x,2)
        y=round(y,2)
        z=round(z,2)
        return(np.array([x,y,z]))

def check_rotation(vec, rad):
    matrix=np.array([[np.cos(rad),-np.sin(rad),0], [np.sin(rad),np.cos(rad),0],[0,0,1]])
    turn=np.dot(matrix,vec)
    x,y,z=turn
    x=round(x,2)
    y=round(y,2)
    z=round(z,2)
    return(np.array([x,y,z]))
