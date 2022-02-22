#pragma once

#include <vector>

#include "Sound.h"
#include "SoundData.h"

namespace IESFX
{
	class Evolution
	{
	public:
		Evolution();
		~Evolution();

		void set_mutation_rate(double value)
		{
			_mutation_rate = value;
		}
		void set_mutation_size(double value)
		{
			_mutation_size = value;
		}

		void reset();

		void execute();
		std::vector<SoundData>* output(size_t size, size_t step);

	private:

		// initialize the population
		//
		void initialize();

		// shuffle population
		//
		void shuffle();

		// evaluate each candidates fitness
		//
		void evaluate(std::pair<SoundData, double>& candidate);

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
		double _mutation_rate, _mutation_size;
		std::vector<std::pair<SoundData, double>> _population;
	};
}

