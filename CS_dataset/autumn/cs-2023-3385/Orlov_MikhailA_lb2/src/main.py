import numpy as np
from PIL import Image, ImageDraw

# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
	drawing = ImageDraw.Draw(image)
	drawing.line(((x0, y0), (x1, y1)), fill, width)
	return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
	return all(i >= 0 for i in [x0, y0, x1, y1]) and \
	x1 > x0 and y1 > y0 and \
	all(x <= image.size[0] for x in [x0, x1]) and \
	all(y <= image.size[1] for y in [y0, y1])

def set_black_white(image, x0, y0, x1, y1):
	if not check_coords(image, x0, y0, x1, y1): return image
	cropped = image.crop((x0, y0, x1, y1))
	converted = cropped.convert("1")
	image.paste(converted, (x0, y0))
	return image

# Задача 3
def find_max_rect(image, color):
	pixels = np.array(image)
	mask = np.all(pixels == color, axis=-1)
	pixels = mask.astype(int)
	for x in range(1, len(pixels)):
		for y in range(len(pixels[x])):
			pixels[x][y] *= pixels[x - 1][y] + 1
	M = 0
	coords = None
	for x in range(len(pixels)):
		k = 0
		for p in set(pixels[x]):
			for y in range(len(pixels[x])):
				if p <= pixels[x][y]: k += p
				if y == len(pixels[x]) - 1 or pixels[x][y + 1] < p:
					if M < k:
						M = k
						coords = ((y - k // p + 1, x - p + 1), (y, x))
					k = 0
	return coords

def find_rect_and_recolor(image: Image.Image, old_color, new_color):
	rect = find_max_rect(image, old_color)
	pixels = np.array(image)
	pixels[rect[0][1]:rect[1][1] + 1, rect[0][0]:rect[1][0] + 1, :3] = list(new_color)
	return Image.fromarray(pixels)