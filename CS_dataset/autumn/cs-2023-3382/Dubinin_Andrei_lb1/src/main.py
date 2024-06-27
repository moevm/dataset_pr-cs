import numpy as np


def check_crossroad(point, point1, point2, point3, point4):
    x = set([p[0] for p in [point1, point2, point3, point4]])
    y = set([p[1] for p in [point1, point2, point3, point4]])
    if max(x) >= point[0] >= min(x) and max(y) >= point[1] >= min(y):
        return True
    else:
        return False



def check_collision(bots):
    solve = []
    for i in range(len(bots)):
        for j in range(len(bots)):
            if i != j:
                if bots[i][1]/bots[i][0] != bots[j][1]/bots[j][0]:
                    solve += [(i,j)]
                elif bots[i][2] != 0 and bots[j][2] != 0:
                    if bots[i][1]/bots[i][2] == bots[j][1]/bots[j][2]:
                        solve += [(i,j)]
                        
    if len(solve) == 0: return []
    return solve


def check_path(points):
    all_path = 0
    for i in range(len(points)-1):
        point_1,point_2 = points[i],points[i+1]
        path = (abs(point_1[0]-point_2[0])**2+abs(point_1[1]-point_2[1])**2)**0.5
        all_path += path
    return round(all_path,2)