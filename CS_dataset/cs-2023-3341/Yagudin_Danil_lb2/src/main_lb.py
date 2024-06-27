from PIL import Image, ImageDraw
import numpy as np

def triangle(img, x0, y0, x1, y1, x2, y2, thickness, color, fill_color):

    cp = ImageDraw.Draw(img)
    points = [(x0, y0), (x1, y1), (x2, y2)]
    color = (color[0], color[1], color[2])

    if fill_color != None:
        fill_color = (fill_color[0], fill_color[1], fill_color[2])
        cp.polygon(points, outline = color, fill = fill_color, width = thickness)
    else:
        cp.polygon(points, outline = color, width = thickness)

    return img


def change_color(img, color):

    img_arr = np.array(img)
    h, w, c = img_arr.shape
    imgr = img_arr.reshape((h * w, c))

    unique, k = np.unique(imgr, axis=0, return_counts = True)
    common = np.argmax(k)

    img_arr[(img_arr == unique[common]).all(axis =-1)] = color
    result_img = Image.fromarray(img_arr)

    return result_img

def collage(img, N, M):

    img_size = img.size
    result = Image.new("RGB", (img_size[0] * M, img_size[1] * N), "red")

    for i in range(N):
        for j in range(M):
            x = j * img_size[0]
            y = i * img_size[1]
            result.paste(img, (x, y))

    return result
