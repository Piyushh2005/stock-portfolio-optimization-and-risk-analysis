# User Guide

Run the program from the project root. Asset data is read from `data/assets.csv`; built-in sample assets are used if the CSV cannot be opened.

## Portfolio Analysis
Enter a positive budget and a nonnegative maximum risk. The program compares greedy, dynamic programming, FIFO branch-and-bound, LIFO branch-and-bound, and least-cost/best-bound branch-and-bound on the same input and prints cost, return score, risk, timing, exactness, and selected symbols.

## Asset Sorting & Searching
Assets are sorted by symbol with merge sort. Enter a symbol such as `TCS`; iterative and recursive binary search report its index. Quick sort is then used as the alternative sorting implementation.

## Financial Demonstration Scenarios
Runs all three required demonstrations: normal operation, a tighter budget/risk constraint shock, and a 50,000-record large-data stress comparison between merge sort and quick sort.

## Algorithm Laboratory
Runs representative inputs through the remaining mandatory syllabus algorithms and prints their results.

## Export Portfolio Comparison
Enter a positive budget and nonnegative risk limit. The command writes `output/portfolio_comparison.csv` and `output/portfolio_comparison.json`.

## Benchmarks and Tests
Run `benchmark_runner` to regenerate `output/benchmark_results.csv`. Run `portfolio_tests`, `make test`, or CTest to execute deterministic, edge-case, and randomized oracle tests.
