import numpy as np 

  

def check_collision(bot1, bot2): 

    if (bot1[0] / bot2[0] == bot1[1] / bot2[1]): 

        return None 

    x = (bot1[2]*bot2[1] - bot2[2]*bot1[1]) / (bot2[0]*bot1[1] - bot1[0]*bot2[1]) 

    y = (-bot1[2] - bot1[0]*x) / bot1[1] 

    return np.round(x, 2)+0, np.round(y, 2)+0 

  

  

def check_surface(point1, point2, point3): 

    Mat = np.vstack( (np.concatenate((point1[:-1], [1])),  

                    np.concatenate((point2[:-1], [1])),  

                    np.concatenate((point3[:-1], [1]))) ) 

    Mat = np.array( Mat, float ) 

    vec = np.array( [point1[2], point2[2], point3[2]], float ) 

     

    rankk = np.linalg.matrix_rank(Mat) 

    if (not(rankk == Mat.shape[0] and rankk == Mat.shape[1])): 

        return None 

     

    result = np.linalg.solve(Mat, vec) 

    result[0] = np.round(result[0], 2) 

    result[1] = np.round(result[1], 2) 

    result[2] = np.round(result[2], 2) 

    return result 

  

  

def check_rotation(vec, rad): 

    bob = np.array([[np.cos(rad), np.sin(rad), 0], 

                     [-np.sin(rad), np.cos(rad), 0], 

                     [0, 0, 1]]) 

     

    res = np.dot(vec, bob) 

    res[0] = np.round(res[0], 2) 

    res[1] = np.round(res[1], 2) 

    res[2] = np.round(res[2], 2) 

    return res  
