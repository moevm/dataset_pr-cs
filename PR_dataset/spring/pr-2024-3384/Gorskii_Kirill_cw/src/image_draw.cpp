#include "image.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstdio>

void Image::fillCircle(vec2f mid, float radius, rgba32 color)
{
	if (mid.x + radius < 0 || mid.x - radius >= width || mid.y + radius < 0 || mid.y - radius >= height)
		return;

	int minx = std::max(0.f, floorf(mid.x - radius));
	int maxx = std::min(width - 1.f, ceilf(mid.x + radius));
	int miny = std::max(0.f, floorf(mid.y - radius));
	int maxy = std::max(height - 1.f, ceilf(mid.y + radius));
	
    for (int x = minx; x <= maxx; x++) {
        for (int y = miny; y <= maxy; y++) {
            float fx = x + 0.5f;
			float fy = y + 0.5f;
			if ((fx-mid.x)*(fx-mid.x) + (fy-mid.y)*(fy-mid.y) < radius * radius)
               setPixel(vec2i(x, y), color);
        }
    }
}

void Image::fillCircle(vec2i mid, float radius, rgba32 color)
{
    fillCircle(vec2f(mid.x + 0.5f, mid.y + 0.5f), radius, color);
}

void Image::drawThinLine(vec2i start, vec2i end, rgba32 color)
{
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    if (abs(dx) > abs(dy)) {
        int stepx = dx < 0 ? -1 : 1;
        for (int x = start.x; x != end.x; x += stepx) {
            float y = start.y + (x - start.x) * dy / (float)dx;
            setPixel(vec2i(x, y + 0.5f), color);
        }
    }
    else {
        int stepy = dy < 0? -1 : 1;
        for (int y = start.y; y != end.y; y += stepy) {
            float x = start.x + (y - start.y) * dx / (float)dy;
            setPixel(vec2i(x, y + 0.5f), color);
        }
    }

    setPixel(end, color);
}

void Image::drawLine(vec2i start, vec2i end, rgba32 color, int thickness)
{
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    if (abs(dx) > abs(dy)) {
        int stepx = dx < 0 ? -1 : 1;
        for (int x = start.x; x != end.x; x += stepx) {
            float y = start.y + (x - start.x) * dy / (float)dx;
            fillCircle(vec2f(x, y + 0.5f), thickness / 2.f, color);
        }
    }
    else {
        int stepy = dy < 0? -1 : 1;
        for (int y = start.y; y != end.y; y += stepy) {
            float x = start.x + (y - start.y) * dx / (float)dy;
            fillCircle(vec2f(x, y + 0.5f), thickness / 2.f, color);
        }
    }

    fillCircle(end, thickness / 2.f, color);
}

void Image::drawTriangle(vec2i p1, vec2i p2, vec2i p3, rgba32 color, int thickness)
{
    drawLine(p1, p2, color, thickness);
	drawLine(p2, p3, color, thickness);
	drawLine(p3, p1, color, thickness);
}

bool is_top_left(vec2f edge)
{
	return (edge.x > 0 && edge.y == 0) || (edge.y < 0);
}

void Image::fillTriangle(vec2i p1, vec2i p2, vec2i p3, rgba32 color, float bias)
{
	fillTriangle(
        vec2f(p1) + vec2f(0.5f, 0.5f),
        vec2f(p2) + vec2f(0.5f, 0.5f),
        vec2f(p3) + vec2f(0.5f, 0.5f),
        color, bias
    );
}

void Image::fillTriangle(vec2f p1, vec2f p2, vec2f p3, rgba32 color, float bias)
{
	if ((p2 - p1).cross_z(p3 - p2) < 0)
    	std::swap(p2, p3);

	int xmin = std::min(std::min(p1.x, p2.x), p3.x);
	int xmax = std::max(std::max(p1.x, p2.x), p3.x);
	int ymin = std::min(std::min(p1.y, p2.y), p3.y);
	int ymax = std::max(std::max(p1.y, p2.y), p3.y);

    vec2f v1 = p2 - p1;
	vec2f v2 = p3 - p2;
	vec2f v3 = p1 - p3;

	float bias1 = is_top_left(v1) ? 0 : -bias;
	float bias2 = is_top_left(v2) ? 0 : -bias;
	float bias3 = is_top_left(v3) ? 0 : -bias;

	for (int x = xmin; x <= xmax; x++) {
		for (int y = ymin; y <= ymax; y++) {
			vec2f cur(x + 0.5f, y + 0.5f);
			float cross1 = v1.cross_z(cur - p1) + bias1;
            float cross2 = v2.cross_z(cur - p2) + bias2;
            float cross3 = v3.cross_z(cur - p3) + bias3;

			if (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) {
				setPixel(vec2i(x, y), color);
			}
		}
	}
}

void Image::fillRect(rect2i rect, rgba32 color)
{
	if (rect.min.x < 0) rect.min.x = 0;
	if (rect.min.y < 0) rect.min.y = 0;
	if (rect.max.x > this->width) rect.max.x = this->width;
	if (rect.max.y > this->height) rect.max.y = this->height;

	for (int y = rect.min.y; y < rect.max.y; y++) {
		for (int x = rect.min.x; x < rect.max.x; x++) {
			setPixel(vec2i(x, y), color);
		}
	}
}
