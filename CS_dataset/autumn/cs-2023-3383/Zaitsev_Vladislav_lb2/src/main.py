from PIL import Image, ImageDraw
import numpy as np
import math
import PIL.ImageOps

def pentagram(img, x0, y0, x1, y1, thickness, color):
    drawing = ImageDraw.Draw(img)
    drawing.ellipse( ((x0,y0) , (x1, y1)), None, (color[0], color[1], color[2]), thickness)
    peaks = np.empty((5, 2))
    for i in range(0,5):
        phi = (math.pi/5)*(2*i+3/2)
        r = (x1 - x0) // 2
        x = r + x0
        y = r + y0
        peaks[i][0] = int((x+r*math.cos(phi)))
        peaks[i][1] = int((y+r*math.sin(phi)))
    for i in range(0,5):
        if i <= 2:
          drawing.line( ((peaks[i][0], peaks[i][1]), (peaks[i+2][0], peaks[i+2][1])), (color[0], color[1], color[2]), thickness)
        else:
          drawing.line( ((peaks[i][0], peaks[i][1]), (peaks[i-3][0], peaks[i-3][1])), (color[0], color[1], color[2]), thickness)
    return img
def invert(img, N,vertical):
    image_data = np.asarray(img, dtype = np.uint8)
    if vertical == True:
        width = image_data.shape[1]
        columns_count = width // N
        current_width = N
        first_slice = image_data[:, 0:N, :]
        for i in range(1, columns_count):
            if i % 2 != 0:
                new_slice = image_data[:,current_width:current_width + N, :]
                current_width += N
                inverted_img = np.asarray(PIL.ImageOps.invert(Image.fromarray(new_slice)))
                first_slice = np.hstack((first_slice, inverted_img))
            else:
                new_slice = image_data[:,current_width:current_width + N, :]
                current_width += N 
                first_slice = np.hstack((first_slice, new_slice))
        if (width / N > columns_count) and ((N+1) % 2 != 0):
            new_slice = image_data[:,current_width:, :]
            inverted_img = np.asarray(PIL.ImageOps.invert(Image.fromarray(new_slice)))
            first_slice = np.hstack((first_slice, new_slice))
        elif (width / N > columns_count) and ((N+1) % 2 == 0):
            new_slice = image_data[:,current_width:, :]
            first_slice = np.hstack((first_slice, new_slice))
    else:
        height = image_data.shape[0]
        rows_count = height // N
        current_height = N
        first_slice = image_data[0:N, :, :]
        for i in range(1, rows_count):
            if i % 2 != 0:
                new_slice = image_data[current_height:current_height+N,:,:]
                current_height += N
                inverted_img = np.asarray(PIL.ImageOps.invert(Image.fromarray(new_slice)))
                first_slice = np.vstack((first_slice, inverted_img))
            else:
                new_slice = image_data[current_height:current_height+N,:,:]
                current_height += N 
                first_slice = np.vstack((first_slice, new_slice))
        if (height / N > rows_count) and ((N+1) % 2 != 0):
            new_slice = image_data[current_height:,:, :]
            inverted_img = np.asarray(PIL.ImageOps.invert(Image.fromarray(new_slice)))
            first_slice = np.vstack((first_slice, new_slice))
        elif (height / N > rows_count) and ((N+1) % 2 == 0):
            new_slice = image_data[current_height:,:,:]
            first_slice = np.vstack((first_slice, new_slice))
    inverted_image = Image.fromarray(first_slice)
    return inverted_image
def mix(img, rules):
    size_seg = int(img.size[0] / 3)
    segments = []
    x1 = 0
    x2 = size_seg
    y1 = 0
    y2 = size_seg
    for x in range(0,9):
        segments.append(img.crop((x1 + (x%3) * size_seg, y1 + (x//3) * size_seg, x2 + (x%3) * size_seg, y2 + (x//3) * size_seg)))
    for item in rules.items():
        dest_ind = int(item[0])
        src_ind = int(item[1])
        img.paste(segments[src_ind], ( x1 + (dest_ind%3) * size_seg, y1 + (dest_ind//3) * size_seg, x2 + (dest_ind%3) * size_seg, y2 + (dest_ind//3) * size_seg))
    return img