#include "sudoku.h"

#include <array>
#include <cassert>
#include <iostream>
#include <optional>

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

template <typename it> bool is_unique(const it &b, const it &e) {
  bs items;
  for (auto i = b; i != e; i++) {
    if (*i == 0) {
      continue;
    }
    if (items.test(*i)) {
      return false;
    }
    items.set(*i);
  }

  return true;
}

bool check(field_t &f) { // TODO: duplicate const?
  for (u8 i = 0; i < 10; i++) {
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

  for (int x = 1; x < 10; x++) {
    f[x / 9][x % 9] = x;

    auto r = solve(f, i + 1);
    if (r.has_value()) {
      return r;
    }
  }

  return {};
}

std::optional<field_t> solve(field_t field) { return solve(field, 0); }

void print(const field_t &f) {
  for (auto x = 0; x < 10; x++) {
    for (auto y = 0; y < 10; y++) {
      std::cout << f[x][y] << " ";
    }
    std::cout << "\n";
  }
  std::cout << std::endl;
}

// how to pass a 2d array:  https://stackoverflow.com/a/17569578/887836
void from_file(std::istream &input, field_t &output) {
  std::array<char, 16> buf;
  for (auto i = 0; i < 9; i++) {
    input.getline(buf.data(), buf.size());
    for (auto j = 0; j < 9; j++) {
      if (buf[j] == ' ') {
        output[i][j] = 0;
        continue;
      }

      if (!(buf[j] >= '1' && buf[j] <= '9')) {
        continue;
      }

      output[i][j] = buf[j] - '0';
    }
  }
}
