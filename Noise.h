#pragma once
#include <random>

class Noise {
public:
    Noise() : gen(std::random_device{}()) {}

    double gaussian(double mean = 0.0, double stddev = 1.0) {
        std::normal_distribution<double> dist(mean, stddev);
        return dist(gen);
    }

    double beta(double alpha, double beta) {
        std::gamma_distribution<double> gamma_a(alpha, 1.0);
        std::gamma_distribution<double> gamma_b(beta, 1.0);

        double y1 = gamma_a(gen);
        double y2 = gamma_b(gen);

        return y1 / (y1 + y2);
    }

private:
    std::mt19937 gen;
};
