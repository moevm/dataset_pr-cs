import numpy as np
import math

def check_collision(bot1,bot2):
    coefficient = np.array((bot1[0:2], bot2[0:2]))
    if np.linalg.matrix_rank(coefficient) == 2 :  #система уравнений имеет решение если ранг матрицы равен кол-ву столбцов или строк
        free_vectors = np.array([-bot1[2],-bot2[2]]) # ax^2+bx=-c, -с - члены массива свободных векторов
        solutions=tuple(np.linalg.solve(coefficient,free_vectors).round(2)) #находим решения уравнений ax^2+bx=-c, округляем с точностью до 2 и добавляем в кортеж
        return solutions # если условие не выполнено, то функция вернет None

def check_surface(point1, point2, point3):
    coordinates_matrix=np.vstack((np.concatenate((point1[:2],[1])), np.concatenate((point2[:2],[1])), np.concatenate((point3[:2],[1])))) #создаем матрицу коэффициентов
    vector_matrix=np.vstack((point1[2], point2[2], point3[2])) #матрица векторов состоящая из z-координат
    if np.linalg.det(coordinates_matrix)!=0: # система уравнений имеет решения если определитель матрицы не равен нулю
        coefficients= np.linalg.solve(coordinates_matrix, vector_matrix)
        list = np.array(tuple(x.round(2) for x in coefficients)) #округляем все элементы матрицы, заносим в ndarray
        list.shape=(1,3) #меняем оси местами
        return list[0] # если условие не выполнено, то функция вернет None

def check_rotation(vec, rad):
    rotate_matrix=np.array([[math.cos(rad), - math.sin(rad), 0],[math.sin(rad),math.cos(rad),0],[0,0,1]]) #матрица поворота
    vec=vec.reshape(3,1) # меняем оси местами для последующего умножения
    rotated = rotate_matrix.dot(vec) #перемножаем векторный столбец и матрицу поворота
    rotated_round=np.array(tuple(x.round(2) for x in rotated))
    rotated_round.shape = (1, 3)  # меняем оси местами
    return rotated_round[0]

