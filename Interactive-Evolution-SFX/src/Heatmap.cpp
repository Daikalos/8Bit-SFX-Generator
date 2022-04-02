//  ---------------------------------------------------------------------------
//  This file is part of the 8-Bit SFX Generator
//	Copyright (C) 2022 Tobias Garpenhall <tobiasgarpenhall@gmail.com>
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program. If not, see <http://www.gnu.org/licenses/>.
//  ---------------------------------------------------------------------------

#define NATIVE_CODE
#include "Heatmap.h"

#if !BUILD

using namespace IESFX;

void Heatmap::heatmap_0()
{
	const size_t width = 1024;
	const size_t height = 1024;

	const sf::Int16 bounds_height = 17000;
	const size_t bounds_width = SAMPLE_RATE * 1.5;

	const size_t size = 10000;

	double max = 0;

	int* heatmap = new int[width * height];
	memset(heatmap, 0, sizeof(heatmap[0]) * width * height);

	std::vector<SoundGene> population(size);

	std::for_each(
		std::execution::par_unseq,
		population.begin(), population.end(),
		[&](SoundGene& gene)
		{
			gene.push({ 24, 14 }); // always volume on

			std::vector<RESID::reg8> offsets(util::random<RESID::reg8>(24));

			for (int s = util::random(1, 7); s > 0; --s)
			{
				for (int p = util::random(1, 23); p > 0; --p)
				{
					gene.push({ offsets[p], util::rvpoke() });
				}
				gene.push({ util::rsample() });
				offsets = util::random<RESID::reg8>(24);
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

	std::for_each(
		std::execution::par_unseq,
		heatmap, heatmap + (int)(width * height),
		[&max](const int& val)
		{
			if (val > max)
				max = val;
		});

	max = std::pow(max, 0.6);

	for (size_t x = 0; x < width; ++x)
	{
		for (size_t y = 0; y < height; ++y)
		{
			image.setPixel(x, y, gradient(heatmap[x + y * width] / max));
		}
	}

	image.saveToFile("../misc/heatmap_0.jpg");

	delete[] heatmap;
}

void Heatmap::heatmap_1()
{
	const size_t width = 161;
	const size_t height = 161;

	const size_t size = 1024;

	double max = DBL_MIN;

	int* heatmap = new int[width * height];
	memset(heatmap, 0, sizeof(heatmap[0]) * width * height);

	std::vector<int> range(size);

	std::for_each(std::execution::seq,
		range.begin(), range.end(),
		[&](const int&)
		{
			Evolution* evolution = new Evolution(
				util::random(0.01, 0.5), 
				util::random(0.01, 0.5));

			for (int i = util::random(1, 24); i > 0; --i)
			{
				evolution->execute(
					util::random(45LLU, GENERATIONS),
					util::random(1.5, QUALITY));

				std::vector<SoundGene> population(evolution->output(256, 0));

				std::for_each(
					std::execution::par_unseq,
					population.begin(), population.end(),
					[&](const SoundGene& gene)
					{
						std::vector<std::tuple<int, int, int>> range = gene.range<int>();

						double average = 0.0;
						double size = 0.0;

						for (int si = 0; si < range.size(); ++si)
						{
							std::vector<bool> offsets(25, false);
							for (int j = std::get<1>(range[si]) - 1; j >= std::get<0>(range[si]); --j)
							{
								Poke* poke = static_cast<Poke*>(gene.get(j));
								if (!offsets[poke->offset])
								{
									offsets[poke->offset] = true;

									average += poke->value;
									++size;
								}
							}
						}

						if (size <= DBL_EPSILON)
							return;

						average /= size;

						int x = std::clamp<double>(average / POKE_VALUE, 0.0, 1.0) * (width - 1);
						int y = (1.0 - std::clamp<double>(size / 161, 0.0, 1.0)) * (height - 1);

						++heatmap[x + y * width];
					});

				std::vector<size_t> indices;
				for (int j = util::random(1, 3); j > 0; --j)
				{
					size_t index = util::random<size_t>(0, population.size() - 1);

					if (std::find(indices.begin(), indices.end(), index) == indices.end())
					{
						evolution->add_model(population[index]);
						indices.push_back(index);
					}
				}
			}

			delete evolution;
		});

	sf::Image image;
	image.create(width, height);

	std::for_each(
		std::execution::par_unseq,
		heatmap, heatmap + (width * height),
		[&max](const int& val)
		{
			if (val > max)
				max = val;
		});

	max = std::pow(max, 0.75);

	for (size_t x = 0; x < width; ++x)
	{
		for (size_t y = 0; y < height; ++y)
		{
			int val = heatmap[x + y * width];

			if (val == 0)
				image.setPixel(x, y, sf::Color::Black);
			else
				image.setPixel(x, y, gradient(val / max));
		}
	}

	image.saveToFile("../misc/heatmap_1.jpg");

	delete[] heatmap;
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

#endif
