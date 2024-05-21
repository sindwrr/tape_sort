#include "TapeSort.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <iostream>

void TapeSort::sort(TapeInterface& inputTape, TapeInterface& outputTape, size_t memoryLimit) {
    std::vector<int> buffer;
    size_t bufferSize = memoryLimit / sizeof(int);
    bool done = false;
    std::vector<std::string> tempFiles;

    // Phase 1: Read chunks of input tape, sort in-memory, and write to temporary files
    while (!done) {
        buffer.clear();
        for (size_t i = 0; i < bufferSize; ++i) {
            try {
                int value = inputTape.read();
                if (value != -1) {
                    buffer.push_back(value);
                    inputTape.forward();
                } else {
                    done = true;
                    break;
                }
            } catch (const std::out_of_range& e) {
                done = true;
                break;
            }
        }

        if (!buffer.empty()) {
            std::sort(buffer.begin(), buffer.end());
            std::string tempFileName = "tmp/temp_" + std::to_string(tempFiles.size()) + ".tape";
            std::ofstream tempFile(tempFileName);
            for (const int& num : buffer)
                tempFile << num << "\n";
            tempFile.close();
            tempFiles.push_back(tempFileName);
        }
    }

    // Rewind input and output tapes
    inputTape.rewind();
    outputTape.rewind();

    // Phase 2: Merge sorted temporary files
    // Assuming we have enough memory to merge sorted files one by one
    for (const std::string& tempFileName : tempFiles) {
        std::ifstream tempFile(tempFileName);
        int value;
        while (tempFile >> value) {
            try {
                outputTape.write(value);
                outputTape.forward();
            } catch (const std::out_of_range& e) {
                std::cerr << "Write position out of range: " << e.what() << std::endl;
                tempFile.close();
                throw;
            }
        }
        tempFile.close();
        std::remove(tempFileName.c_str());
    }
}
