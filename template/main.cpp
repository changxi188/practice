#include <iostream>
#include "array.h"

int main(void)
{
    array<int, 50> intArray;
    intArray.set_value(0, 2);
    int  firstElem = intArray.get_value(0);
    int* begin     = intArray;

    std::cout << firstElem << std::endl;
}

