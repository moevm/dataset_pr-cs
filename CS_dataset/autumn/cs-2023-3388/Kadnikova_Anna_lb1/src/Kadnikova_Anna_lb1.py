import numpy as np

def check_crossroad(robot, point1, point2, point3, point4):
    x_robot = robot[0]
    y_robot = robot[1]

    x1 = point1[0]
    y1 = point1[1]

    x2 = point2[0]
    y2 = point2[1]

    x3 = point3[0]
    y3 = point3[1]

    x4 = point4[0]
    y4 = point4[1]

    xs = [x1, x2, x3, x4]

    ys = [y1, y2, y3, y4]
    
    return (min(xs) <=  x_robot <= max(xs)) and (min(ys) <=  y_robot <= max(ys)) 
#print(check_rectangle((9, 3), (14, 13), (26, 13), (26, 23), (14, 23) ))

def check_collision(arr):
    n = len(arr)
    coords = []
    ans = []
    collisions = []
    
    for i in range(n):
        curr_coords = [arr[i][0], arr[i][1]]
        curr_ans = arr[2]*(-1)
        coords.append(curr_coords)
        ans.append(curr_ans)
    
    for i in range(n):
        for j in range(n):
            coords_a = coords[i]
            coords_b = coords[j]
            ans_a = ans[i]
            ans_b = ans[j]
            rank = np.linalg.matrix_rank([coords_a, coords_b])
            coords_a = np.array(coords_a)
            coords_b = np.array(coords_b)
            if rank >= 2 and i != j:
                collisions.append(tuple([i, j]))
    
    return collisions 
#print(check_collision([[-1, -4,  0],[-7, -5,  5],[ 1,  4,  2],[-5,  2,  2]]))

def check_path(way):
    s = 0 
    for i in range(1,len(way)):
        curr_way = np.sqrt((way[i][0] - way[i-1][0])**2 + (way[i][1] - way[i-1][1])**2)
        s += curr_way
    s = np.round(s,2)
    return s 

#print(check_path([(2.0, 3.0), (4.0, 5.0)]))
