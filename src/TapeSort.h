#ifndef TAPESORT_H
#define TAPESORT_H

#include "TapeInterface.h"

#include <string>

class TapeSort 
{
public:
    void sort(TapeInterface& inputTape, TapeInterface& outputTape, size_t memoryLimit);
};

#endif // TAPESORT_H