#pragma once

#include <vector>

#include "Sound.h"
#include "SoundInfo.h"

namespace IESFX
{
	class Evolution
	{
	public:
		Evolution();
		~Evolution();

		void execute();
		std::vector<SoundInfo>* output();

	private:

		// initialize the population
		//
		void initialize();

		// shuffle population
		//
		void shuffle();

		// evaluate each candidates fitness
		//
		void evaluate(std::pair<SoundInfo, double>& candidate);

		// rank based selection (we can do it because we sort before selection)
		//
		void selection();

		// create new offspring from existing candidates
		//
		void crossover();

		// mutate the new offspring 
		//
		void mutation();

		// stop if maximum generations are reached or there is an individual with sufficient quality
		//
		bool complete(int current_gen, double current_quality);

	private:
		std::vector<std::pair<SoundInfo, double>> _population;
	};
}

