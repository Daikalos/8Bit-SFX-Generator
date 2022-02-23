#pragma once

#if _DEBUG

#include <SFML/Graphics.hpp>
#include <random>

#include "Sound.h"
#include "Interpreter.h"
#include "Utilities.h"
#include "Config.h"

namespace IESFX
{
	static sf::Color gradient(double ratio)
	{
		ratio = util::clamp(1.0 - ratio, 0.01, 0.99);

		int normalized = int(ratio * 256 * 4);
		int region = normalized / 256;
		int x = normalized % 256;

		int r = 0, g = 0, b = 0;
		switch (region)
		{
		case 0: r = 255; g = 0;   b = 0;   g += x; break;
		case 1: r = 255; g = 255; b = 0;   r -= x; break;
		case 2: r = 0;   g = 255; b = 0;   b += x; break;
		case 3: r = 0;   g = 255; b = 255; g -= x; break;
		}

		return sf::Color(r, g, b);
	}

	static void heatmap()
	{
		const size_t width = 1024;
		const size_t height = 1024;

		const size_t max = 10;

		const sf::Int16 bounds_height = 700;
		const size_t bounds_width = SAMPLE_RATE;

		const size_t size = 1000;

		int* heatmap = new int[(width + 1) * (height + 1)];
		memset(heatmap, 0, sizeof(heatmap[0]) * (width + 1) * (height + 1));

		std::vector<SoundData> data(size);
		Interpreter interpreter;

		for (size_t i = 0; i < size; ++i)
		{
			//interpreter.read_file(&data[i], "../test.txt");

			data[i].read_poke(24, 15); // always volume on

			size_t commands = util::random(0, 64);
			for (size_t j = 0; j < commands; ++j)
			{
				if (util::random(0.0, 1.0) > 0.15)
					data[i].read_poke(util::random(0, 23), util::random(0, 200));
				else
					data[i].read_sample(util::random(250, 750));
			}

			std::vector<sf::Int16> buffer = data[i].buffer();
			size_t buffer_size = std::min<size_t>(buffer.size(), bounds_width);

			for (size_t j = 0; j < buffer_size; j += (buffer_size / width))
			{
				if (buffer[j] < -bounds_height || buffer[j] > bounds_height)
					continue;

				int x = (j / (double)bounds_width) * width;
				int y = util::scale<sf::Int16>(buffer[j], -bounds_height, bounds_height) * height;

				++heatmap[x + y * width];
			}
		}

		sf::Image image;
		image.create(width, height);

		for (size_t x = 0; x < width; ++x)
		{
			for (size_t y = 0; y < height; ++y)
			{
				image.setPixel(x, y, gradient(heatmap[x + y * width] / (double)max));
			}
		}

		image.saveToFile("../heatmap.png");

		delete[] heatmap;
	}
}

#endif