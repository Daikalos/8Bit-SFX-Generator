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
	static const size_t MAX_GENERATIONS = 100;
	static const size_t MAX_QUALITY = 1.0;

	class Evolution
	{
	public:
		Evolution();
		~Evolution();

		void add_model(SoundGene* gene)
		{
			_models.push_back(gene);
		}
		void remove_model(SoundGene* gene)
		{
			_models.erase(std::remove_if(_models.begin(), _models.end(), [gene](SoundGene* model)
			{
				return gene == model;
			}), _models.end());
		}

		void set_mutation_rate(double value) { _mutation_rate = value; }
		void set_mutation_size(double value) { _mutation_size = value; }

		void reset();

		int execute();
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

		// create new offspring from existing candidates
		//
		void crossover();

		// mutate the new offspring 
		//
		void mutation();

		// stop if maximum generations are reached or there is an individual with sufficient quality
		//
		bool complete(int generation, double quality);

	private:
		double _mutation_rate, _mutation_size;
		std::vector<SoundGene> _population;

		std::vector<SoundGene*> _models;
	};
}

