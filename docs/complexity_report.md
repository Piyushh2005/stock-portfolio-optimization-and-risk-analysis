# Complexity and Correctness Report

## Core Portfolio Problem
The decision form asks whether a subset of assets can satisfy budget and risk constraints while reaching a target return. It is a multidimensional 0/1 knapsack-style problem. Exact enumeration is exponential in asset count. The implemented dynamic program is pseudo-polynomial in asset count, budget, and risk limit. Branch-and-bound has exponential worst-case time but can prune large parts of the search tree. The greedy heuristic is fast but is not guaranteed optimal.

For `n` assets, budget `B`, and risk limit `R`, the reconstruction-safe DP uses `Theta(nBR)` time and `Theta(nBR)` memory. Branch-and-bound is `O(2^n)` in the worst case; its live-node memory is input/order dependent. The greedy implementation is `O(n^2)` because it uses an in-place pairwise ranking of asset indices before selection.

## Recurrences and Asymptotic Results
Merge sort follows `T(n)=2T(n/2)+Theta(n)`, giving `Theta(n log n)` time and `Theta(n)` auxiliary space. Recursive binary search follows `T(n)=T(n/2)+Theta(1)`, giving `Theta(log n)` time and stack space. Divide-and-conquer maximum subarray follows `T(n)=2T(n/2)+Theta(n)`, giving `Theta(n log n)`. Fast powering follows `T(n)=T(n/2)+Theta(1)`, giving `Theta(log n)`. Classical matrix multiplication is `Theta(n^3)`. Strassen follows `T(n)=7T(n/2)+Theta(n^2)`, approximately `Theta(n^2.807)`.

Quicksort is expected `Theta(n log n)` and worst-case `Theta(n^2)`. Dijkstra and Prim use adjacency matrices and are `Theta(V^2)`. Kruskal is dominated by edge ordering in this educational implementation. Bellman-Ford is `Theta(VE)`. Floyd-Warshall is `Theta(V^3)`. Ford-Fulkerson depends on the number of augmentations for integral capacities. KMP is linear after prefix preprocessing; finite-automaton matching uses a precomputed transition table; naive matching is `O(nm)`; Rabin-Karp is expected linear for suitable hashing but can degrade under collisions.

## Complexity Classes and Reduction Mapping
Sorting, binary search, shortest paths, minimum spanning tree, maximum flow, and bipartite matching have polynomial-time algorithms here. Exact bounded TSP and general binary portfolio selection are combinatorial optimization problems. The portfolio problem contains 0/1 knapsack as a special case: set every risk value to zero (or make the risk limit nonbinding), map item weight to asset price, item value to return score, and knapsack capacity to budget. Therefore an exact solver for the generalized portfolio problem can solve 0/1 knapsack instances.

## Correctness Evidence
Known-answer and edge-case tests cover the mandatory algorithm library. Classical and Strassen multiplication are compared directly, including a recursive 4x4 case. Prim and Kruskal are checked against the same MST weight. Bellman-Ford is tested with and without a reachable negative cycle. All four string matchers are checked on overlapping matches. For 500 deterministic randomized small portfolio instances, brute-force enumeration acts as the oracle and its optimum is compared with dynamic programming and FIFO, LIFO, and least-cost/best-bound branch-and-bound; reconstructed portfolios are also revalidated against budget and risk constraints.

## Empirical Benchmark Design
`benchmark_runner` measures merge sort and quick sort on 100, 1,000, 10,000, and 50,000 reverse-ordered records plus a 50,000-record duplicate-heavy adversarial workload. It also compares greedy and exact dynamic programming under the normal and constraint-shock portfolio scenarios. The CSV records measured CPU time, an estimated working-memory footprint, exact/heuristic quality, and either sorting correctness or portfolio objective value.

## Production Strategy
For bounded academic instances, dynamic programming is a reliable exact baseline and branch-and-bound is useful when pruning is effective. The greedy strategy is suitable when latency matters more than exact optimality. Large production portfolio systems should not assume pseudo-polynomial or exponential methods scale to unrestricted budgets, risk dimensions, and asset counts; specialized mathematical optimization, approximation, or domain-specific solvers are appropriate beyond the laboratory scope.
