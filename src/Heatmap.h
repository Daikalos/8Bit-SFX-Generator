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
		static void heatmap_2();
		static void heatmap_3();

	private:
		static sf::Color gradient(double ratio);
		static void plot_line(int* heatmap, int width, int x0, int y0, int x1, int y1, int dx, int dy);
	};
}

#endif