#ifndef TAPE_INTERFACE_H
#define TAPE_INTERFACE_H

#include <string>

// интерфейс для работы с лентой
class TapeInterface 
{
public:
    virtual ~TapeInterface() = default;

    virtual void write(int) = 0;
    virtual int read() = 0;
    virtual void rewind() = 0;
    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void configure(const std::string&) = 0;
};

#endif // TAPE_INTERFACE_H