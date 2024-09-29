#include <cstdio>
#include <cassert>
#include <iostream>

#include "sudoku.h"

using namespace std;


int main(int argc, char **argv) {
    bs input[9][9];
    from_file(std::cin, input);

    sudoku s = std::move(input);

    auto ret = s.solve();

    if (ret == 0) {
    } else { 
        std::cout << "unsolvable\n";
    }

    return 0;
}
