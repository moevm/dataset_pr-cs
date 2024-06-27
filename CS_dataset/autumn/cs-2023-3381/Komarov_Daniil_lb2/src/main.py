import numpy as np
from PIL import Image, ImageDraw


def swap(img, x0,y0,x1,y1,width):
    output_img = img.copy()
    part1 = img.crop((x0, y0, x0+width, y0+width)).transpose(Image.Transpose.ROTATE_270)
    part2 = img.crop((x1, y1, x1+width, y1+width)).transpose(Image.Transpose.ROTATE_270)
    output_img.paste(part2, (x0, y0))
    output_img.paste(part1, (x1, y1))
    return output_img.transpose(Image.Transpose.ROTATE_270)

def avg_color(img, x0,y0,x1,y1):
    output_img = img.copy()
    pixels = img.load()
    output_pixels = output_img.load()
    for x in range(x0, x1+1):
    	for y in range(y0, y1+1):
    		#8 neighboors
    		if((x != 0 and x != img.size[0]-1) and (y != 0 and y != img.size[1]-1)):
    			neighboors = [pixels[xi, yi] for xi in [x-1, x, x+1] for yi in [y-1, y, y+1]]
    			neighboors_count = 8
    		#5 neighboors
    		elif((x != 0 and x != img.size[0]-1) or (y != 0 and y != img.size[1]-1)):
    			if(x == 0):               neighboors = [pixels[xi, yi] for xi in [x, x+1] for yi in [y-1, y, y+1]]
    			elif(x == img.size[0]-1): neighboors = [pixels[xi, yi] for xi in [x-1, x] for yi in [y-1, y, y+1]]
    			elif(y == 0):             neighboors = [pixels[xi, yi] for xi in [x-1, x, x+1] for yi in [y, y+1]]
    			elif(y == img.size[1]-1): neighboors = [pixels[xi, yi] for xi in [x-1, x, x+1] for yi in [y-1, y]]
    			neighboors_count = 5
    		#3 neighboors
    		else:
    			if(x == 0):               xl = [x, x+1]
    			elif(x == img.size[0]-1): xl = [x-1, x]
    			if(y == 0):               yl = [y, y+1]
    			elif(y == img.size[1]-1): yl = [y-1, y]
    			neighboors = [pixels[xi, yi] for xi in xl for yi in yl]
    			neighboors_count = 3
    		#print(x, y, neighboors_count, neighboors, pixels[x, y])
    		neighboors.remove(pixels[x, y])
    		neighboors = list(zip(*neighboors))
    		output_pixels[x, y] = tuple(map(lambda x: int(sum(x)/neighboors_count), neighboors))
    return output_img

def pentagram(img, x, y, r, thickness, color):
    draw = ImageDraw.Draw(img)
    draw.ellipse((x-r, y-r, x+r, y+r), outline=tuple(color), width=thickness)
    points = [(int(x+r*np.cos(phi)),int(y+r*np.sin(phi))) for phi in [(np.pi/5)*(2*i+3/2) for i in range(5)]]
    for i in range(5):
        draw.line((points[(i*2)%5], points[((i+1)*2)%5]), fill=tuple(color), width=thickness)
    return img
