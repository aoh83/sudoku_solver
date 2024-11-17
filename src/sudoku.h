#pragma once

#include "myint.h"

#include <array>
#include <bitset>
#include <iostream>
#include <optional>

#include <boost/iterator/iterator_facade.hpp>

using bs = std::bitset<10>;

static const bs ALL = 9;

using field_t = std::array<std::array<u8, 9>, 9>;

class row_iterator
    : public boost::iterator_facade<row_iterator, u8,
                                    boost::random_access_traversal_tag> {
public:
  row_iterator(field_t &s, u8 row, u8 col = 0) : s_(s), row_(row), col_(col) {}

private:
  friend class boost::iterator_core_access;

  void increment() { col_++; }

  bool equal(const row_iterator &other) const {
    return &(this->s_) == &(other.s_) && this->row_ == other.row_ &&
           this->col_ == other.col_;
  }

  u8 &dereference() const { return s_[row_][col_]; }

  field_t &s_;
  const u8 row_;
  u8 col_;
};

class col_iterator
    : public boost::iterator_facade<col_iterator, u8,
                                    boost::random_access_traversal_tag> {
public:
  col_iterator(field_t &s, u8 col, u8 row = 0) : s_(s), row_(row), col_(col) {}

private:
  friend class boost::iterator_core_access;

  void increment() { row_++; }

  bool equal(const col_iterator &other) const {
    return &(this->s_) == &(other.s_) && this->row_ == other.row_ &&
           this->col_ == other.col_;
  }

  u8 &dereference() const { return s_[row_][col_]; }

  field_t &s_;
  u8 row_;
  const u8 col_;
};

class sq_iterator
    : public boost::iterator_facade<sq_iterator, u8,
                                    boost::random_access_traversal_tag> {
public:
  sq_iterator(field_t &s, u8 sq, u8 start = 0) : s_(s), sq_(sq), it_(start) {}

private:
  friend class boost::iterator_core_access;

  void increment() { it_++; }

  bool equal(const sq_iterator &other) const {
    return &(this->s_) == &(other.s_) && this->sq_ == other.sq_ &&
           this->it_ == other.it_;
  }

  u8 &dereference() const {
    auto sq_row = sq_ / 3;
    auto sq_col = sq_ % 3;

    auto it_row = it_ / 3;
    auto it_col = it_ % 3;

    auto row = sq_row * 3 + it_row;
    auto col = sq_col * 3 + it_col;

    return s_[row][col];
  }

  field_t &s_;
  const u8 sq_;
  u8 it_;
};

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

void print(const field_t &f);
std::optional<field_t> solve(field_t f);
bool check(field_t &f);
void from_file(std::istream &input, field_t &output);
field_t from_file(std::istream &input);
