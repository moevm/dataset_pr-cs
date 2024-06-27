from PIL import Image, ImageDraw
import numpy

# Задача 1
def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):
    drawing = ImageDraw.Draw(img)
    if fill_color != None:
        drawing.polygon(((x0,y0), (x1,y1), (x2,y2)), tuple(fill_color), tuple(color), thickness)
    else:
        drawing.polygon(((x0,y0), (x1,y1), (x2,y2)), None, tuple(color), thickness)
    return img
    


# Задача 2
def change_color(img, color):
    col_dict = {}
    res_col = []
    col_counter = 0
    res = img.copy()
    
    for width in range (0,res.size[0]):
        for length in range (0,res.size[1]):
            if res.getpixel((width, length)) not in col_dict:
                col_dict[res.getpixel((width, length))] = 1
            else:
                col_dict[res.getpixel((width, length))] +=1
    
    for col in col_dict.keys():
        if col_dict[col] > col_counter:
            col_counter = col_dict[col]
            res_col.append(col)
    
    col = res_col[::-1][0]
    
    for width in range (0,res.size[0]):
        for length in range (0,res.size[1]):
            if res.getpixel((width, length)) == col:
                res.putpixel((width, length), tuple(color))
    return res


# Задача 3
def collage(img, N, M):
    res = Image.new("RGB", (img.size[0]*M, img.size[1]*N), 'white')
    for x in range(0, img.size[0]*(M-1)+1, img.size[0]):
        for y in range(0, img.size[1]*(N-1)+1, img.size[1]):
            res.paste(img, (x,y))
    return res
