#include <gtest/gtest.h> // googletest header file

#include <string>
using std::string;

#include "sudoku.h"

const char *actualValTrue  = "hello gtest";
const char *actualValFalse = "hello world";
const char *expectVal      = "hello gtest";

TEST(Bs, Simple) {
    bs bs = ALL;

    bs.set(5);
    bs.set(6);
    bs.print();
    bs.clear(5);
    bs.print();
    
    assert(bs.isSet(6));

}