#define NATIVE_CODE
#include "Heatmap.h"

using namespace IESFX;

void Heatmap::heatmap_0()
{
	const size_t width = 1024;
	const size_t height = 1024;

	const sf::Int16 bounds_height = 17000;
	const size_t bounds_width = SAMPLE_RATE * 1.5;

	const size_t size = 10000;

	double max = 0;

	int* heatmap = new int[(width + 1) * (height + 1)];
	memset(heatmap, 0, sizeof(heatmap[0]) * (width + 1) * (height + 1));

	std::vector<int> range(size);

	std::for_each(
		std::execution::par_unseq,
		range.begin(), range.end(), 
		[&](const int&)
		{
			SoundGene gene;

			gene.push({ 24, 14 }); // always volume on

			std::vector<RESID::reg8> offsets(util::random<RESID::reg8>(24));

			for (size_t j = 0, index = 0, size = util::random(0, 128); j < size; ++j)
			{
				if (util::random() > 0.1 && index < offsets.size())
					gene.push({ offsets[index++], util::rvpoke() });
				else
				{
					gene.push({ util::rsample() });

					offsets = util::random<RESID::reg8>(24);
					index = 0;
				}
			}

			std::vector<sf::Int16> buffer = SoundData()(gene);

			int x0 = 0, y0 = 0;
			for (int x1 = 0; x1 < width; ++x1)
			{
				int j = (int)util::map(x1, 0, (int)width, 0, (int)buffer.size());

				if (j >= buffer.size() || std::abs(buffer[j]) > bounds_height)
					continue;

				int y1 = (1.0 - util::scale<sf::Int16>(buffer[j], -bounds_height, bounds_height)) * height;

				if (x1 > 0)
				{
					//int dx = std::abs(x1 - x0);
					//int dy = std::abs(y1 - y0);
					//plot_line(heatmap, width, x0, y0, x1, y1, dx, dy);

					bool dir = (y0 < y1);
					for (int y = y0; dir ? y < y1 : y > y1; dir ? ++y : --y)
						++heatmap[x0 + y * width];
				}

				x0 = x1;
				y0 = y1;
			}
		});

	sf::Image image;
	image.create(width, height);

	for (size_t x = 0; x < width; ++x)
	{
		for (size_t y = 0; y < height; ++y)
		{
			if (heatmap[x + y * width] > max)
				max = heatmap[x + y * width];
		}
	}

	max = std::pow(max, 0.6);

	for (size_t x = 0; x < width; ++x)
	{
		for (size_t y = 0; y < height; ++y)
		{
			image.setPixel(x, y, gradient(heatmap[x + y * width] / max));
		}
	}

	image.saveToFile("../misc/heatmap.jpg");

	delete[] heatmap;
}

void Heatmap::heatmap_1()
{
	const size_t width = 1024;
	const size_t height = 1024;

	const sf::Int16 bounds_height = 17000;
	const size_t bounds_width = SAMPLE_RATE * 1.5;

	const size_t size = 64;

	double max = 0;

	int* heatmap = new int[(width + 1) * (height + 1)];
	memset(heatmap, 0, sizeof(heatmap[0]) * (width + 1) * (height + 1));

	Evolution* _evolution = new Evolution(0.13, 0.09);

	std::vector<int> range(size);

	std::for_each(
		std::execution::par_unseq,
		range.begin(), range.end(),
		[&](const int&)
		{

		});

	sf::Image image;
	image.create(width, height);

	for (size_t x = 0; x < width; ++x)
	{
		for (size_t y = 0; y < height; ++y)
		{
			if (heatmap[x + y * width] > max)
				max = heatmap[x + y * width];
		}
	}

	max = std::pow(max, 0.6);

	for (size_t x = 0; x < width; ++x)
	{
		for (size_t y = 0; y < height; ++y)
		{
			image.setPixel(x, y, gradient(heatmap[x + y * width] / max));
		}
	}

	image.saveToFile("../misc/heatmap.jpg");

	delete[] heatmap;
	delete _evolution;
}

sf::Color IESFX::Heatmap::gradient(double ratio)
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

void Heatmap::plot_line(int* heatmap, int width, int x0, int y0, int x1, int y1, int dx, int dy)
{
	if (x0 == x1 && y0 == y1)
		return;

	if (dx > dy)
	{
		++heatmap[x0 + y0 * width];

		int pk = 2 * dy - dx;
		for (int i = 0; i < dx; ++i)
		{
			x0 < x1 ? ++x0 : --x0;
			if (pk < 0)
				pk += 2 * dy;
			else
			{
				y0 < y1 ? ++y0 : --y0;
				pk += 2 * dy - 2 * dx;
			}
			++heatmap[x0 + y0 * width];
		}
	}
	else
	{
		++heatmap[x0 + y0 * width];

		int pk = 2 * dx - dy;
		for (int i = 0; i < dy; ++i)
		{
			y0 < y1 ? ++y0 : --y0;
			if (pk < 0)
				pk += 2 * dx;
			else
			{
				x0 < x1 ? ++x0 : --x0;
				pk += 2 * dx - 2 * dy;
			}
			++heatmap[x0 + y0 * width];
		}
	}
}
