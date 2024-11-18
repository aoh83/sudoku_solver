#include "sudoku.h"

#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <spdlog/spdlog.h>

std::optional<u16> first(const bs &b) {
  for (u16 i = 1, e = b.size(); i < e; i++) {
    if (b.test(i)) {
      return std::optional<u16>(i);
    }
  }
  return {};
}

template <typename iterator> bs to_bs(iterator begin, iterator end) {
  bs ret = 0xff << 1;
  for (auto i = begin; i != end; i++) {
    ret.reset(i);
  }
  return ret;
}

bool check(field_t &f) { // TODO: duplicate const?
  for (u8 i = 0; i < 9; i++) {
    if (!is_unique(row_iterator(f, i, 0), row_iterator(f, i, 9))) {
      return false;
    }
    if (!is_unique(col_iterator(f, i, 0), col_iterator(f, i, 9))) {
      return false;
    }
    if (!is_unique(sq_iterator(f, i, 0), sq_iterator(f, i, 9))) {
      return false;
    }
  }
  return true;
}

static std::optional<field_t> solve(field_t f, u8 i) {
  if (i >= 81) {
    if (check(f)) {
      return f;
    }
    return {};
  }

  if (f[i / 9][i % 9] != 0) {
    return solve(f, i + 1);
  }

  for (int x = 1; x < 10; x++) {
    f[i / 9][i % 9] = x;

    auto r = solve(f, i + 1);
    if (r.has_value()) {
      return r;
    }
  }

  return {};
}

std::optional<field_t> solve(field_t field) { return solve(field, 0); }

void print(const field_t &f) {
  for (auto x = 0; x < 9; x++) {
    for (auto y = 0; y < 9; y++) {
      std::cout << f[x][y] << " ";
    }
    std::cout << "\n";
  }
  std::cout << std::endl;
}

// how to pass a 2d array:  https://stackoverflow.com/a/17569578/887836
void from_file(std::istream &input, field_t &output) {
  std::array<u8, 16> buf;
  for (auto i = 0; i < 9; i++) {
    input.getline((char *)buf.data(), buf.size());
    for (auto j = 0; j < 9; j++) {
      if (buf[j] == ' ') {
        output[i][j] = 0;
        continue;
      }

      if ((buf[j] < '1' || buf[j] > '9')) {
        output[i][j] = 0;
        std::cout << "not a number:" << buf[j] << "on (" << i << ", " << j
                  << ")" << std::endl;
        continue;
      }

      output[i][j] = buf[j] - '0';
    }
  }
}

field_t from_file(std::istream &input) {
  field_t output;
  std::array<u8, 16> buf;
  for (auto i = 0; i < 9; i++) {
    input.getline((char *)buf.data(), buf.size());
    for (auto j = 0; j < 9; j++) {
      if (buf[j] == ' ') {
        output[i][j] = 0;
        continue;
      }

      if ((buf[j] < '1' || buf[j] > '9')) {
        output[i][j] = 0;
        std::cout << "not a number:" << buf[j] << "on (" << i << ", " << j
                  << ")" << std::endl;
        continue;
      }

      output[i][j] = buf[j] - '0';
    }
  }
  return output;
}
