#include <iostream>
#include <cmath>
#include <unordered_set>
#include <random>
#include "sudoku.hpp"

std::random_device rd;
std::mt19937 gen(rd());

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

void Sudoku::set_row(size_t i, std::vector<size_t>&& row) {
    if(row.size() != grid.size()) {
        throw std::logic_error("Wrong row size!");
    }

    grid.at(i) = std::move(row);
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

void Sudoku::fill_randomly() {
    std::uniform_int_distribution<size_t> dist(1, grid.size());

    std::unordered_set<size_t> region;
    size_t sq_size = sqrt(grid.size());
    
    for(size_t i = 0; i < sq_size; ++i) {
        for(size_t n = 0; n < sq_size; ++n) {
            
            for(size_t j = 0; j < sq_size; ++j) {
                for(size_t k = 0; k < sq_size; ++k) {
                    region.insert(grid.at((i*sq_size)+j).at(k+(n*sq_size)));
                }
            }

            for(size_t j = 0; j < sq_size; ++j) {
                for(size_t k = 0; k < sq_size; ++k) {
                    if(grid.at((i*sq_size)+j).at(k+(n*sq_size)) == 0) {
                        size_t rand_num = dist(gen);

                        while(region.find(rand_num) != region.end()) {
                            rand_num = dist(gen);
                        }
                        
                        region.insert(rand_num);
                        grid.at((i*sq_size)+j).at(k+(n*sq_size)) = rand_num;
                    }            
                }
            }
            
            region.clear();
        }
    }
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
