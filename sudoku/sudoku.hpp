#ifndef SUDOKU
#define SUDOKU

#include <iostream>

class Sudoku {
    std::vector<std::vector<size_t>> grid;
    std::vector<std::vector<bool>> fixed;

public:
    Sudoku(size_t n);

    void set_position(size_t i, size_t j, size_t value);
    void set_row(size_t i, std::vector<size_t>&& value);

    size_t get_value(size_t i, size_t j);

    size_t duplicates_col(size_t i);
    size_t duplicates_row(size_t i); 
    size_t total_cost();
    
    void sa_optimization(size_t start_temp, size_t end_temp, size_t cooling_rate, size_t steps);
    void new_state_energy(size_t i);

    void make_fixed();
    void print_fixed();
    void fill_randomly();
    void print_sudoku();
};


#endif