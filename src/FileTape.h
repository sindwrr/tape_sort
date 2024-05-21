#ifndef FILE_TAPE_H
#define FILE_TAPE_H

#include "TapeInterface.h"

#include <fstream>
#include <vector>
#include <chrono>
#include <thread>

// класс (реализация интерфейса) для работы с лентой 
class FileTape : public TapeInterface 
{
private:
    std::string filename;
    std::vector<int> tape_data;
    size_t position;
    int read_delay;
    int write_delay;
    int rewind_delay;
    int move_delay;

    void loadTape();
    void saveTape();

public:
    FileTape(const std::string&);
    ~FileTape();

    void write(int) override;
    int read() override;
    void rewind() override;
    void forward() override;
    void backward() override;
    void configure(const std::string&) override;
};

#endif // FILE_TAPE_H
