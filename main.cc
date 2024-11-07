#include <iostream>

#include "sudoku.h"

using namespace std;

int main(int argc, char **argv) {
  field_t input;
  from_file(std::cin, input);

  auto ret = solve(input);

  if (ret.has_value()) {
    print(ret.value());
  } else {
    std::cout << "unsolvable\n";
  }

  return 0;
}
