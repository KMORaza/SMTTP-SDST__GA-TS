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
* Tardiness of job is: $T_i = max$($0,C_i-d_i$)
