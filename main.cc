#include <cstdio>
#include <cstdint>
#include <cassert>
#include <array>
#include <tuple>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <optional>

using namespace std;

typedef uint16_t u16;

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

    optional<u16> first() {
        for (u16 i = 1; i < 10; i++) {
            if (values & (1<<i)) {
                return optional<u16>(i);
            }
        }
        return {};
    }
};

bs of(u16 i) { return bs(1<<i);}
bs non() { return bs(ALL);}

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
    void exclude_line(u16 line) {
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

    void exclude_row(u16 row) {
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
    
    void exclude_square(int sqrow, int sqcol) {
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
    
    void exclude_square(int nr) {
        const auto offsets = vector<tuple<u16, u16>> { 
            {0,0}, {0,1}, {0,2}, 
            {1,0}, {1,1}, {1,2},
            {2,0}, {2,1}, {2,2}
        };
        exclude_square(get<0>(offsets[nr]), get<1>(offsets[nr]));
    }
    
    // TODO: how to detect fix point? 
    // keep running until fix point
    void run_exclusions() {
        for (int i = 0; i < 9; i++) {
            exclude_line(i);
            exclude_row(i);
            exclude_square(i);
        }
    }

public:
    int solve() {
        stack<sudoku> s; 
        s.push(field);
        return 0;
    }

    void print() {

    }
};

void test_set_clear() {
    bs bs = ALL;

    bs.set(5);
    bs.set(6);
    bs.print();
    bs.clear(5);
    bs.print();
    
    assert(bs.isSet(6));

}

// how to pass a 2d array:  https://stackoverflow.com/a/17569578/887836
void from_file(istream &input, bs (&output)[9][9]) {
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




#ifdef TEST
void test_all() {
    test_set_clear();

}

int main() {
    test_all();
}
#endif

#ifndef TEST
int main(int argc, char **argv) {
    bs input[9][9];
    from_file(std::cin, input);

    sudoku s = std::move(input);

    auto ret = s.solve();

    if (ret == 0) {
        s.print();
    } else { 
        std::cout << "unsolvable\n";
    }

    return 0;
}
#endif
