import numpy as np

# Функция check_crossroad проверяет, пересекает ли робот какой-либо перекресток, заданный 4 точками.
# Она принимает координаты робота (robot) и координаты 4 точек перекрестка (point1, point2, point3, point4).
def check_crossroad(robot, point1, point2, point3, point4) -> bool: 
    # Проверяем, находится ли робот внутри перекрестка, используя условия пересечения прямоугольников.
    return (
        robot[0] >= point1[0] and robot[1] >= point1[1] and
        robot[0] <= point2[0] and robot[1] >= point2[1] and
        robot[0] <= point3[0] and robot[1] <= point3[1] and
        robot[0] >= point4[0] and robot[1] <= point4[1]
    )

# Функция check_collision проверяет пересечение двух прямых, заданных коэффициентами a, b, c.
# Она принимает список коэффициентов coefficients, где каждый элемент - кортеж (a, b, c) для одной прямой.
def check_collision(coefficients) -> list:
    collisions = []
    for i in range(len(coefficients)):
        for j in range(i + 1, len(coefficients)):
            a1, b1, c1 = coefficients[i]
            a2, b2, c2 = coefficients[j]
            
            # Создаем матрицу из коэффициентов a и b для двух прямых.
            matrix = np.array([[a1, b1], [a2, b2]])
            
            # Проверяем ранг матрицы, чтобы определить, пересекаются ли прямые.
            if np.linalg.matrix_rank(matrix) == 2:
                collisions.append((i, j))
                collisions.append((j, i))
        
    collisions.sort()

    return collisions

# Функция check_path вычисляет общее расстояние между точками в списке points_list.
def check_path(points_list) -> float:
    if len(points_list) < 2:
        return 0.0
    
    points_array = np.array(points_list)
    deltas = np.diff(points_array, axis=0)
    
    # Используем np.linalg.norm для вычисления евклидовых расстояний между точками.
    distances = np.linalg.norm(deltas, axis=1)
    total_distance = np.sum(distances)
    
    return round(total_distance, 2)




