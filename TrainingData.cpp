#include "TrainingData.hpp"


TrainingData::TrainingData(const std::string filename){
    m_trainingDataFile.open(filename.c_str());
    
}

bool TrainingData::isEof(){
    return this->m_trainingDataFile.eof();
}

unsigned TrainingData::getNextInputs(std::vector<double> &inputVals){
    inputVals.clear();
    std::string line;
    getline(m_trainingDataFile, line);
    
    std::stringstream ss(line);
    std::string label;
    ss >> label;
    std::string pom = label;
    
    if(label.compare(label) == 0){
        
        double oneValue;
        std::string pom1;
        // while(ss.tellg() != 23){
        //     ss >> pom1;
        //     std::cout << pom1 << "." << std::endl;
        // }
        std::cout << std::endl;
        while(ss.tellg() != 23){
            
            ss >> pom1;
            //std::cout << "INPUT: " << ss.tellg() << std::endl;

            
            oneValue = pom1[1] - '0';
            oneValue = static_cast<double>(oneValue);
            
            
            //std::cout << oneValue << std::endl;
            
            inputVals.push_back(oneValue);
        }
    }
    
    return inputVals.size();
}

unsigned TrainingData::getTargetOutputs(std::vector<double> &targetOutputVals){
    targetOutputVals.clear();
    std::string line;
    getline(m_trainingDataFile, line);
    std::stringstream ss(line);
    std::string label;

    ss >> label;
    
    if(label.compare(label) == 0){
        //std::cout << "PROSLO" << std::endl;
        double oneValue;
        std::string pom1;
        while(ss.tellg() != 17){
            
            ss >> pom1;
            //std::cout << "OUTPUT: " << ss.tellg() << std::endl;
            
            oneValue = pom1[1] - '0';
            oneValue = static_cast<double>(oneValue);

            // std::cout << pom1.size() * sizeof(char) << std::endl;
            //std::cout << oneValue << std::endl;
            //std::cout << ss.tellg() << std::endl;
            targetOutputVals.push_back(oneValue);
            if(ss.tellg() == -1)
                break;
        }
    }
    //std::cout << targetOutputVals.size() << std::endl;
    return targetOutputVals.size();
}

void TrainingData::getTopology(std::vector<unsigned> &topology){
    std::string line;
    std::string label;

    getline(this->m_trainingDataFile, line);
    getline(this->m_trainingDataFile, line);
    
    std::stringstream ss(line);
    
    ss >> label;

    if(this->isEof() || label.compare(label) != 0){
        std::cout << "it is end of file or first label is not 'topology:'. aborting!" << std::endl;
       
        abort();
    }

    // while(ss.tellg() != 31){
    //     ss >> label;
    //     std::cout << label << std::endl;
    //     std::cout << ss.tellg() << std::endl;
    // }
    

    while(ss.tellg() != 31){
        unsigned n;
        std::string pom;
        
        ss >> pom;

        n = pom[1]-'0';

        //std::cout << n << std::endl;
        topology.push_back(n);
    }

    
    return;
}