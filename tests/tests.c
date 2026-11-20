#include "portfolio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do{if(!(x)){printf("FAIL line %d: %s\n",__LINE__,#x);return 1;}}while(0)
static int portfolio_valid(const Asset *a,Portfolio p,int budget,int risk){int i,c=0,r=0,v=0,seen[MAX_ASSETS]={0};for(i=0;i<p.count;i++){int k=p.selected[i];if(k<0||k>=MAX_ASSETS||seen[k])return 0;seen[k]=1;c+=a[k].price;r+=a[k].risk;v+=a[k].return_score;}return c==p.cost&&r==p.risk&&v==p.return_score&&c<=budget&&r<=risk;}
int main(void){
 Asset a[]={{"D",400,6,2,1,1},{"A",100,4,1,1,1},{"C",300,5,2,1,1},{"B",200,7,3,1,1}},b[4];
 int x[]={-2,1,-3,4,-1,2,1,-5,4},neg[]={-8,-3,-6,-2,-5,-4};
 int cm[]={0,1,1,0,0,1,0,0,0},nocm[]={0,1,1,0};
 int A[]={1,2,3,4},B[]={5,6,7,8},C[4],D[4];
 int A4[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},I4[]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},C4[16],D4[16];
 int st[]={1,3,0,5,8,5},fn[]={2,4,6,7,9,9},freq[]={5,9,12,13,16,45};
 int g[]={0,2,0,6,0,2,0,3,8,5,0,3,0,0,7,6,8,0,0,9,0,5,7,9,0},dist[5];
 int w[]={10,20,30},v[]={60,100,120},dims[]={40,20,30,10,30},of[]={34,8,50};
 int edges[]={0,1,-1,0,2,4,1,2,3,1,3,2,1,4,2,3,2,5,3,1,1,4,3,-3};
 int negcycle[]={0,1,1,1,2,-1,2,0,-1};
 int fw[]={0,5,999999,10,999999,0,3,999999,999999,999999,0,1,999999,999999,999999,0};
 int tg[]={0,10,15,20,10,0,35,25,15,35,0,30,20,25,30,0};
 int ss[]={3,34,4,12,5,2},flow[]={0,16,13,0,0,0,0,0,10,12,0,0,0,4,0,0,14,0,0,0,9,0,0,20,0,0,0,7,0,4,0,0,0,0,0,0};
 int bg[]={1,1,0,1,0,1,0,1,1}; long long rr[]={2,3,2},mm[]={3,5,7},badm[]={4,6}; long long badr[]={1,2};
 Portfolio dp,bf,bn; memcpy(b,a,sizeof(a));merge_sort_assets(b,4);CHECK(!strcmp(b[0].symbol,"A")&&!strcmp(b[3].symbol,"D"));CHECK(binary_search_iterative(b,4,"C")==2);CHECK(binary_search_recursive(b,0,3,"B")==1);CHECK(binary_search_iterative(b,4,"Z")==-1);memcpy(b,a,sizeof(a));quick_sort_assets(b,4);CHECK(!strcmp(b[0].symbol,"A")&&!strcmp(b[3].symbol,"D"));
 CHECK(maximum_subarray(x,9)==6);CHECK(maximum_subarray(neg,6)==-2);CHECK(fast_power(2,10)==1024);CHECK(celebrity(cm,3)==2);CHECK(celebrity(nocm,2)==-1);
 matrix_multiply_classic(A,B,C,2);matrix_multiply_strassen(A,B,D,2);CHECK(!memcmp(C,D,sizeof(C)));matrix_multiply_classic(A4,I4,C4,4);matrix_multiply_strassen(A4,I4,D4,4);CHECK(!memcmp(C4,D4,sizeof(C4))&&!memcmp(A4,D4,sizeof(A4)));
 CHECK(activity_selection(st,fn,6)==4);CHECK(interval_partitioning(st,fn,6)==3);CHECK(huffman_weighted_path_length(freq,6)==224);
 dijkstra(g,5,0,dist);CHECK(dist[4]==7);CHECK(prim_mst(g,5)==16);CHECK(kruskal_mst(g,5)==16);CHECK(knapsack01(w,v,3,50)==220);CHECK(matrix_chain(dims,5)==26000);CHECK(lcs_length("AGGTAB","GXTXAYB")==4);CHECK(optimal_bst_cost(of,3)==142);
 CHECK(bellman_ford(edges,8,5,0,dist)==1&&dist[4]==1);CHECK(bellman_ford(negcycle,3,3,0,dist)==0);floyd_warshall(fw,4);CHECK(fw[3]==9);CHECK(tsp_bounded(tg,4)==80);CHECK(nqueens_count(4)==2);CHECK(subset_sum(ss,6,9)==1&&subset_sum(ss,6,30)==0);
 CHECK(ford_fulkerson(flow,6,0,5)==23);CHECK(bipartite_matching(bg,3,3)==3);CHECK(crt(rr,mm,3)==23);CHECK(crt(badr,badm,2)==-1);
 CHECK(naive_match_count("AAAAA","AA")==4);CHECK(rabin_karp_count("AAAAA","AA")==4);CHECK(finite_automaton_count("AAAAA","AA")==4);CHECK(kmp_count("AAAAA","AA")==4);CHECK(kmp_count("abc","")==4);
 Portfolio gr=portfolio_greedy(a,4,700,6);dp=portfolio_dp(a,4,700,6);bf=portfolio_bruteforce(a,4,700,6);bn=portfolio_bnb(a,4,700,6,0);CHECK(dp.return_score==bf.return_score);CHECK(bn.return_score==bf.return_score);CHECK(portfolio_valid(a,gr,700,6)&&portfolio_valid(a,dp,700,6)&&portfolio_valid(a,bn,700,6));CHECK(portfolio_greedy(NULL,4,700,6).count==0);CHECK(portfolio_greedy(a,MAX_ASSETS+1,700,6).count==0);CHECK(portfolio_greedy(a,4,-1,6).count==0);CHECK(portfolio_greedy(a,4,700,-1).count==0);
 srand(7);for(int t=0;t<500;t++){Asset q[10];int n=1+rand()%10,budget=100+rand()%1200,risk=1+rand()%20;for(int i=0;i<n;i++){snprintf(q[i].symbol,MAX_NAME,"Q%d",i);q[i].price=20+rand()%300;q[i].return_score=1+rand()%30;q[i].risk=1+rand()%8;q[i].sector=1;q[i].transaction_limit=1;}Portfolio o=portfolio_bruteforce(q,n,budget,risk),d=portfolio_dp(q,n,budget,risk),f=portfolio_bnb(q,n,budget,risk,0),l=portfolio_bnb(q,n,budget,risk,1),c=portfolio_bnb(q,n,budget,risk,2);CHECK(d.return_score==o.return_score&&f.return_score==o.return_score&&l.return_score==o.return_score&&c.return_score==o.return_score);CHECK(portfolio_valid(q,d,budget,risk)&&portfolio_valid(q,f,budget,risk)&&portfolio_valid(q,l,budget,risk)&&portfolio_valid(q,c,budget,risk));}
 printf("All deterministic, edge-case and randomized oracle tests passed\n");return 0;
}
