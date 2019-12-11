#pragma once

#include <random>

class Random {
public:
	static double exponential(double mean) {

		std::random_device rd;

		std::exponential_distribution<> rng(mean);
		std::mt19937 rnd_gen(rd());

		return rng(rnd_gen);
	}
};