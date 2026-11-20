#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <stddef.h>
#define MAX_ASSETS 128
#define MAX_NAME 32
typedef struct { char symbol[MAX_NAME]; int price; int return_score; int risk; int sector; int transaction_limit; } Asset;
typedef struct { int selected[MAX_ASSETS]; int count; int cost; int return_score; int risk; } Portfolio;
typedef struct { char name[40]; Portfolio portfolio; double time_ms; size_t memory_bytes; int exact; } StrategyResult;
int load_assets_csv(const char *path, Asset *assets, int max_assets);
int save_assets_csv(const char *path, const Asset *assets, int n);
void print_assets(const Asset *assets, int n);
int validate_assets(const Asset *assets, int n);
Portfolio portfolio_greedy(const Asset *assets, int n, int budget, int risk_limit);
Portfolio portfolio_dp(const Asset *assets, int n, int budget, int risk_limit);
Portfolio portfolio_bruteforce(const Asset *assets, int n, int budget, int risk_limit);
Portfolio portfolio_bnb(const Asset *assets, int n, int budget, int risk_limit, int mode);
void print_portfolio(const char *title, const Asset *assets, Portfolio p);
int export_comparison_csv(const char *path, const StrategyResult *results, int n);
int export_comparison_json(const char *path, const StrategyResult *results, int n, const Asset *assets);
void merge_sort_assets(Asset *a, int n);
void quick_sort_assets(Asset *a, int n);
int binary_search_iterative(const Asset *a, int n, const char *symbol);
int binary_search_recursive(const Asset *a, int left, int right, const char *symbol);
int maximum_subarray(const int *a, int n);
long long fast_power(long long base, unsigned int exp);
int celebrity(const int *matrix, int n);
void matrix_multiply_classic(const int *a, const int *b, int *c, int n);
void matrix_multiply_strassen(const int *a, const int *b, int *c, int n);
int activity_selection(const int *start, const int *finish, int n);
int interval_partitioning(const int *start, const int *finish, int n);
int huffman_weighted_path_length(const int *freq, int n);
void dijkstra(const int *g, int n, int src, int *dist);
int prim_mst(const int *g, int n);
int kruskal_mst(const int *g, int n);
int knapsack01(const int *weight, const int *value, int n, int capacity);
long long matrix_chain(const int *dims, int n);
int lcs_length(const char *a, const char *b);
int optimal_bst_cost(const int *freq, int n);
int bellman_ford(const int *edges, int edge_count, int vertices, int src, int *dist);
void floyd_warshall(int *g, int n);
int tsp_bounded(const int *g, int n);
int nqueens_count(int n);
int subset_sum(const int *a, int n, int target);
int ford_fulkerson(const int *capacity, int n, int source, int sink);
int bipartite_matching(const int *g, int left_n, int right_n);
long long crt(const long long *rem, const long long *mod, int n);
int naive_match_count(const char *text, const char *pat);
int rabin_karp_count(const char *text, const char *pat);
int finite_automaton_count(const char *text, const char *pat);
int kmp_count(const char *text, const char *pat);
#endif
