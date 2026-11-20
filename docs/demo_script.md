# Demonstration Script

1. Build with `make` or CMake, then run `portfolio_tests`. Show `output/test_results.txt` or the console message confirming deterministic, edge-case, and randomized oracle tests pass.
2. Run `portfolio_lab` and choose **Portfolio Analysis**. Enter budget `10000` and maximum risk `20`. Explain that all five strategies receive identical inputs; compare return, cost, risk, time, exactness, and selected assets.
3. Choose **Financial Demonstration Scenarios**. Show normal operation, the budget/risk constraint shock, and the 50,000-record stress comparison.
4. Choose **Asset Sorting & Searching** and search for `TCS`. Show merge sort plus iterative/recursive binary search, then the quick-sort verification.
5. Choose **Algorithm Laboratory**. Use the printed known results to demonstrate the remaining mandatory syllabus implementations.
6. Choose **Export Portfolio Comparison** with budget `10000` and risk `20`. Open `output/portfolio_comparison.csv` and `output/portfolio_comparison.json`.
7. Run `benchmark_runner` and open `output/benchmark_results.csv`. Point out small, medium, large, stress, adversarial, normal-portfolio, and shock-portfolio rows.
8. If a complete transcript is useful during evaluation, open `output/full_demo_run.txt`.
