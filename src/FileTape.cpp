#include "FileTape.h"

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

FileTape::FileTape(const std::string& fileName) : fileName(fileName), position(0) 
{
    std::ifstream inputFile(fileName);
    int value;
    while (inputFile >> value)
        tapeData.push_back(value);
    
    for (const int& i : tapeData)
        std::cout << i << " ";

    inputFile.close();
}

FileTape::~FileTape() 
{
    std::ofstream outputFile(fileName, std::ofstream::trunc);
    for (const int& value : tapeData)
        outputFile << value << "\n";

    outputFile.close();
}

void FileTape::write(int value) 
{
    if (position < tapeData.size())
        tapeData[position] = value;
    else
        tapeData.push_back(value);

    std::this_thread::sleep_for(std::chrono::milliseconds(writeDelay));
}

int FileTape::read() 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(readDelay));
    return tapeData[position];
}

void FileTape::rewind() 
{
    position = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(rewindDelay));
}

void FileTape::forward() 
{
    if (position < tapeData.size() - 1)
        ++position;

    std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay));
}

void FileTape::backward() 
{
    if (position > 0)
        --position;

    std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay));
}

void FileTape::configure(const std::string& configPath) 
{
    std::ifstream configFile(configPath);
    if (configFile.is_open()) 
    {
        configFile >> readDelay;
        configFile >> writeDelay;
        configFile >> rewindDelay;
        configFile >> moveDelay;
        configFile.close();
    }
}
