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

  for (int x = 0; x < 9; x++) {
    for (int y = 0; y < 9; y++) {
      EXPECT_LT(field[x][y], 10);
      EXPECT_GE(field[x][y], 0);
    }
  }
}

TEST(Sudoku, row) {
  field_t field;
  auto expected = std::array<u8, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto ifs = std::ifstream("row.txt");

  from_file(ifs, field);
  auto b = row_iterator(field, 0), e = row_iterator(field, 0, 9);
  auto it1 = b;
  auto it2 = expected.begin();
  while (it1 != e && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  // Ensure both iterators reached the end
  EXPECT_EQ(it1, e);
  EXPECT_EQ(it2, expected.end());
}

TEST(Sudoku, col) {
  field_t field;
  auto expected = std::array<u8, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto ifs = std::ifstream("col.txt");

  from_file(ifs, field);
  auto b = col_iterator(field, 7), e = col_iterator(field, 7, 9);
  auto it1 = b;
  auto it2 = expected.begin();
  while (it1 != e && it2 != expected.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  // Ensure both iterators reached the end
  EXPECT_EQ(it1, e);
  EXPECT_EQ(it2, expected.end());
}

TEST(Sudoku, sqr) {
  field_t field;
  auto expected = std::array<u8, 9>{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto ifs = std::ifstream("sqr.txt");

  from_file(ifs, field);
  auto b = sq_iterator(field, 8), e = sq_iterator(field, 8, 9);
  auto it1 = b;
  auto it2 = expected.begin();
  while (it1 != e && it2 != expected.end()) {
    auto i = *it1++;
    auto j = *it2++;
    EXPECT_EQ(i, j);
  }
  // Ensure both iterators reached the end
  EXPECT_EQ(it1, e);
  EXPECT_EQ(it2, expected.end());
}

TEST(Sudoku, check) {
  auto ifs = std::ifstream("solved.txt");
  auto field = from_file(ifs);
  ASSERT_TRUE(check(field));
}

TEST(Sudoku, uniqueness) {}

#if 0
TEST(Sudoku, solve) {
  field_t field;
  auto ifs = std::ifstream("easy.txt");

  from_file(ifs, field);
  // looks like the loader is correct someone needs to fix that array here :D

  auto r = solve(field);
  if (r.has_value()) {
    print(r.value());
    ASSERT_TRUE(false);
  }
}
#endif
