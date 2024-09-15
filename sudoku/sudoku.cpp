#include <iostream>
#include <cmath>
#include <unordered_set>
#include "sudoku.hpp"

Sudoku::Sudoku(size_t n) {
    size_t root = sqrt(n);
    if(root*root != n) {
        throw std::logic_error("Wrong size of sudoku");
    } 

    for(size_t i = 0; i < n; ++i) {
        grid.emplace_back(std::vector<size_t>(n, 0));
    }
}

void Sudoku::set_position(size_t i, size_t j, size_t value) {
    grid.at(i).at(j) = value;
}

size_t Sudoku::get_value(size_t i, size_t j) {
    return grid.at(i).at(j);
}

size_t Sudoku::duplicates_col(size_t i) {
    std::unordered_set<size_t> unique;
    
    for(size_t j = 0; j < grid.size(); ++j) {
        unique.insert(grid[j][i]);
    }

    return grid.size()-unique.size();
}

size_t Sudoku::duplicates_row(size_t i) {
    std::unordered_set<size_t> unique;
    for(size_t j = 0; j < grid.size(); ++j) {
        unique.insert(grid[i][j]);
    }

    return grid.size()-unique.size();
}


void Sudoku::print_sudoku() {
    for(size_t i = 0; i < grid.size(); ++i) {
        std::cout << '\n';
        
        if(i % static_cast<size_t>(sqrt(grid.size())) == 0) {
            std::cout << ' ';
            
            std::cout << '\n';
        }

        for(size_t j = 0; j < grid.size(); ++j) {
            if(j != 0 && j % static_cast<size_t>(sqrt(grid.size())) == 0) {
                std::cout << " |";
            }
            std::cout << ' ' << grid[i][j] ; 
        }
    }

    std::cout << "\n\n\n";
}
