#include "TapeSort.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

// сортировка данных из входной ленты в выходную
void TapeSort::sort(TapeInterface& input_tape, 
                    TapeInterface& output_tape, 
                    size_t mem_limit) 
{
    std::vector<int> buffer; // буфер, ограниченный лимитом по памяти
    size_t buff_size = mem_limit / sizeof(int);

    bool done = false;
    std::vector<std::string> temp_files; // вектор временных файлов

    // создаем временную директорию, если ее нет
    const std::string tmp_dir = "tmp";
    if (!std::filesystem::exists(tmp_dir))
        std::filesystem::create_directory(tmp_dir);

    // заносим в файлы элементы, пока не дойдем до последнего
    while (!done) 
    {
        // заносим первые N элементов в буфер
        buffer.clear();
        for (size_t i = 0; i < buff_size; ++i) 
        {
            try 
            {
                int value = input_tape.read();
                buffer.push_back(value);
                input_tape.forward();
            } 
            catch (const std::out_of_range& e) 
            {
                done = true;
                break;
            }
        }

        if (!buffer.empty()) 
        {
            // сортируем буфер
            std::sort(buffer.begin(), buffer.end());

            // создаем временный файл
            std::string temp_filename = tmp_dir + "/temp_" 
                                        + std::to_string(temp_files.size()) 
                                        + ".tape";
            std::ofstream temp_file(temp_filename);
            
            // заносим буфер в временный файл
            for (const int& num : buffer)
                temp_file << num << "\n";

            temp_file.close();
            temp_files.push_back(temp_filename);
        }
    }

    // обнуляем позиции обеих лент
    input_tape.rewind();
    output_tape.rewind();

    for (const std::string& temp_filename : temp_files) 
    {
        // читаем временной файл
        std::ifstream temp_file(temp_filename);
        int value;
        while (temp_file >> value) 
        {
            try 
            {
                // заносим элемент в выходную ленту
                output_tape.write(value);
                output_tape.forward();
            } 
            catch (const std::out_of_range& e) 
            {
                temp_file.close();
                throw;
            }
        }

        temp_file.close();
    }

    // удаляем директорию с временными файлами
    std::filesystem::remove_all(tmp_dir);
}
