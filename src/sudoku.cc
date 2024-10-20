#include "sudoku.h"

#include <vector>
#include <array>
#include <stack>
#include <cassert>

std::optional<u16> first(const bs &b) {
    for (u16 i = 1, e = b.size(); i < e; i++) {
        if (b.test(i)) {
            return std::optional<u16>(i);
        }
    }
    return {};
}

void sudoku::exclude_line(u16 line) {
    bs excludes;
    for (u16 i = 0; i < 9; i++) {
        if (field[line][i].count() == 1) {
            excludes.reset(first(field[line][i]).value());
        }
    }
    for (u16 i = 0; i < 9; i++) {
        if (field[line][i].count() != 1) {
            field[line][i] &= (excludes);
        }
    }
}

void sudoku::exclude_row(u16 row) {
    bs excludes;
    for (u16 i = 0; i < 9; i++) {
        if (field[i][row].count() == 1) {
            excludes.reset(first(field[i][row]).value());
        }
    }
    for (u16 i = 0; i < 9; i++) {
        if (field[i][row].count() != 1) {
            field[i][row] &= (excludes);
        }
    }
}

void sudoku::exclude_square(int sqrow, int sqcol) {
    bs excludes;
    for (u16 x = 0; x < 3; x++) {
        for (u16 y = 0; y < 3; y++) {
            if (field[3 * sqrow + x][3 * sqcol + y].count() == 1) {
                auto value = first(field[3 * sqrow + x][3 * sqcol + y]).value();
                excludes.reset(value);
            }
        }
    }

    for (u16 x = 0; x < 3; x++) {
        for (u16 y = 0; y < 3; y++) {
            if (field[3 * sqrow + x][3 * sqcol + y].count() != 1) {
                field[3 * sqrow + x][3 * sqcol + y] &= excludes;
            }
        }
    }
}

void sudoku::exclude_square(int nr) {
    const auto offsets = std::vector<std::tuple<u16, u16>> { 
        {0,0}, {0,1}, {0,2}, 
        {1,0}, {1,1}, {1,2},
        {2,0}, {2,1}, {2,2}
    };
    exclude_square(std::get<0>(offsets[nr]), std::get<1>(offsets[nr]));
}

// TODO: how to detect fix point? 
// keep running until fix point
void sudoku::run_exclusions() {
    for (int i = 0; i < 9; i++) {
        exclude_line(i);
        exclude_row(i);
        exclude_square(i);
    }
}

int sudoku::solve() {
    std::stack<sudoku> s; 
    s.push(field);
    return 0;
}

void sudoku::print() {
}

// how to pass a 2d array:  https://stackoverflow.com/a/17569578/887836
void from_file(std::istream &input, bs (&output)[9][9]) {
    std::array<char, 16> buf;
    for (auto i = 0; i < 9; i++) {
        input.getline(buf.data(), buf.size());
        for (auto j = 0; j < 9; j++) {
            if (buf[j] == ' ') {
                output[i][j] |= 0x01ff; // set [0 .. 8
                continue;
            }
            
            if (!(buf[j] >= '1' && buf[j] <= '9')) {
                continue;
            }

            output[i][j].set(buf[j] - '0' - 1);
        }
    }
}
