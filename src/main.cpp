#include "FileTape.h"
#include "TapeSort.h"
#include "assert.h"

#include <iostream>

#define MEM_LIMIT 1024

int main(int argc, char* argv[]) 
{
    tests(); // юнит-тесты

    if (argc != 4) 
    {
        std::cerr << "Ошибка: Неверное кол-во аргументов" << std::endl;
        return 1;
    }
    
    // считываем имена файлов из аргументов
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string config_file = argv[3];

    try 
    {
        // инициализация и конфигурация лент
        FileTape input_tape(input_file);
        input_tape.configure(config_file);

        FileTape output_tape(output_file);
        output_tape.configure(config_file);

        // непосредственно сортировка
        size_t mem_limit = MEM_LIMIT;
        TapeSort sorter;

        std::cout << "Сортировка началась. Пожалуйста, подождите...\n";
        sorter.sort(input_tape, output_tape, mem_limit);
        std::cout << "Сортировка завершена! См. выходной файл.\n";     
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Исключение: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}