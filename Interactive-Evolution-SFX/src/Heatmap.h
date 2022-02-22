#pragma once

#if !NDEBUG

#include <SFML/Graphics.hpp>
#include "Sound.h"

namespace IESFX
{
	static void Heatmap()
	{
		const size_t width = 512;
		const size_t height = 512;

		sf::Image heatmap;
		heatmap.create(width, height);



		heatmap.saveToFile("../heatmap.png");
	}
}

#endif