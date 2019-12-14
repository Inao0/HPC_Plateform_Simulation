#pragma once

#include <random>

class Random {
public:


	static double exponential(double mean) {
        std::random_device rd;
        std::mt19937 rnd_gen(rd());
        std::exponential_distribution<> rng(mean);
		return rng(rnd_gen);
	}

    static double uniformDouble(double min, double max) {
        std::random_device rd;
        std::mt19937 rnd(rd());
        std::uniform_real_distribution <double> uni (min,max);
        return uni(rnd);
    }
    /*
 * 99.7 % of the sample will be in the interval [mean - 3 stddev; mean +3 stddev]
 */
    static double normalDouble(double mean, double stddev) {
        std::random_device rd;
        std::mt19937 rnd(rd());
        std::normal_distribution <double> norm (mean,stddev);
        return norm(rnd);
    }
    static int binomialInt(int n, double p) {
        std::random_device rd;
        std::mt19937 rnd(rd());
        std::binomial_distribution<int> bin (n,0.5);
        return bin(rnd);
    }

    static double uniformInt(double min, double max) {
        std::random_device rd;
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased //
        return uni(rng);
    }

};