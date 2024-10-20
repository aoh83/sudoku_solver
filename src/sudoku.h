#pragma once

#include "myint.h"

#include <iostream>
#include <optional>
#include <bitset>

#include <boost/iterator/iterator_facade.hpp>

using bs = std::bitset<9>; 

static const bs ALL = 9;

class sudoku {
    bs field[9][9];
    
public:
    sudoku(const bs (&input)[9][9]) { std::copy(&input[0][0], &input[0][0]+9*9, &field[0][0]); }

    sudoku(const sudoku &) = default;
    sudoku(sudoku &&) = default;
    sudoku &operator=(const sudoku &) = default;
    sudoku &operator=(sudoku &&) = default;
    sudoku() = default;

    void exclude_line(u16 line);
    void exclude_row(u16 row);
    void exclude_square(int sqrow, int sqcol);
    void exclude_square(int nr);

    void run_exclusions();

public:
    int solve();
    void print();
    
friend class row_iterator;
};

class row_iterator : public boost::iterator_facade<row_iterator, bs, boost::random_access_traversal_tag> {
public:
    row_iterator(sudoku &s, u8 row) : s_(s), row_(row), col_(0) {}

private:
    friend class boost::iterator_core_access;

    void increment() { col_++; }

    bool equal(row_iterator & other) const
    {
        return &(this->s_) == &(other.s_) && this->row_ == other.row_ && this->col_ == other.col_;
    }

    bs& dereference() const { return s_.field[row_][col_]; }

    sudoku &s_;
    const u8 row_;
    u8 col_;
};

struct row_range {
    sudoku &s_;
    const u8 row_;

    row_range(sudoku &s, u8 row) : s_(s), row_(row) {}
    
    row_iterator begin() {}
    row_iterator end() {}
};

void from_file(std::istream &input, bs (&output)[9][9]);
