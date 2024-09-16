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
        grid.emplace_back(std::vector<int16_t>(n, 0));
        fixed.emplace_back(std::vector<bool>(n, false));
    }
}

void Sudoku::set_position(size_t i, size_t j, int16_t value) {
    grid.at(i).at(j) = value;
}

void Sudoku::set_row(size_t i, std::vector<int16_t>&& row) {
    if(row.size() != grid.size()) {
        throw std::logic_error("Wrong row size!");
    }

    grid.at(i) = std::move(row);
}

int16_t Sudoku::get_value(size_t i, size_t j) {
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

size_t Sudoku::total_cost() {
    size_t cost = 0;
    for(size_t i = 0; i < grid.size(); ++i) {
        cost += duplicates_col(i);
        cost += duplicates_row(i);
    }

    return cost;
}


auto Sudoku::new_state_energy(size_t sq_n) {
    if(sq_n < 0 || sq_n >= grid.size()) {
        throw std::logic_error("Wrong square");
    }

    std::vector<std::pair<size_t, size_t>> not_fixed;
    size_t n = sqrt(grid.size());
    
    for(size_t i = (sq_n / n) * n; i < (sq_n / n) * n + n; ++i) {
        for(size_t j = (sq_n % n) * n; j < (sq_n % n) * n + n; ++j) {
            size_t curr_num = grid.at(i).at(j);
            if(fixed.at(i).at(j) == false) {
                not_fixed.emplace_back(i, j);
            }
        }
    }

    std::uniform_int_distribution<size_t> dist(0, not_fixed.size()-1);
    std::pair<int, int> rand_nums{-1, -1};
    
    if(not_fixed.size() <= 1) {
        return std::tuple<std::pair<size_t, size_t>, std::pair<size_t, size_t>, size_t>{std::pair<size_t, size_t>{0, 0}, std::pair<size_t, size_t>{0, 0}, total_cost()};
    }
    
    while(rand_nums.first == -1 || rand_nums.second == -1) {
        if(rand_nums.first == -1) {
            rand_nums.first = dist(gen);
        }
        else {
            size_t rand_n = dist(gen);
            if(rand_nums.first != rand_n) {
                rand_nums.second = rand_n;
                break;
            }
        }
    }   

    std::swap(grid.at(not_fixed[rand_nums.first].first).at(not_fixed[rand_nums.first].second), grid.at(not_fixed[rand_nums.second].first).at(not_fixed[rand_nums.second].second));

    return std::tuple<std::pair<size_t, size_t>, std::pair<size_t, size_t>, size_t>{not_fixed.at(rand_nums.first), not_fixed.at(rand_nums.second), total_cost()};
}

void Sudoku::sa_optimization(double start_temp, double end_temp, double cooling_rate, size_t steps) {
    make_fixed();
    fill_randomly();

    std::uniform_int_distribution<size_t> dist(0, grid.size()-1);

    size_t currEnergy = total_cost();
    double T = start_temp;
    
    size_t i = 0;
    while(i < steps && currEnergy != 0) {

        std::pair<size_t, size_t> num1;
        std::pair<size_t, size_t> num2;

        size_t newEnergy = 0;
        
        auto new_state = new_state_energy(dist(gen));
        newEnergy = std::get<2>(new_state);

        if(newEnergy < currEnergy) {
            currEnergy = newEnergy;
        }
        else {
            if(make_transition(exp(-((newEnergy-currEnergy)/T)))) {
               currEnergy = newEnergy;
            }
            else {
               std::swap(grid.at(std::get<0>(new_state).first).at(std::get<0>(new_state).second), grid.at(std::get<1>(new_state).first).at(std::get<1>(new_state).second));
            }
        }

        T = start_temp / (1 + cooling_rate * i); 

        if(T <= end_temp) {
            return ;
        }

        ++i;
    }
}

bool Sudoku::make_transition(long double P) {
    std::uniform_real_distribution<> dis(0.0, 1.0);
    if(P >= dis(gen)) {
        return true;
    }

    return false;
}

void Sudoku::make_fixed() {
    for(size_t i = 0; i < grid.size(); ++i) {
        for(size_t j = 0; j < grid.size(); ++j) {
            if(grid.at(i).at(j) != 0) {
                fixed.at(i).at(j) = true;
            }
        }
    }
}



void Sudoku::print_fixed() {
    for(size_t i = 0; i < grid.size(); ++i) {
        for(size_t j = 0; j < grid.size(); ++j) {
            if(fixed.at(i).at(j)) {
                std::cout << 1 << ' ';
            }
            else {
                std::cout << 0 << ' ';
            }
        }
        std::cout << '\n';
    }
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
