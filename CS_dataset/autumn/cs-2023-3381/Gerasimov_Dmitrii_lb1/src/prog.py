import numpy as np

def decorator(func):
    def wrapper(*args, **kwargs):
        try: r = func(*args, **kwargs) 
        except: r = None
        return r
    return wrapper

@decorator
def check_collision(bot1, bot2):
    return tuple(np.round(np.linalg.solve(np.array([[bot1[0],bot1[1]],[bot2[0],bot2[1]]]),-1*np.array([bot1[2],bot2[2]])),2))

@decorator
def check_surface(point1, point2, point3):
    return np.round(np.linalg.solve(np.array([[point1[0],point1[1],1],[point2[0],point2[1],1],[point3[0],point3[1],1]]),np.array([point1[2],point2[2],point3[2]])),2)

@decorator
def check_rotation(vec, rad):
    return np.round(np.dot(np.array([[np.cos(rad),-1*np.sin(rad),0],[np.sin(rad),np.cos(rad),0],[0,0,1]]),vec),2)