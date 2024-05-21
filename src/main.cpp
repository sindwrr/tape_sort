#include "FileTape.h"
#include "TapeSort.h"

#include <iostream>

int main(int argc, char* argv[]) 
{
    // if (argc != 4) 
    // {
    //     std::cerr << "Wrong input format" << std::endl;
    //     return 1;
    // }

    std::string inputFileName = "input.txt";
    std::string outputFileName = "output.txt";
    std::string configFileName = "config.txt";

   try {
        FileTape inputTape(inputFileName);
        inputTape.configure(configFileName);

        FileTape outputTape(outputFileName);

        size_t memoryLimit = 1024 * 1024;
        TapeSort sorter;
        sorter.sort(inputTape, outputTape, memoryLimit);

        std::cout << "Sorting completed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
