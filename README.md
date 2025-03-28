### Solution of Single-Machine Total Tardiness Problem with Sequence Dependent Setup Times (SMTTP-SDST) using hybrid of Genetic Algorithm & Tabu Search (GA+TS)
---

__(1) PROBLEM DEFINITION__

For a given set of jobs $J =$ { $J_1,J_2,J_3,....,J_n$ }, where each job $J_i$ has:
* Processing time $p_i$ for job $i$
* Due date $d_i$ for job $i$
* Weight $w_i$ for job $i$
* Setup time between jobs $i$ and $j$ denoted as $s_ij$ which is sequence dependent

The goal is to minimize the _total tardiness_, which is the sum of the _weighted tardiness_ for all jobs in a sequence of jobs.

__(2) TARDINESS & WEIGHTED TARDINESS__

For each job $J_i$, the completion time $C_i$ is given by: 

$C_i =$ _Completion time of previous job_ $+$ _Setup time between previous & current job_ $+$ _Processing time of current job_

* If $i=1$, $C_1 = p_1$
* For subsequent jobs $i>1$, then completion time becomes $C_i = C_{i-1} + s_{i-1,i} + p_i$
* Tardiness of job is $T_i = max$($0,C_i-d_i$)
* Weighted taardiness of job is $WT_i = T_i × w_i$
* Total tardiness is $T_{total} = ΣWT_i = Σmax(0,C_i-d_i)×w_i$

__(3) GENETIC ALGORITHM__

Genetic Algorithm is to explore the search space of possible job sequences to find one that minimizes the total tardiness.
* _Population Initialization_ - Generate an initial population of random job sequences. Each individual (solution) in the population represents a permutation of jobs. The fitness of each solution is the total tardiness $T_{total}$ calculated for the sequence.
*  _Selection_ - Select two parent solutions $P_1$ and $P_2$ based on their fitness. Typically, solutions with lower total tardiness are selected.
*  _Crossover_ - Crossover is applied to generate two offspring solutions. Suppose we have two parents, $P_1 = [ J_{i_1}, J_{i_2}, J_{i_3},....,J_{i_n}]$ and $P_2 = [J_{j_1}, J_{j_2}, J_{j_3},....,J_{j_n}]$
  * Select a segment from the first parent, e.g., a subset of jobs from positions $l$ to $r$ in $P_1$
  * Copy this segment to the child sequence.
  * Fill the remaining positions with jobs from $P_2$, maintaining the relative order of jobs from $P_2$, ensuring no repetitions.
* _Mutation_ - Randomly swap two jobs in a sequence to introduce small variations. For a sequence $S = [ J_1,J_2,J_3....J_n]$,  a mutation operation randomly selects two indices $i$ and $j$ and swaps the corresponding jobs $S_{mutated} = [ J_1,....J_i,J_j....J_n]$. The mutation rate is typically low to ensure that exploration is balanced with exploitation.
* _Fitness Evaluation_ - After crossover and mutation, evaluate the fitness (total tardiness) of the new offspring using the formula for total tardiness $T_{total} = Σmax(0,C_i-d_i)×w_i$.
* _Survival Selection_ - The next population is formed by selecting the best individuals from the current population and the newly generated offspring. This step ensures that the population evolves toward better solutions.

__(4) TABU SEARCH FOR LOCAL REFINEMENT__

After applying Genetic Algorithm operations (selection, crossover, mutation), Tabu Search is used to improve the best solutions found by GA through local search.
* _Neighbor Generation_ - A neighbor solution is created by swapping two jobs in the current solution sequence. For a solution $S = [ J_1,J_2,J_3....J_n]$, a neighbor is created by swapping jobs $J_i$ and $J_j$: $S_{neighbor} = [ J_1,....J_i,J_j....J_n]$
* _Tabu Search_
  * Maintain a Tabu List to store recently made moves (e.g., job swaps) to avoid revisiting them. Each move is associated with a Tabu Tenure (a number of iterations the move should be forbidden).
  * If a swap results in a better solution, even if it's in the Tabu List, it might still be accepted, which is called Aspiration Criteria.
* _Move Evaluation_ - After generating the neighbors, each move is evaluated based on the total tardiness formula. If a swap results in a better total tardiness (lower tardiness), then that solution becomes the new current solution.
* _Tabu Update_ - After selecting the best neighbor, update the Tabu List by adding the recent move. If the list exceeds the Tabu Tenure, remove the oldest entries.

__(5) STOPPING CRITERIA__

The algorithm stops after a predefined number of generations or when a stopping condition is met (e.g., no improvement in several iterations).

__(6) BEST SOLUTION__

The best sequence $S_{best}$ found by algorithm, with the lowest totat tardiness $T_{total}$, is returned as the optimal or near-optimal solution. 
