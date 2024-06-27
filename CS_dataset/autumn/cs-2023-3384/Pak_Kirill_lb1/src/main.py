import numpy as np 
import math 
 
def check_crossroad(robot, point1, point2,point3, point4): 
    if (robot[0]>=point1[0] and robot[0]<=point2[0]) and (robot[1]>=point1[1] and robot[1]<=point3[1]): 
        return True 
    else: 
        return False 
 
def check_collision(coefficients):
    res=[]
    coefficients1=coefficients[::-1]
    s1=0
    s2=len(coefficients)-1
    for i in coefficients:
        s2=len(coefficients)-1
        for j in coefficients1:
            d1=[[i[0],i[1]],[j[0],j[1]]]
            d2=[i[2],j[2]]
            try:
                np.linalg.solve(d1,d2)
                res.append((s1,s2))
            except:
                pass
            s2-=1
        s1+=1
    res=sorted(res)
    return res


def check_path(points_list):
    ans=float()
    c,d=0,0
    s=0
    for i in points_list:
        a=i[0]
        b=i[1]
        if s!=0:
            s1=a-c
            s2=b-d
            ans+=math.sqrt((s1**2)+(s2**2))
        c=i[0]
        d=i[1]
        s+=1
    ans=round(ans,2)
    return ans








 
