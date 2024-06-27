import numpy as np

def check_collision(bot1, bot2):

  #извлечение коэффицентов прямых
  a1,b1,c1=bot1
  a2,b2,c2=bot2

  # создание матрицы коэффицентов
  coeff_matrix=np.array([[a1,b1],[a2,b2]])
  #создание вектора свободных членов
  const_vector=np.array([-c1, -c2])

  #проверка ранга матрицы с коэффицентами
  if np.linalg.matrix_rank(coeff_matrix)!=2:
      return None

  #решение системы уравнений
  system_solution=np.round(np.linalg.solve
  (coeff_matrix,const_vector),2)
  intersects=(system_solution[0],system_solution[1])

  return intersects

def check_surface(point1, point2, point3):
  # создание матрицы координат точек
  points_matrix=np.array([point1,point2,point3])

  if np.linalg.matrix_rank(points_matrix)!=3:
      return None

  # извлечение координат x, y, z точек
  x=points_matrix[:,0]
  y=points_matrix[:,1]
  z=points_matrix[:,2]

  coeff_matrix= np.column_stack((x,y,np.ones(3)))
  coeff= np.round(np.linalg.solve(coeff_matrix,z),2)
  return (coeff)

def check_rotation(vec, rad):
  rotation_matrix=np.array([[np.cos(rad), np.sin(rad), 0],
                                [-np.sin(rad), np.cos(rad), 0],
                                [0, 0, 1]])
  rotated_coord= np.round(np.dot(vec,rotation_matrix),2)
  return (rotated_coord)


