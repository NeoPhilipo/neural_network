#ifndef NEURON
#define NEURON
#include <vector>
#include <cstdlib>
#include <cmath>
//#include "NeuralNetwork.hpp"

//typedef std::vector<Neuron> Layer;

struct Connection{
    double weight;
    double deltaWeights;
};


class Neuron{
private:
    double m_outputVal;
    std::vector<Connection> m_outputWeights;
    unsigned n_index;
    double sumDOW(const std::vector<Neuron> &nextLayer) const;
    static double eta;
    static double alpha;
    static double transferFunction(double value);
    static double transferFunctionDerivative(double value);
    double m_gradient;
public:
    Neuron(unsigned outputNum, unsigned index);
    static double randomWeights();
    void feedForward(const std::vector<Neuron> &prevLayer);
    void setOutputVal(const double &inputVals);
    double getOutputVal(void) const;
    void calcOutputGradients(double targetVal);
    void calcHiddenGradients(const std::vector<Neuron> &nextLayer);
    void updateInputWeights(std::vector<Neuron> &prevLayer);
};

#endif