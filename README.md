# Solving the Single-Machine Total Tardiness Problem with Sequence Dependent Setup Times (SMTTP-SDST)

## Problem Definition

We are given:
- **n jobs**, each characterized by:
  - **Processing Time**: `p_i` for job `i`,
  - **Due Date**: `d_i` for job `i`,
  - **Weight**: `w_i` for job `i`.
- **Setup Times**: `s_ij` is the setup time required when processing job `j` after job `i` (sequence-dependent).

The goal is to determine the optimal job sequence on a single machine that minimizes the **total weighted tardiness**. The **tardiness** for job `i` is defined as the time by which job `i` is completed after its due date, or zero if the job is completed on time.

## Steps to Solve SMTTP-SDST

### 1. Completion Time of Jobs

Let the jobs be scheduled in a sequence `σ = (j_1, j_2, ..., j_n)`, where `j_i` represents the job processed in the `i`-th position.

The **completion time** `C_j` for job `j_i` can be computed as:

- For the first job:
  `C_j1 = p_j1`

  (The first job has no previous job, so its completion time is just its processing time.)

- For subsequent jobs (`j2, j3, ..., jn`):
  `C_jk = C_j(k-1) + p_jk + s_j(k-1),jk`

  Where:
  - `C_j(k-1)` is the completion time of the previous job in the sequence,
  - `p_jk` is the processing time of the current job `j_k`,
  - `s_j(k-1),jk` is the setup time between the previous job `j_(k-1)` and the current job `j_k`.

### 2. Tardiness of Jobs

The **tardiness** `T_jk` for job `j_k` is defined as:

`T_jk = max(0, C_jk - d_jk)`

Where:
- `C_jk` is the completion time of job `j_k`,
- `d_jk` is the due date of job `j_k`,
- `T_jk` is the tardiness of job `j_k`, which is zero if the job completes before its due date and positive if it is late.

### 3. Weighted Tardiness

The **weighted tardiness** for each job is calculated by multiplying its tardiness by its weight:

`WT_jk = w_jk * T_jk`

Where:
- `w_jk` is the weight of job `j_k`,
- `T_jk` is the tardiness of job `j_k`.

### 4. Total Weighted Tardiness (Objective Function)

The **total weighted tardiness** for the entire schedule is the sum of the weighted tardiness for all jobs:

`TWT = Σ (w_jk * max(0, C_jk - d_jk))`

Where:
- `TWT` is the **total weighted tardiness** (our objective function to minimize),
- The summation goes over all jobs in the sequence `σ`.

---

## Solving SMTTP-SDST Using Hybrid Algorithms

### Genetic Algorithm (GA):
- **Initialization**: Start with a random population of job sequences.
- **Crossover**: Combine two parent sequences using the **Order Crossover (OX)** method to create offspring.
- **Mutation**: Apply a random swap between two jobs in a sequence with a small probability (mutation probability).
- **Fitness**: The fitness function is the **total weighted tardiness** `TWT`, which we want to minimize.
- **Selection**: Select parents based on their fitness (lower tardiness gets selected more often).

### Tabu Search (TS):
- **Neighborhood Search**: Generate neighboring solutions by swapping pairs of jobs in the sequence and calculate the new **total weighted tardiness**.
- **Tabu List**: Store the recently visited solutions (or moves), and avoid revisiting them for a fixed number of iterations (tabu tenure).
- **Local Optima**: The algorithm attempts to find the best local optimum by exploring neighbors, even if it means temporarily accepting a worse solution (to escape local minima).

### Final Solution:
- After multiple iterations of **Genetic Algorithm** and **Tabu Search**, the best sequence with the lowest **total weighted tardiness** is selected as the final solution.

By combining **Global Search** (GA) with **Local Search** (TS), the hybrid approach efficiently navigates the solution space, balancing exploration and exploitation to find high-quality solutions for the SMTTP-SDST.

---

## Example

Suppose we have 3 jobs with the following data:

| Job | Processing Time `p_i` | Due Date `d_i` | Weight `w_i` |
|-----|-----------------------|-----------------|--------------|
| 1   | 3                     | 5               | 2            |
| 2   | 4                     | 8               | 1            |
| 3   | 2                     | 6               | 3            |

And the setup times are:

| Setup Times  | 1  | 2  | 3  |
|--------------|----|----|----|
| From Job 1   | 0  | 2  | 3  |
| From Job 2   | 2  | 0  | 1  |
| From Job 3   | 3  | 1  | 0  |

If we schedule jobs in the order `σ = (1, 3, 2)`, then we can compute the **completion times**, **tardiness**, and **total weighted tardiness** using the formulas described earlier.

---

Let me know if you need further clarification or a specific example calculation!
