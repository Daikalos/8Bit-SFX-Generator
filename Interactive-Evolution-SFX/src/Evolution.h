#pragma once

#include <vector>
#include <fstream>

#include "Sound.h"
#include "SoundGene.h"

namespace IESFX
{
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
		std::vector<SoundGene> _population;

		std::vector<SoundGene*> _models;
	};
}

