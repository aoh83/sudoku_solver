#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "sudoku.h"

using namespace std;

int main(int argc, char **argv) {

  auto console = spdlog::stdout_color_mt("console");
  spdlog::set_default_logger(console);

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
