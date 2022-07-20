#include "add1.h"

#include <gtest/gtest.h>
int Add::result = 1;

int Add::GetRes(int i)
{
    return result;
}
