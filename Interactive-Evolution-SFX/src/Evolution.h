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
		~Evolution();

		void add_model(SoundGene& gene);
		void remove_model(const SoundGene& gene);

		void set_mutation_rate(double value) { _mutation_rate = value; }
		void set_mutation_size(double value) { _mutation_size = value; }

		void reset();

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
		bool complete(int current_generation, double current_quality);

	private:
		size_t 
			_offspring_size,  
			_max_generations;
		double 
			_max_quality, 
			_mutation_rate, 
			_mutation_size;

		std::vector<SoundGene> _population;
		std::vector<SoundGene> _models;

		std::vector<SoundGene> _old_population;
		std::vector<SoundGene> _old_models;
	};
}

