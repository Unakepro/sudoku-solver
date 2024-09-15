#include <iostream>
#include "sudoku/sudoku.hpp"

int main() {
    Sudoku xs(9);
    
    std::vector<size_t> row1{3, 0, 4, 5, 6, 0, 9, 0, 0};
    std::vector<size_t> row2{1, 8, 5, 0, 0, 9, 7, 0, 0};
    std::vector<size_t> row3{0, 0, 0, 0, 7, 8, 4, 1, 5};
    std::vector<size_t> row4{0, 2 ,0, 0, 1, 0, 0, 4, 9};
    std::vector<size_t> row5{0, 4, 9, 0, 5, 0, 0, 0, 0};
    std::vector<size_t> row6{0, 0, 1, 9, 8, 0, 6, 7, 0};
    std::vector<size_t> row7{4, 9, 0, 0, 3, 0, 0, 0, 7};
    std::vector<size_t> row8{0, 1, 8, 7, 4, 5, 0, 0, 6};
    std::vector<size_t> row9{0, 0, 0, 0, 0, 0, 0, 8, 0};

    xs.set_row(0, std::move(row1));
    xs.set_row(1, std::move(row2));
    xs.set_row(2, std::move(row3));
    xs.set_row(3, std::move(row4));
    xs.set_row(4, std::move(row5));
    xs.set_row(5, std::move(row6));
    xs.set_row(6, std::move(row7));
    xs.set_row(7, std::move(row8));
    xs.set_row(8, std::move(row9));

    xs.sa_optimization(150, 0.01, 0.9999, 100000);
    xs.print_sudoku();

}