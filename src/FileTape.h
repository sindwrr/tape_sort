#ifndef FILETAPE_H
#define FILETAPE_H

#include "TapeInterface.h"

#include <fstream>
#include <vector>
#include <chrono>
#include <thread>

class FileTape : public TapeInterface 
{
private:
    std::fstream file;
    std::string fileName;
    std::vector<int> tapeData;
    size_t position;
    int readDelay;
    int writeDelay;
    int rewindDelay;
    int moveDelay;

    void loadTape();
    void saveTape();

public:
    FileTape(const std::string& fileName);
    ~FileTape();

    void write(int value) override;
    int read() override;
    void rewind() override;
    void forward() override;
    void backward() override;
    void configure(const std::string& configPath) override;
};

#endif // FILETAPE_H
