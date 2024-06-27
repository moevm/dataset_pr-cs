import numpy

def check_collision(bot1, bot2):
    index = [[bot1[0],bot1[1]],[bot2[0],bot2[1]]]
    vector = [-bot1[2],-bot2[2]]
    crossingPoint = numpy.round(numpy.linalg.solve(index,vector),2)
    return tuple(crossingPoint)

def check_surface(point1, point2, point3):
    index1 = [point1[0], point1[1], 1]
    index2 = [point2[0], point2[1], 1]
    index3 = [point3[0], point3[1], 1]
    vector = [point1[2], point2[2], point3[2]]
    if numpy.linalg.matrix_rank([index1, index2, index3]) != 3:
        return None
    equation = numpy.round(numpy.linalg.solve([index1, index2, index3],vector),2)
    return equation

def check_rotation(vec, rad):
    line1 = [numpy.cos(rad),-numpy.sin(rad)]
    line2 = [numpy.sin(rad),numpy.cos(rad)]
    line = numpy.vstack((line1,line2))
    vector = [vec[0],vec[1]]
    twoDimensions = numpy.round(numpy.dot(line,vector),2)
    threeDimensions = numpy.append(twoDimensions,vec[2])
    return threeDimensions
