#include "Neuron.hpp"

double Neuron::transferFunction(double value){
    return tanh(value);
}
double Neuron::transferFunctionDerivative(double value){
    return 1-value*value;
}

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

Neuron::Neuron(unsigned outputNum, unsigned index){
    for(unsigned c = 0; c < outputNum; c++){
        this->m_outputWeights.push_back(Connection());
        this->m_outputWeights.back().weight = randomWeights();
    }
    this->n_index = index;
}

double Neuron::randomWeights(){
    return (rand()/static_cast<double>(RAND_MAX));
}

void Neuron::setOutputVal(const double &inputVal){
    this->m_outputVal = inputVal;
}
double Neuron::getOutputVal(void) const {
    return this->m_outputVal;
}
void Neuron::feedForward(const std::vector<Neuron> &prevLayer){
    double sum = 0.0;
    //Loop trought all neuron from previous layer
    //Sum up all neuron outputs from previous layer, which are our inputs
    //Include the bias neuron from previous layer
    for(unsigned n = 0; n < prevLayer.size(); n++){
        sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[n_index].weight;
    }

    this->m_outputVal = Neuron::transferFunction(sum);
}

void Neuron::calcOutputGradients(double targetVal){
    double delta = targetVal - this->m_outputVal;
    this->m_gradient = delta * Neuron::transferFunctionDerivative(this->m_outputVal);
}

void Neuron::calcHiddenGradients(const std::vector<Neuron> &nextLayer){
    double sum = sumDOW(nextLayer);
    this->m_gradient = sum * Neuron::transferFunctionDerivative(this->m_outputVal);
}

double Neuron::sumDOW(const std::vector<Neuron> &nextLayer) const{
    double sum = 0.0;

    //Sum our contributions of the errors at the nodes we feed
    for(unsigned n = 0; n < nextLayer.size() - 1; ++n){
        sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
    }

    return sum;
}

void Neuron::updateInputWeights(std::vector<Neuron> &prevLayer){

    //The weights that needs to be updated are in connection container
    //in the neuron in the preceding layer

    for(unsigned n = 0; n < prevLayer.size(); ++n){
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_outputWeights[this->n_index].deltaWeights;

        double newDeltaWeight = 
            eta
            * neuron.getOutputVal()
            * m_gradient
            + alpha
            * oldDeltaWeight;

        neuron.m_outputWeights[this->n_index].deltaWeights = newDeltaWeight;
        neuron.m_outputWeights[this->n_index].weight += newDeltaWeight;
    }

}