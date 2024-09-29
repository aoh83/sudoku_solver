#pragma once

#include "myint.h"

#include <iostream>
#include <optional>
#include <tuple>
#include <stack>
#include <vector>

static const u16 ALL = 0xfe | (1<<8) |(1<<9);

class bs {
    u16 values;
public: 
    bs(u16): values(0) {}
    bs(): values(0) {}

    bs &operator=(const bs &b) = default;
    bs &operator=(bs &&b) = default;
    bs(const bs &b) = default;
    bs(bs &&b) = default;
    ~bs() = default;

    u16 raw() { return values; }

    void print() {
        std::cout << values << std::endl;
        std::cout << "{";
        for (u16 i = 1; i < 10; i++) {
            if (values & (1 << i)) { std::cout <<  i ; } else { std::cout << " "; }
        }
        std::cout << "}\n";
    }

    bool isClear() { return values == 0; }
    bool isClear(u16 i) { return (values & (1 << i)) == 0; }

    void clear(u16 i) { values &= (~(1 << i) & ALL) ; }

    void set(u16 i) { values |= (1 << i); }
    bool isSet(u16 i) { return (values & (1 << i)); }
    
    void intersect(const bs& other) {
        values &= other.values;
    }

    bool only_one() {
        for (u16 i = 1; i < 10; i++) {
            if (values == (1 << i)) {
                return true;
            }
        }
        return false;
    }

    std::optional<u16> first() {
        for (u16 i = 1; i < 10; i++) {
            if (values & (1<<i)) {
                return std::optional<u16>(i);
            }
        }
        return {};
    }
};

static inline bs of(u16 i) { return bs(1<<i);}
static inline bs non() { return bs(ALL);}


class sudoku {
    bs field[9][9];
public:
    sudoku(const bs (&input)[9][9]) { std::copy(&input[0][0], &input[0][0]+9*9, &field[0][0]); }

    sudoku(const sudoku &) = default;
    sudoku(sudoku &&) = default;
    sudoku &operator=(const sudoku &) = default;
    sudoku &operator=(sudoku &&) = default;
    sudoku() = default;
private:
    void exclude_line(u16 line);

    void exclude_row(u16 row);
    void exclude_square(int sqrow, int sqcol);
    void exclude_square(int nr);
    void run_exclusions();

public:
    int solve();
};

void from_file(std::istream &input, bs (&output)[9][9]);
