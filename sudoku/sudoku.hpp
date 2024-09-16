#ifndef SUDOKU
#define SUDOKU

#include <iostream>

class Sudoku {
    std::vector<std::vector<size_t>> grid;
    std::vector<std::vector<bool> > fixed;

public:
    Sudoku(size_t n);

    void set_position(size_t i, size_t j, size_t value);
    void set_row(size_t i, std::vector<size_t>&& value);

    size_t get_value(size_t i, size_t j);

    size_t duplicates_col(size_t i);
    size_t duplicates_row(size_t i); 
    size_t total_cost();

    void sa_optimization(double start_temp, double end_temp, double cooling_rate, size_t steps);
    auto new_state_energy(size_t sq_n);
    
    bool make_transition(long double P);

    void make_fixed();
    void print_fixed();
    void fill_randomly();
    void print_sudoku();
};


#endif