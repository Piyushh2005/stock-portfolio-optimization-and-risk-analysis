# Stock Portfolio Selection and Risk Analysis Lab

Portable C11 implementation of Project 19. The project provides an interactive portfolio experimentation CLI, a reusable algorithm library, an automated correctness suite, benchmark runner, sample financial data, CSV/JSON exports, and demonstration documentation.

## Build

### CMake

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

### Make

```sh
make
make test
```

Run commands from the project root so `data/` and `output/` resolve correctly.

## Executables

- `portfolio_lab` - menu-driven application.
- `portfolio_tests` - deterministic, edge-case, and randomized brute-force-oracle tests.
- `benchmark_runner` - empirical sorting and portfolio benchmarks; writes `output/benchmark_results.csv`.

Windows PowerShell with CMake normally runs the generated `.exe` files from `build` (or the configuration subdirectory used by your generator).

## Main CLI

1. Portfolio Analysis
2. Asset Sorting & Searching
3. Financial Demonstration Scenarios
4. Algorithm Laboratory
5. Export Portfolio Comparison
6. View Assets
0. Exit

## Portfolio Model

Each asset is a typed record containing symbol, price, expected-return score, risk score, sector, and transaction limit. The laboratory optimization is a binary (0/1) portfolio: maximize aggregate return score while total price stays within budget and aggregate risk stays within the risk limit. The supplied data uses transaction limit `1`, consistent with binary selection.

The same portfolio instance can be solved by a greedy heuristic, dynamic programming, FIFO branch-and-bound, LIFO branch-and-bound, and least-cost/best-bound branch-and-bound. Exact methods are checked against brute force on randomized small instances.

## Mandatory Algorithm Coverage

The reusable library includes merge sort, quick sort, iterative/recursive binary search, maximum subarray, fast powering, celebrity discovery, classical/Strassen multiplication, activity selection, interval partitioning, Huffman coding cost, Dijkstra, Prim, Kruskal, 0/1 knapsack, matrix chain, LCS, optimal BST, Bellman-Ford, Floyd-Warshall, bounded TSP, N-Queens, subset sum, FIFO/LIFO/least-cost branch-and-bound, Ford-Fulkerson, bipartite matching, CRT, naive matching, Rabin-Karp, finite-automaton matching, and KMP.

## Required Demonstrations

`Financial Demonstration Scenarios` runs:

- Normal operation: budget 10000, risk 20; compares five portfolio strategies.
- Constraint shock: budget 5000, risk 10; compares the same five strategies.
- Large-data stress: 50,000 generated records; compares merge sort and quick sort.

The benchmark runner additionally includes small, medium, large, stress, and duplicate-heavy adversarial sorting workloads plus normal/shock portfolio comparisons. `space_bytes` is a documented working-memory estimate; `time_ms` is measured CPU time.

## Output Files

- `output/portfolio_comparison.csv`
- `output/portfolio_comparison.json`
- `output/benchmark_results.csv`
- `output/full_demo_run.txt`
- `output/test_results.txt`

## Validation

The Makefile keeps the public header search path in `CPPFLAGS`, so callers may override `CFLAGS` (for example to add `-Werror` or sanitizers) without breaking compilation.

Use `make test` or CTest. The suite verifies known answers for the mandatory algorithms and runs 500 deterministic randomized portfolio instances where brute force is the oracle for dynamic programming and all three branch-and-bound disciplines. Exported JSON and CSV files are also generated and syntax-checked during the final release audit.
