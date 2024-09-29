#include "sudoku.h"

void sudoku::exclude_line(u16 line) {
    bs excludes = non();
    for (u16 i = 0; i < 9; i++) {
        if (field[line][i].only_one()) {
            excludes.clear(field[line][i].first().value());
        }
    }
    for (u16 i = 0; i < 9; i++) {
        if (!field[line][i].only_one()) {
            field[line][i].intersect(excludes);
        }
    }
}

void sudoku::exclude_row(u16 row) {
    bs excludes = non();
    for (u16 i = 0; i < 9; i++) {
        if (field[i][row].only_one()) {
            excludes.clear(field[i][row].first().value());
        }
    }
    for (u16 i = 0; i < 9; i++) {
        if (!field[i][row].only_one()) {
            field[i][row].intersect(excludes);
        }
    }
}

void sudoku::exclude_square(int sqrow, int sqcol) {
    auto excludes = non();
    for (u16 x = 0; x < 3; x++) {
        for (u16 y = 0; y < 3; y++) {
            if (field[3 * sqrow + x][3 * sqcol + y].only_one()) {
                auto value = field[3 * sqrow + x][3 * sqcol + y].first().value();
                excludes.clear(value);
            }
        }
    }

    for (u16 x = 0; x < 3; x++) {
        for (u16 y = 0; y < 3; y++) {
            if (!field[3 * sqrow + x][3 * sqcol + y].only_one()) {
                field[3 * sqrow + x][3 * sqcol + y].intersect(excludes);
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

// how to pass a 2d array:  https://stackoverflow.com/a/17569578/887836
void from_file(std::istream &input, bs (&output)[9][9]) {
    char buf[16];
    for (auto i = 0; i < 9; i++) {
        input.getline(buf, sizeof(buf));
        for (auto j = 0; j < 9; j++) {
            if (buf[j] == ' ') {
                output[i][j] = non();
                continue;
            }
            output[i][j] = of(buf[j] - '0');
        }
    }
}