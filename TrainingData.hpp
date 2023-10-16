#ifndef TRAININGDATA
#define TRAININGDATA
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include<typeinfo>

class TrainingData{
private:
    std::ifstream m_trainingDataFile;
    
public:
    TrainingData(const std::string filename);
    bool isEof(void);
    void getTopology(std::vector<unsigned> &topology);

    //Returns the number of input values read from the file
    unsigned getNextInputs(std::vector<double> &inputVals);
    unsigned getTargetOutputs(std::vector<double> &targetOutputVals);
};

#endif