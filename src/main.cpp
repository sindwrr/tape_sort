#include "FileTape.h"
#include "TapeSort.h"

#include <iostream>

int main(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        std::cerr << "Wrong input format" << std::endl;
        return 1;
    }
    
    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];
    std::string configFileName = argv[3];

    try 
    {
        
        FileTape inputTape(inputFileName);
        
        inputTape.configure(configFileName);

        FileTape outputTape(outputFileName);
        size_t memoryLimit = 1024 * 1024;
        TapeSort sorter;
        
        sorter.sort(inputTape, outputTape, memoryLimit);
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
