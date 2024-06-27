import numpy as np
from PIL import Image, ImageDraw
import math

def pentagram(image, centerX, centerY, radius, line_thickness, line_color):
    pentagram_draw = ImageDraw.Draw(image)

    star_vertices = []
    for vertex in range(5):
        angle = (math.pi / 5) * (2 * vertex + 1.5)
        vertex_x = int(centerX + radius * math.cos(angle))
        vertex_y = int(centerY + radius * math.sin(angle))
        star_vertices.append((vertex_x, vertex_y))

    pentagram_draw.ellipse((centerX - radius, centerY - radius, centerX + radius, centerY + radius), outline=tuple(line_color), width=line_thickness)

    for vertex in range(5):
        next_vertex = (vertex + 2) % 5
        pentagram_draw.line((star_vertices[vertex], star_vertices[next_vertex]), fill=tuple(line_color), width=line_thickness)

    return image

def crop_and_rotate(image, posX, posY, size):
    cropped_image = image.crop((posX, posY, posX + size, posY + size))
    rotated_image = cropped_image.rotate(270)
    return rotated_image

def swap(original_image, posX1, posY1, posX2, posY2, size):
    part1 = crop_and_rotate(original_image, posX1, posY1, size)
    part2 = crop_and_rotate(original_image, posX2, posY2, size)
    result_image = original_image.copy()
    result_image.paste(part1, (posX2, posY2))
    result_image.paste(part2, (posX1, posY1))
    return result_image.rotate(270)

def calculate_avg_color(source_image, coordX, coordY):
    image_width, image_height = source_image.size
    pixel_data = source_image.load()
    adjacent_pixels = []
    for deltaX in range(-1, 2):
        for deltaY in range(-1, 2):
            if 0 <= (coordX + deltaX) < image_width and 0 <= (coordY + deltaY) < image_height:
                adjacent_pixels.append(pixel_data[coordX + deltaX, coordY + deltaY])
    adjacent_pixels.remove(pixel_data[coordX, coordY])
    avg_color = [0, 0, 0]
    for color in adjacent_pixels:
        for color_index in range(3):
            avg_color[color_index] += color[color_index]
    avg_color = [int(color_sum / len(adjacent_pixels)) for color_sum in avg_color]
    return tuple(avg_color)

def avg_color(image, leftX, topY, rightX, bottomY):
    image_copy = image.copy()
    image_pixels = image_copy.load()
    for posX in range(leftX, rightX + 1):
        for posY in range(topY, bottomY + 1):
            image_pixels[posX, posY] = calculate_avg_color(image, posX, posY)
    return image_copy

def calculate_vertex(number, centerX, centerY, radius):
    angle = (np.pi / 5) * (2 * number + 1.5)
    vertex = (int(centerX + radius * np.cos(angle)), int(centerY + radius * np.sin(angle)))
    return vertex
