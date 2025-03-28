### Solution of Single-Machine Total Tardiness Problem with Sequence Dependent Setup Times (SMTTP-SDST) using hybrid of Genetic Algorithm & Tabu Search (GA+TS)
---

__(1) Problem Definition__

For a given set of jobs $J =$ { $J_1,J_2,J_3,....,J_n$ }, where each job $J_i$ has:
* Processing time $p_i$ for job $i$
* Due date $d_i$ for job $i$
* Weight $w_i$ for job $i$
* Setup time between jobs $i$ and $j$ denoted as $s_ij$ which is sequence dependent

The goal is to minimize the _total tardiness_, which is the sum of the _weighted tardiness_ for all jobs in a sequence of jobs.
