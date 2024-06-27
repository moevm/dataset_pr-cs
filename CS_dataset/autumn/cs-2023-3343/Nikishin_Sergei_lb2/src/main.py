from PIL import Image, ImageDraw, ImageOps
from numpy import pi, cos, sin
import math
 
def pentagram(img, x0, y0, x1, y1, tolcshina, cvet):
    cvet = tuple(cvet)
    kartinka = ImageDraw.Draw(img)
    kartinka.ellipse(((x0, y0), (x1, y1)), None, cvet, tolcshina)
    okruglen = round((x1 - x0) / 2)
    uzli = {}
    x = round(x0 + okruglen)
    y = round(y0 + okruglen)
    for i in range(5):
        phi = (pi / 5) * (2 * i + 3 / 2)
        uzel = (int(x + okruglen * cos(phi)), int(y + okruglen * sin(phi)))
        uzli[i] = [uzel, i + 1]
        if i == 4:
            uzli[i] = [uzel, 0]
    for i in range(5):
        sleduzl = uzli[uzli[i][1]]
        posleduzl = uzli[sleduzl[1]]
        kartinka.line((uzli[i][0], posleduzl[0]), cvet, tolcshina)
    return img
 
def invert(img, N, vertical):
    razmer = img.size
    nomeraziastrok = int(math.ceil(razmer[0] / N))
    for i in range(nomeraziastrok):
        if vertical:
            obrez = img.crop((N * i, 0, N * (i + 1), razmer[1]))
        else:
            obrez = img.crop((0, N * i, razmer[1], N * (i + 1)))
        if i % 2 != 0:
            obrez = ImageOps.invert(obrez)
        if vertical:
            img.paste(obrez, (N * i, 0))
        else:
            img.paste(obrez, (0, N * i))
    return img
 
def mix(img, rules):
    razmer = img.size
    obrezrazmer = (razmer[0] // 3, razmer[1] // 3)
    obrezpikchas = []
    for i in range(3):
        for j in range(3):
            levo = (j * obrezrazmer[0], i * obrezrazmer[1])
            pravo = ((j + 1) * obrezrazmer[0], (i + 1) * obrezrazmer[1])
            obrezpikcha = img.crop((levo[0], levo[1], pravo[0], pravo[1]))
            obrezpikchas.append(obrezpikcha)
    schet = 0
    for i in range(3):
        for j in range(3):
            obrezpikcha = obrezpikchas[rules[schet]]
            schet += 1
            img.paste(obrezpikcha, (j * obrezrazmer[0], i * obrezrazmer[1]))
    return img
