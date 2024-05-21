#include "FileTape.h"

#include <iostream>

// конструктор
FileTape::FileTape(const std::string& filename)
    : filename(filename), position(0), read_delay(0), 
      write_delay(0), rewind_delay(0), move_delay(0) 
{
    loadTape();
}

// деструктор
FileTape::~FileTape() 
{
    saveTape();
}

// ввод данных из файла в вектор данных
void FileTape::loadTape() 
{
    // открываем файловый поток ввода
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
        throw std::runtime_error("Ошибка открытия входного файла");

    // заносим поочередно данные в вектор
    int value;
    tape_data.clear();
    while (inputFile >> value)
        tape_data.push_back(value);

    inputFile.close();
}

// ввод данных в файл из вектора данных
void FileTape::saveTape()
{    
    // открываем файловый поток вывода
    std::ofstream outputFile(filename, std::ios::out);
    if (!outputFile.is_open())
        throw std::runtime_error("Ошибка открытия выходного файла");
    
    // заносим поочередно данные в файл
    for (const int& value : tape_data)
        outputFile << value << "\n";
    outputFile.close();
}

// запись в ячейку ленты
void FileTape::write(int value) 
{
    // задержка по записи из конф. файла 
    std::this_thread::sleep_for(std::chrono::milliseconds(write_delay));

    // в зависимости от размера вектора либо меняем, либо вставляем элемент
    if (position < tape_data.size())
        tape_data[position] = value;
    else if (position == tape_data.size())
        tape_data.push_back(value);
    else
        throw std::out_of_range("Позиция за пределами вектора");
}

// чтение из ячейки ленты
int FileTape::read() 
{
    // задержка по чтению из конф. файла 
    std::this_thread::sleep_for(std::chrono::milliseconds(read_delay));

    // возвращаем элемент на текущей позиции 
    if (position < tape_data.size()) 
        return tape_data[position];
    else
        throw std::out_of_range("Позиция за пределами вектора");
}

// перемотка ленты
void FileTape::rewind() 
{
    // задержка по перемотке из конф. файла 
    std::this_thread::sleep_for(std::chrono::milliseconds(rewind_delay));   

    // обнуляем позицию
    position = 0;
}

// сдвиг вперед на 1 позицию
void FileTape::forward() 
{
    // задержка по сдвигу ленты из конф. файла 
    std::this_thread::sleep_for(std::chrono::milliseconds(move_delay));

    // инкрементируем текущую позицию
    if (position < tape_data.size())
        ++position;
    else
        throw std::out_of_range("Позиция за пределами вектора");
}

// сдвиг назад на 1 позицию
void FileTape::backward() 
{
    // задержка по сдвигу ленты из конф. файла 
    std::this_thread::sleep_for(std::chrono::milliseconds(move_delay));

    // декрементируем текущую позицию
    if (position > 0)
        --position;
    else
        throw std::out_of_range("Позиция за пределами вектора");
}

// чтение конфигурационных данных
void FileTape::configure(const std::string& configPath) 
{
    // открываем файловый поток ввода
    std::ifstream configFile(configPath);
    if (!configFile.is_open())
        throw std::runtime_error("Ошибка открытия конф. файла");

    // читаем параметры из файла
    if (!(configFile >> read_delay 
                     >> write_delay 
                     >> rewind_delay 
                     >> move_delay))
        throw std::runtime_error("Ошибка формата конф. файла");

    configFile.close();
}