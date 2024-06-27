import numpy as np

def check_collision(bot1, bot2):

  a1, b1, c1 = bot1
  a2, b2, c2 = bot2

  coeffs = np.array([[a1,b1], [a2,b2]])
  vector = np.array([-c1, -c2])
  
  if np.linalg.matrix_rank(coeffs) != 2:
      return None
  
  collision_pos = np.round(np.linalg.solve(coeffs, vector), 2)

  return tuple(collision_pos)

def check_surface(pos1, pos2, pos3):
  pos_matrix = np.array([pos1, pos2, pos3])

  if np.linalg.matrix_rank(pos_matrix) != 3:
      return None

  x = pos_matrix[:, 0]
  y = pos_matrix[:, 1]
  z = pos_matrix[:, 2]

  coeff_matrix = np.column_stack((x, y, np.ones(3)))
  coeffs = np.round(np.linalg.solve(coeff_matrix, z), 2)
  
  return coeffs

def check_rotation(vec, rad):
  rotation_matrix = np.array([[np.cos(rad), np.sin(rad), 0], [-np.sin(rad), np.cos(rad), 0], [0, 0, 1]])
  
  coords = np.round(np.dot(vec, rotation_matrix), 2)
    
  return coords 
