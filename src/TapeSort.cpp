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

    // вектора для слияния временных лент в одну сортированную
    std::vector<std::ifstream> temp_streams(temp_files.size());
    std::vector<int> current_values(temp_files.size(), INT_MAX);
    std::vector<bool> has_next(temp_files.size(), true);

    // открываем все временные файлы и считываем первые значения
    for (size_t i = 0; i < temp_files.size(); ++i)
    {
        temp_streams[i].open(temp_files[i]);
        if (!(temp_streams[i] >> current_values[i]))
            has_next[i] = false;
    }

    while (true) 
    {
        int min_value = INT_MAX;
        size_t min_index = 0;
        bool found = false;

        // ищем минимальный элемент среди прочитанных
        for (size_t i = 0; i < current_values.size(); ++i)
            if (has_next[i] && current_values[i] < min_value) 
            {
                min_value = current_values[i];
                min_index = i;
                found = true;
            }

        // если не нашли (если дошли до конца всех файлов), выходим из цикла
        if (!found)
            break;

        // записываем этот элемент на выходную ленту
        try 
        {
            output_tape.write(min_value);
            output_tape.forward();
        } 
        catch (const std::out_of_range& e) 
        {
            throw e;
        }

        // читаем следующий элемент из соотв. файла
        if (!(temp_streams[min_index] >> current_values[min_index]))
            has_next[min_index] = false;
    }

    // закрываем временные файловые потоки
    for (auto& stream : temp_streams)
        if (stream.is_open())
            stream.close();

    // удаляем директорию с временными файлами
    std::filesystem::remove_all(tmp_dir);
}