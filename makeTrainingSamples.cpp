#include <iostream>
#include <cmath>
#include <cstdlib>

int main(){

    // Random training sets for XOR - two inputs and one output
    std::cout << "topology: 2 4 1" << std::endl;
    for(int i = 2000; i >= 0; --i){
        int n1 = static_cast<int>(2.0 * rand() / static_cast<double>(RAND_MAX));
        int n2 = static_cast<int>(2.0 * rand() / static_cast<double>(RAND_MAX));
        int t = n1 ^ n2;
        std::cout << "in: " << n1 << ".0 " << n2 << ".0 " << std::endl;
        std::cout << "out: " << t << ".0" << std::endl;

    }

    return 0;
}