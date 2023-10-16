#ifndef NEURALNETWORK
#define NEURALNETWORK
#include <vector>
#include "Neuron.hpp"
#include <iostream>
#include <cassert>

typedef std::vector<Neuron> Layer;

class NeuralNetwork{
private:
    std::vector<Layer> m_layers;
    double m_error;
    double m_recentAverageError;
    static double m_recentAverageSmoothingFactor;
public:
    NeuralNetwork(const std::vector<unsigned> &topology);
    void feedForward(const std::vector<double> &inputs);
    void backProp(const std::vector<double> &targetVals);
    void getResults(std::vector<double> &resultVals) const;
    double getRecentAverageError(void) const;
};

#endif