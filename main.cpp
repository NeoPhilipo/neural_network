#include <iostream>
#include <vector>
#include "NeuralNetwork.hpp"
#include "TrainingData.hpp"
//#include "main_proba.hpp"

void showVectorVals(std::string label, std::vector<double> &vals);

int main(int argc, char* argv[]){

    
    TrainingData trainData("trainingData.txt");
    std::vector<unsigned> topology;
    
    
    trainData.getTopology(topology);
    
    
    NeuralNetwork net(topology);

    std::vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;
    
    while(!trainData.isEof()){
        ++trainingPass;
       
        std::cout << std::endl << "Pass " << trainingPass;
        //std::cout << std::endl << "Is eof? - " << trainData.isEof() << std::endl;
        //std::cout << std::endl << "OVDE" << std::endl;
        //Get new input data and feed it forward
        if(trainData.getNextInputs(inputVals) != topology[0]){
            break;
        }
       
        showVectorVals("Inputs:", inputVals);
        net.feedForward(inputVals);

        //Collect the network's actual results
        net.getResults(resultVals);
        showVectorVals("Outputs: ", resultVals);

        //Train the network what the outputs should have been
        trainData.getTargetOutputs(targetVals);
        showVectorVals("Targets: ", targetVals);
        assert(targetVals.size() == topology.back());

        net.backProp(targetVals);

        //Report how well the training is working
        std::cout << "Network's recent average error: " << net.getRecentAverageError() << std::endl;
    }

    std::cout << std::endl << "Done" << std::endl;
    
    inputVals.clear();
    inputVals.push_back(1);
    inputVals.push_back(1);

    std::cout << "Test -----------------" << std::endl;

    net.feedForward(inputVals);
    showVectorVals("Inputs: ", inputVals);
    net.getResults(resultVals);
    showVectorVals("Outputs: ", resultVals);

    return 0;
}

void showVectorVals(std::string label, std::vector<double> &vals){
    std::cout << label << " ";
    for(unsigned i = 0; i < vals.size(); i++){
        std::cout << vals[i] << " ";
    }
    std::cout << std::endl;
}