#pragma once

#if !BUILD

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>

#include "Sound.h"
#include "Interpreter.h"
#include "Utilities.h"
#include "Config.h"
#include "Evolution.h"

#ifdef NATIVE_CODE
#include <execution>
#endif

namespace IESFX
{
	class Heatmap
	{
	public:
		static void heatmap_0();
		static void heatmap_1();

	private:
		static sf::Color gradient(double ratio);
		static void plot_line(int* heatmap, int width, int x0, int y0, int x1, int y1, int dx, int dy);
	};
}

#endif