#pragma once

#include <vector>
#include <fstream>

#ifdef NATIVE_CODE
#include <execution>
#endif

#include "Sound.h"
#include "SoundGene.h"
#include "GeneExamples.h"
#include "Utilities.h"

namespace IESFX
{
	class Evolution
	{
	public:
		Evolution(double mutation_rate, double mutation_size);
		~Evolution() = default;

		void set_mutation_rate(double value) { _mutation_rate = value; }
		void set_mutation_size(double value) { _mutation_size = value; }

		double generation() const { return (_max_generations == 0) ? 0.0 : _generations / (double)_max_generations; }
		double quality() const { return (_max_quality == 0) ? 0.0 : _quality / _max_quality; }

		bool active() const { return _active; }

		void add_model(SoundGene& gene);
		void remove_model(const SoundGene& gene);

		void reset();
		bool retry();

		int execute(size_t max_generations = GENERATIONS, double max_quality = QUALITY);
		std::vector<SoundGene> output(size_t size, size_t step);

		bool save(const std::string& filename) const;
		bool load(const std::string& filename);

	private:

		// initialize the population
		//
		void initialize();

		// shuffle population
		//
		void shuffle();

		// evaluate each candidates fitness
		//
		void evaluate(SoundGene& candidate);

		// rank based selection (we can do it because we sort before selection)
		//
		void selection();

		// create new offspring from existing candidates, uniform crossover
		//
		void crossover();

		// mutate the new offspring 
		//
		void mutation();

		// stop if maximum generations are reached or there is a a individual with sufficient quality
		//
		bool complete();

	private:
		size_t 
			_offspring_size{0},
			_generations{0},
			_max_generations{0};
		double 
			_quality{0.0},
			_max_quality{0.0},
			_mutation_rate, 
			_mutation_size;
		bool
			_active{false};

		std::vector<SoundGene> _population;
		std::vector<SoundGene> _models;

		std::vector<SoundGene> _old_population;
	};
}

