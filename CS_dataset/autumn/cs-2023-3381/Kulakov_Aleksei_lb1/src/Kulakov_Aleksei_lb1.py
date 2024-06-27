import numpy as np
    
    def check_surface(point1, point2, point3):
        mtx1 = np.vstack((point1[:2], point2[:2], point3[:2]))
        mtx1 = np.hstack((mtx1, np.ones((3, 1)))) 
        mtx2 = np.vstack((point1[2], point2[2], point3[2]))
        try:
            solution = np.linalg.solve(mtx1, mtx2)
            rounded_solution = np.round(solution, 2)
            return rounded_solution[:, 0] 
        except np.linalg.LinAlgError as e:
            return None
    def check_collision(bot1, bot2):
        mtx1 = bot1[:2]
        c1 = bot1[2] * -1
        mtx2 = bot2[:2]
        c2 = bot2[2] * -1
        mtx3 = np.vstack((c1,c2))
        mtx4 = np.vstack((mtx1,mtx2))
        try:
            solution = np.linalg.solve(mtx4,mtx3)
            rounded_solution = np.round(solution,2)
            return tuple(rounded_solution[:, 0])
        except np.linalg.LinAlgError as e:
            return None
    def check_rotation(vec, rad):
        ans = np.array([0.,0.,vec[2]])
        ans[0] = np.cos(rad) * vec[0] - np.sin(rad)*vec[1]
        ans[1] = np.sin(rad) * vec[0] + np.cos(rad)*vec[1]
        ans = np.round(ans,2)
        return ans