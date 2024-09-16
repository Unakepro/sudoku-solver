# Sudoku solver

This project implements a simple Sudoku grid and a Simulated Annealing (SA) optimization algorithm to solve the puzzle efficiently.

## Why simulated annealing?

Simulated Annealing (SA) is a great meta-heuristic algorithm that allows globally optimize complex functions. That's why we could use it in the Traveling Salesman Problem (TSP) 
and other optimization problems. While it doesn't guarantee the optimal solution for NP problems like the TSP, SA allows to find a near-optimal solution using heuristics.

In the case of Sudoku, also considered an NP-complete problem (for grids of size n x n), SA offers an optimization approach. For this project, I've chosen to work with 
the classic 9 x 9 Sudoku grid, as it's a well-known version of the puzzle and serves as a great demonstration of the algorithm's capabilities.

## How it works?

So, what is Simulated Annealing (SA)? This algorithm is inspired by the **metallurgy process** where metals are heated and then slowly cooled to create a stronger microstructure. 

Like in the real world for SA, we have Temperature as a parameter. Also, we have cooling_rate and end_temperature which define how fast we cool down and what is the minimal possible temperature. We can consider 
the cooling rate as a hyperparameter alpha. Steps are simply a parameter for our algorithm that limits the maximum possible number of iterations, so in hard problems, it wouldn't take too much time.

Before looking at the pseudocode, let's define some key things:

- **State**: The current configuration of the system (in Sudoku, it’s the grid, and in TSP, it’s the vector of visited points).
- **T**: The current temperature.
- **Energy**: The energy helps rate how efficient the current solution is. We can say it's sort of loss function. In Sudoku,
  the energy function is the sum of duplicate numbers in rows and columns (we don't consider duplicates in regions,
  as they are already filled with unique random numbers to prevent it).


Here’s the pseudocode for SA in this project:

```cpp
void SA(double start_temp, double end_temp, double cooling_rate, size_t steps) {
    currEnergy -> current_state_of_the_system
    double T = start_temp;
    
    size_t i = 0;
    while(i < steps && currEnergy != 0) {

        auto new_state = new_state();
        newEnergy -> new_state;

        if(newEnergy < currEnergy) {
            currEnergy = newEnergy;
        }
        else {
            P = exp(-((newEnergy-currEnergy)/T)
            if(make_transition(P)) {
                currEnergy = newEnergy;
                state -> new_state;
            }
        }

        T = start_temp / (1 + cooling_rate * i); 

        if(T <= end_temp) {
            return ;
        }

        ++i;
    }
}
```
Explanation:

1. We start by measuring the current energy of the system and setting the initial temperature.
2. We iterate while i < steps or until the energy reaches 0 (for Sudoku, energy == 0 means no duplicates, is solved).

---
**NOTE**

It's okay for sudoku, cause 0 energy in this case means, there is no duplication, so Sudoku is solved, but in other problems, you may not terminate like this, cause for TCP you want simply to optimize without  stopping at some number.

---


3. In each iteration, we select a new state (for Sudoku, we select the random region and swap two values that which was not set at start.).
4. We calculate the new energy. If it's lower than the current energy, we accept the new state. If not, we compute a probability using the formula e^(-((newEnergy-currEnergy)/T).
5. To decide if we accept a worse option, we use the **make_transition** function, which compares this probability with a randomly generated number between 0 and 1. If the probability is higher, we accept the worse option.
6. Decrease temperature. 
​
---
**NOTE**
 
I'm talking about minimizing, because it is what we want to do in Sudoku or in TCP, we want to minimize duplicates and a sum of distances corresponding. In another task maybe you want to maximize your energy.

---



## Why we even take worse options somethimes?

Sometimes, accepting worse options allows us to escape local minima. If we only move downhill (as in gradient descent),
we may get stuck in a local minimum and miss the global minimum.

![image](https://github.com/user-attachments/assets/85fee6c8-647e-443f-a3ea-eeed748a5301)

In the picture above we can see the function, and we want to get to the global minimum, but if we go simply down, using gradient descent,
we would go straight to the local minimum and get stuck in it, in order to go through it, we need to go explore uphill, but gradient descent won't allow us to go against minimizing.
So SA sometimes takes worse direction to find a better one later.



## Configuration

To configure Simulated Annealing (SA), we need to set the following parameters:

1. **start_temp** (Initial Temperature)
2. **end_temp** (Final Temperature)
3. **cooling_rate** (Rate at which temperature decreases)
4. **steps** (Maximum number of iterations)

The values for `start_temp`, `end_temp`, and `cooling_rate` depend on the specific task and its complexity. For solving Sudoku, the following configuration works well:

- **start_temp**: 100
- **end_temp**: 0.01
- **cooling_rate**: A value between **0.99** and **0.999** works best.


### Steps

`steps` is used to limit the number of iterations the algorithm will run. For Sudoku, setting `steps` to around **100,000** will prevent the algorithm from running for too long, ensuring a reasonable computation time.





## Run

Now the only step is to run a sudoku solver.

```bash
g++ -std=c++17 main.cpp sudoku/sudoku.cpp
./a.out
```

## Demonstration


