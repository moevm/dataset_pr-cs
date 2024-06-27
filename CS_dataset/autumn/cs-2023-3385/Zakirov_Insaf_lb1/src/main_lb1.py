import numpy as np

def check_crossroad(r, p1, p2, p3, p4) :
    if r[1] < p1[1] or r[1] > p3[1] :
        return False
    
    if r[0] < p1[0] or r[0] > p3[0] :
        return False
    
    return True


def check_solution(arr) :
    mtx = np.matrix(arr)
    rank = np.linalg.matrix_rank(mtx) 
    
    size = max(max(list(len(x) for x in arr)), len(arr))
    
    return rank == size
    
def check_collision(arr) :
    res = []
    for i in range(len(arr)) :
        for j in range(len(arr)) :
            a1,b1,c1 = arr[i]
            a2,b2,c2 = arr[j]
            temp_a = [[a1,b1], [a2,b2]]
            
            if check_solution(temp_a) :
                res.append((i, j))
                
    return res

def check_path(p_list) :
    result = 0
    for i in range(1, len(p_list)) :
        
        x = p_list[i][0] - p_list[i - 1][0]
        y = p_list[i][1] - p_list[i - 1][1]
        result += np.linalg.norm((x,y))
    
    return round(result, 2)
