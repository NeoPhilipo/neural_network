#include "NeuralNetwork.hpp"

double NeuralNetwork::m_recentAverageSmoothingFactor = 0.01;

NeuralNetwork::NeuralNetwork(const std::vector<unsigned> &topology){
    for(unsigned layerNum = 0; layerNum < topology.size(); layerNum++){
        this->m_layers.push_back(Layer());
        unsigned outputNum = (layerNum == topology.size()-1) ? 0 : topology[layerNum+1];
        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++){
            this->m_layers.back().push_back(Neuron(outputNum, neuronNum));
            //std::cout << "Neuron made" << std::endl;
        }
        //std::cout << "-----------" << std::endl;

        // Force the bias neuron's output value to 1.0. It's a last neuron created above
        this->m_layers.back().back().setOutputVal(1.0);
    }
}

void NeuralNetwork::feedForward(const std::vector<double> &inputVals){
    assert(inputVals.size() == m_layers[0].size() - 1);

    for(unsigned input = 0; input < inputVals.size(); input++){
        //Bice metoda setOutputVals() u Neuron klasi
        m_layers[0][input].setOutputVal(inputVals[input]);
    }

    for(unsigned numLayer = 1; numLayer < m_layers.size(); numLayer++){
        Layer &prevLayer = m_layers[numLayer - 1];
        for(unsigned n = 0; n < m_layers[numLayer].size() - 1; n++){
            //Bice metoda feedForward() u klasi Neuron
            m_layers[numLayer][n].feedForward(prevLayer);

        }
    }
}

void NeuralNetwork::backProp(const std::vector<double> &targetVals){
    //Calculate overall net error
    Layer &outputLayer = this->m_layers.back();
    m_error = 0.0;

    for(unsigned n = 0; n < outputLayer.size() - 1; n++){
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        m_error += delta * delta;
        
    }
    m_error /= outputLayer.size() - 1;
    m_error = sqrt(m_error);
    
    this->m_recentAverageError =
            (this->m_recentAverageError * this->m_recentAverageSmoothingFactor + this->m_error)
            / (this->m_recentAverageSmoothingFactor + 1.0);
    
    

    //Calculate output layer gradients
    for(unsigned n = 0; n < outputLayer.size() - 1; n++){
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    //Calculate gradients on hidden layer
    for(unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum){
        Layer &hiddenLayer = m_layers[layerNum];
        Layer &nextLayer = m_layers[layerNum + 1];

        for(unsigned n = 0; n < hiddenLayer.size(); n++){
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    //For all layer except input layer
    //update connection weights
    for(unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum){
        Layer &layer = m_layers[layerNum];
        Layer &prevLayer = m_layers[layerNum - 1];

        for(unsigned n = 0; n < layer.size() - 1; n++){
            layer[n].updateInputWeights(prevLayer);
        }
    }

}

void NeuralNetwork::getResults(std::vector<double> &resultVals) const {
    resultVals.clear();
    
    for(unsigned n = 0; n < this->m_layers.back().size() - 1; n++){
        resultVals.push_back(this->m_layers.back()[n].getOutputVal());
    }
}

double NeuralNetwork::getRecentAverageError(void) const{
     return this->m_recentAverageError;
}