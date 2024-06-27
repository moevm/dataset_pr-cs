import numpy as np


def check_collision(coords1, coords2):
    ndarray1=np.array([coords1[:-1],coords2[:-1]])
    ndarray2=np.array([-coords1[-1],-coords2[-1]])
    if np.linalg.matrix_rank(ndarray1)<2:
        return None
    else:
        intersection_point=np.linalg.solve(ndarray1,ndarray2)
        intersection_point=np.round(intersection_point,2)
    return tuple(intersection_point)


def check_surface(array1, array2, array3):
    ndarray_of_constants=np.array([[array1[-1]],[array2[-1]],[array3[-1]]])
    array1[-1]=1
    array2[-1]=1
    array3[-1]=1
    ndarray_of_coefficients=np.array([array1,array2,array3])
    if np.linalg.matrix_rank(ndarray_of_coefficients) < 3:
        return None
    else:
        coefficients_of_surface_equation=np.linalg.solve(ndarray_of_coefficients,ndarray_of_constants)
        coefficients_of_surface_equation=np.round(coefficients_of_surface_equation,2)
    return coefficients_of_surface_equation.flatten()



def check_rotation(vec, rad):
    rotated_matrix=np.array([[np.cos(rad),-np.sin(rad),0],[np.sin(rad),np.cos(rad),0],[0,0,1]])
    rotated_ndarray=np.dot(rotated_matrix,vec)
    rounded_rotated_ndarray=np.array([np.round(rotated_ndarray[0],2),np.round(rotated_ndarray[1],2),np.round(rotated_ndarray[2],2)])
    return rounded_rotated_ndarray
