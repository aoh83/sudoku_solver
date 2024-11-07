#pragma once

#include "myint.h"

#include <array>
#include <bitset>
#include <iostream>
#include <optional>

#include <boost/iterator/iterator_facade.hpp>

using bs = std::bitset<9>;

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
    : public boost::iterator_facade<row_iterator, u8,
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
    auto sq_x = sq_ / 3;
    auto sq_y = sq_ % 3;

    auto it_x = it_ / 3;
    auto it_y = it_ % 3;

    auto x = sq_x * 3 + it_x;
    auto y = sq_y * 3 + it_y;

    return s_[x][y];
  }

  field_t &s_;
  const u8 sq_;
  u8 it_;
};

void print(const field_t &f);
std::optional<field_t> solve(field_t f);
void from_file(std::istream &input, field_t &output);
