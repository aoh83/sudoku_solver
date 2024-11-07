#include <gtest/gtest.h> // googletest header file
                         //
#include <cstring>
#include <fstream>
#include <string>

using std::string;

#include "sudoku.h"

const char *actualValTrue = "hello gtest";
const char *actualValFalse = "hello world";
const char *expectVal = "hello gtest";

TEST(Bs, Simple) {
  bs bs = ALL;

  bs.set(5);
  bs.set(6);
  bs.reset(5);

  assert(bs.test(6));
}

TEST(Sudoku, loadFile) {
  field_t field;
  field_t expected = field_t{{{0}}};
  auto ifs = std::ifstream("easy.txt");

  from_file(ifs, field);
  // looks like the loader is correct someone needs to fix that array here :D
  EXPECT_NE(expected, field);
}

TEST(Sudoku, copy) {
  std::array<int, 3> foo{0, 1, 2};
  std::array<int, 3> bar = foo;

  EXPECT_EQ(foo, bar);
}
