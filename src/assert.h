#include "FileTape.h"
#include "TapeSort.h"

#include <cassert>

// юнит-тесты
void tests()
{
    FileTape test_input_tape("src/test/test_input.txt");
    FileTape test_output_tape("src/test/test_output.txt");

    test_input_tape.configure("src/test/test_config.txt");
    test_output_tape.configure("src/test/test_config.txt");   

    assert(test_input_tape.read() == 5);
    test_input_tape.forward();
    assert(test_input_tape.read() == 4);
    test_input_tape.forward();
    assert(test_input_tape.read() == 3);
    test_input_tape.forward();
    assert(test_input_tape.read() == 2);
    test_input_tape.forward();
    assert(test_input_tape.read() == 1);
    test_input_tape.backward();
    assert(test_input_tape.read() == 2);
    test_input_tape.backward();
    assert(test_input_tape.read() == 3);
    test_input_tape.write(0);
    assert(test_input_tape.read() == 0);
    test_input_tape.write(3);
    test_input_tape.rewind(); 

    TapeSort test_sorter;
    test_sorter.sort(test_input_tape, test_output_tape, 1024);

    test_output_tape.rewind();
    assert(test_output_tape.read() == 1);
    test_output_tape.forward();
    assert(test_output_tape.read() == 2);
    test_output_tape.forward();
    assert(test_output_tape.read() == 3);
    test_output_tape.forward();
    assert(test_output_tape.read() == 4);
    test_output_tape.forward();
    assert(test_output_tape.read() == 5);
}