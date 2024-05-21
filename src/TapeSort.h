#ifndef TAPE_SORT_H
#define TAPE_SORT_H

#include "TapeInterface.h"

// класс для алгоритма сортировки
class TapeSort 
{
public:
    void sort(TapeInterface&, TapeInterface&, size_t);
};

#endif // TAPE_SORT_H