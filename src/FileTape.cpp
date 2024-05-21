#include "FileTape.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <stdexcept>

FileTape::FileTape(const std::string& fileName) : fileName(fileName), position(0), readDelay(0), writeDelay(0), rewindDelay(0), moveDelay(0) 
{
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open())
        throw std::runtime_error("Failed to open input file: " + fileName);
    
    int value;
    tapeData.clear();
    while (inputFile >> value) 
        tapeData.push_back(value);

    inputFile.close();
}

FileTape::~FileTape() {
    std::ofstream outputFile(fileName, std::ofstream::trunc);
    if (!outputFile.is_open())
        throw std::runtime_error("Failed to open output file: " + fileName);

    for (const int& value : tapeData) 
        outputFile << value << "\n";
    
    outputFile.close();
}

void FileTape::write(int value) 
{
    if (position < tapeData.size())
        tapeData[position] = value;
    else if (position == tapeData.size())
        tapeData.push_back(value);
    else
        throw std::out_of_range("Write position out of range");
    
    std::this_thread::sleep_for(std::chrono::milliseconds(writeDelay));
}

int FileTape::read() {
    std::this_thread::sleep_for(std::chrono::milliseconds(readDelay));
    if (position < tapeData.size())
        return tapeData[position];
    else
        throw std::out_of_range("Read position out of range");
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
    else
        throw std::out_of_range("Forward position out of range");

    std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay));
}

void FileTape::backward() 
{
    if (position > 0)
        --position;
    else
        throw std::out_of_range("Backward position out of range");

    std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay));
}

void FileTape::configure(const std::string& configPath) 
{
    std::ifstream configFile(configPath);
    if (!configFile.is_open())
        throw std::runtime_error("Failed to open config file: " + configPath);
    if (!(configFile >> readDelay >> writeDelay >> rewindDelay >> moveDelay))
        throw std::runtime_error("Invalid config file format: " + configPath);

    configFile.close();
}