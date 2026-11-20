# Design Guide

The project is split into a reusable C11 algorithm library and three executables. `portfolio_lab` is the interactive product, `portfolio_tests` provides correctness evidence, and `benchmark_runner` produces empirical results.

Asset data is stored in typed `Asset` records and arrays. Matrices represent weighted, capacitated, and bipartite graphs. Dynamic-programming tables and search-tree nodes represent optimization state. The portfolio objective is a two-constraint binary optimization problem: maximize aggregate return score while total price does not exceed budget and aggregate risk does not exceed the risk limit.

The primary comparison uses a greedy heuristic, dynamic programming, and three branch-and-bound queue disciplines. FIFO selects the oldest live node, LIFO selects the newest, and the least-cost variant treats the negative upper bound as cost, equivalently selecting the live node with the greatest return upper bound. Branch-and-bound nodes store an explicit selection vector, so they support the full `MAX_ASSETS` range without a 64-bit mask limitation. The live-node container grows dynamically instead of silently dropping nodes.

The dynamic-programming solver retains per-stage state so the selected portfolio can be reconstructed consistently with the optimum value. Brute force is intentionally bounded to small instances and is used as a correctness oracle in tests.

Sorting and portfolio benchmarks report measured CPU time and estimated algorithm working memory. Large unrestricted financial optimization is outside the intended laboratory scale; the complexity report explains the production tradeoff.
