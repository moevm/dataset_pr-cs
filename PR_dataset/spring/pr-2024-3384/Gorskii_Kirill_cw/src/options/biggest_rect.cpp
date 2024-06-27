#include "../options.hpp"
#include <vector>

struct HistRect {
	uint32_t start;
	uint32_t end;
	uint32_t height;

	uint32_t area() { return height * (end - start); }
};

HistRect getMaxHistRect(std::vector<uint32_t> &hist)
{
	std::vector<HistRect> stack;
	HistRect max_rect = { 0, 0, 0 };
	
	for (uint32_t i = 0; i < hist.size(); i++) {
		uint32_t start = i;
		while (!stack.empty() && stack.back().height >= hist[i]) {
			uint32_t height = stack.back().height;
			start = stack.back().start;
			stack.pop_back();

			HistRect new_rect = { start, i, height };
			if (max_rect.area() < new_rect.area())
				max_rect = new_rect;
		}

		stack.emplace_back(HistRect { start, i, hist[i] });
	}

	for (uint32_t i = 0; i < stack.size(); i++) {
		HistRect new_rect = { stack[i].start, (uint32_t)hist.size(), stack[i].height };
		if (max_rect.area() < new_rect.area())
			max_rect = new_rect;
	}

	return max_rect;
}

void processBiggestRectOption(Image &image, Options& args)
{
	std::vector<uint32_t> hist(image.getWidth());
	for (uint32_t i = 0; i < image.getWidth(); i++) {
		rgba32 color = image.getPixel(vec2i(i, 0));
		hist[i] = (color == args.old_color) ? 1 : 0;
	}

	uint32_t rect_y = 0;
	HistRect rect = getMaxHistRect(hist);

	for (int i = 1; i < image.getHeight(); i++) {
		for (int j = 0; j < image.getWidth(); j++) {
			rgba32 color = image.getPixel(vec2i(j, i));
			hist[j] = (color == args.old_color) ? hist[j] + 1 : 0;
		}

		HistRect new_rect = getMaxHistRect(hist);
		
		if (new_rect.area() >= rect.area()) {
			rect_y = i;
			rect = new_rect;
		}
	}
	
	image.fillRect(rect2i(
		vec2i(rect.start, rect_y - rect.height + 1),
		vec2i(rect.end,   rect_y + 1)),
		args.new_color
	);
}