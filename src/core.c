#include "portfolio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

int load_assets_csv(const char *path, Asset *assets, int max_assets) {
    FILE *f = fopen(path, "r");
    char line[256];
    int n = 0;
    if (!f) return -1;
    if (!fgets(line, sizeof(line), f)) { fclose(f); return 0; }
    while (n < max_assets && fgets(line, sizeof(line), f)) {
        Asset x;
        if (sscanf(line, "%31[^,],%d,%d,%d,%d,%d", x.symbol, &x.price, &x.return_score, &x.risk, &x.sector, &x.transaction_limit) == 6) assets[n++] = x;
    }
    fclose(f);
    return n;
}
int save_assets_csv(const char *path, const Asset *assets, int n) {
    FILE *f = fopen(path, "w"); int i;
    if (!f) return 0;
    fprintf(f, "symbol,price,return,risk,sector,transaction_limit\n");
    for (i=0;i<n;i++) fprintf(f, "%s,%d,%d,%d,%d,%d\n", assets[i].symbol, assets[i].price, assets[i].return_score, assets[i].risk, assets[i].sector, assets[i].transaction_limit);
    fclose(f); return 1;
}
void print_assets(const Asset *a, int n) {
    int i;
    printf("%-14s %-8s %-8s %-6s %-7s %-10s\n", "Symbol", "Price", "Return", "Risk", "Sector", "TxnLimit");
    for(i=0;i<n;i++) printf("%-14s %-8d %-8d %-6d %-7d %-10d\n",a[i].symbol,a[i].price,a[i].return_score,a[i].risk,a[i].sector,a[i].transaction_limit);
}
int validate_assets(const Asset *a, int n) {
    int i,j;
    if(n<=0||n>MAX_ASSETS) return 0;
    for(i=0;i<n;i++) {
        if(a[i].symbol[0]=='\0'||a[i].price<=0||a[i].return_score<0||a[i].risk<0||a[i].transaction_limit<=0) return 0;
        for(j=i+1;j<n;j++) if(strcmp(a[i].symbol,a[j].symbol)==0) return 0;
    }
    return 1;
}
static Portfolio empty_portfolio(void) { Portfolio p; memset(&p,0,sizeof(p)); return p; }
Portfolio portfolio_greedy(const Asset *a,int n,int budget,int risk_limit) {
    int idx[MAX_ASSETS],i,j,t; Portfolio p=empty_portfolio();
    if(!a||n<=0||n>MAX_ASSETS||budget<0||risk_limit<0) return p;
    for(i=0;i<n;i++) idx[i]=i;
    for(i=0;i<n;i++) for(j=i+1;j<n;j++) if((long long)a[idx[j]].return_score*(a[idx[i]].risk+1)*(a[idx[i]].price) > (long long)a[idx[i]].return_score*(a[idx[j]].risk+1)*(a[idx[j]].price)) { t=idx[i];idx[i]=idx[j];idx[j]=t; }
    for(i=0;i<n;i++){ int k=idx[i]; if(p.cost+a[k].price<=budget&&p.risk+a[k].risk<=risk_limit){p.selected[p.count++]=k;p.cost+=a[k].price;p.risk+=a[k].risk;p.return_score+=a[k].return_score;}}
    return p;
}
Portfolio portfolio_dp(const Asset *a,int n,int budget,int risk_limit) {
    size_t cells, stages, total_cells;
    int *dp;
    Portfolio p=empty_portfolio();
    int i,b,r;
    if(!a||n<=0||n>MAX_ASSETS||budget<0||risk_limit<0) return p;
    cells=(size_t)(budget+1)*(size_t)(risk_limit+1);
    stages=(size_t)n+1;
    if(cells==0 || stages > SIZE_MAX/cells || stages*cells > SIZE_MAX/sizeof(int)) return p;
    total_cells=stages*cells;
    dp=calloc(total_cells,sizeof(int));
    if(!dp) return p;
    for(i=1;i<=n;i++) {
        int price=a[i-1].price, arisk=a[i-1].risk, value=a[i-1].return_score;
        for(b=0;b<=budget;b++) for(r=0;r<=risk_limit;r++) {
            size_t cur=(size_t)i*cells+(size_t)b*(risk_limit+1)+r;
            size_t prev=(size_t)(i-1)*cells+(size_t)b*(risk_limit+1)+r;
            int best=dp[prev];
            if(b>=price&&r>=arisk) {
                size_t take=(size_t)(i-1)*cells+(size_t)(b-price)*(risk_limit+1)+(r-arisk);
                int v=dp[take]+value;
                if(v>best) best=v;
            }
            dp[cur]=best;
        }
    }
    b=budget; r=risk_limit;
    for(i=n;i>=1;i--) {
        size_t cur=(size_t)i*cells+(size_t)b*(risk_limit+1)+r;
        size_t prev=(size_t)(i-1)*cells+(size_t)b*(risk_limit+1)+r;
        if(dp[cur]!=dp[prev]) {
            int k=i-1;
            p.selected[p.count++]=k;
            p.cost+=a[k].price; p.risk+=a[k].risk; p.return_score+=a[k].return_score;
            b-=a[k].price; r-=a[k].risk;
        }
    }
    free(dp);
    return p;
}
static void brute_rec(const Asset *a,int n,int i,int budget,int risk,int cost,int usedrisk,int value,Portfolio *cur,Portfolio *best){int k;if(cost>budget||usedrisk>risk)return;if(i==n){if(value>best->return_score){*best=*cur;best->cost=cost;best->risk=usedrisk;best->return_score=value;}return;}brute_rec(a,n,i+1,budget,risk,cost,usedrisk,value,cur,best);k=cur->count;cur->selected[cur->count++]=i;brute_rec(a,n,i+1,budget,risk,cost+a[i].price,usedrisk+a[i].risk,value+a[i].return_score,cur,best);cur->count=k;}
Portfolio portfolio_bruteforce(const Asset *a,int n,int budget,int risk_limit){Portfolio cur=empty_portfolio(),best=empty_portfolio();if(n<0||n>24||budget<0||risk_limit<0)return best;brute_rec(a,n,0,budget,risk_limit,0,0,0,&cur,&best);return best;}
typedef struct {int level,cost,risk,value; double bound; unsigned char chosen[MAX_ASSETS];} Node;
static double node_bound(const Asset *a,int n,const Node *x,int budget,int risk){int i;double v=x->value;if(x->cost>budget||x->risk>risk)return -1;for(i=x->level;i<n;i++)v+=a[i].return_score;return v;}
static int push_node(Node **q,size_t *count,size_t *cap,const Node *x){Node *tmp;if(*count==*cap){size_t nc=*cap?*cap*2:256;if(nc>*cap && nc<=SIZE_MAX/sizeof(Node)){tmp=realloc(*q,nc*sizeof(Node));if(!tmp)return 0;*q=tmp;*cap=nc;}else return 0;}(*q)[(*count)++]=*x;return 1;}
Portfolio portfolio_bnb(const Asset *a,int n,int budget,int risk_limit,int mode){Node *q=NULL,root,bestnode;size_t count=0,cap=0,pos,j;int i,bestv=0;Portfolio p=empty_portfolio();if(!a||n<=0||n>MAX_ASSETS||budget<0||risk_limit<0||mode<0||mode>2)return p;memset(&root,0,sizeof(root));memset(&bestnode,0,sizeof(bestnode));root.bound=node_bound(a,n,&root,budget,risk_limit);if(!push_node(&q,&count,&cap,&root))return p;while(count){pos=0;if(mode==1)pos=count-1;else if(mode==2)for(j=1;j<count;j++)if(q[j].bound>q[pos].bound)pos=j;Node x=q[pos];q[pos]=q[--count];if(x.level>=n||x.bound<=bestv)continue;i=x.level;Node y=x;y.level=i+1;y.cost+=a[i].price;y.risk+=a[i].risk;y.value+=a[i].return_score;y.chosen[i]=1;if(y.cost<=budget&&y.risk<=risk_limit){if(y.value>bestv){bestv=y.value;bestnode=y;}y.bound=node_bound(a,n,&y,budget,risk_limit);if(y.bound>bestv&&!push_node(&q,&count,&cap,&y)){free(q);return empty_portfolio();}}y=x;y.level=i+1;y.chosen[i]=0;y.bound=node_bound(a,n,&y,budget,risk_limit);if(y.bound>bestv&&!push_node(&q,&count,&cap,&y)){free(q);return empty_portfolio();}}free(q);for(i=0;i<n;i++)if(bestnode.chosen[i]){p.selected[p.count++]=i;p.cost+=a[i].price;p.risk+=a[i].risk;p.return_score+=a[i].return_score;}return p;}
void print_portfolio(const char *title,const Asset *a,Portfolio p){int i;printf("\n%s\n",title);printf("Selected: ");for(i=0;i<p.count;i++)printf("%s%s",a[p.selected[i]].symbol,i+1==p.count?"":" ");printf("\nCost: %d  Return score: %d  Risk: %d\n",p.cost,p.return_score,p.risk);}
int export_comparison_csv(const char *path,const StrategyResult *r,int n){FILE*f=fopen(path,"w");int i;if(!f)return 0;fprintf(f,"strategy,cost,return,risk,time_ms,memory_bytes,exact\n");for(i=0;i<n;i++)fprintf(f,"%s,%d,%d,%d,%.6f,%zu,%d\n",r[i].name,r[i].portfolio.cost,r[i].portfolio.return_score,r[i].portfolio.risk,r[i].time_ms,r[i].memory_bytes,r[i].exact);fclose(f);return 1;}
int export_comparison_json(const char *path,const StrategyResult *r,int n,const Asset *a){FILE*f=fopen(path,"w");int i,j;if(!f)return 0;fprintf(f,"{\n  \"results\": [\n");for(i=0;i<n;i++){fprintf(f,"    {\"strategy\":\"%s\",\"cost\":%d,\"return\":%d,\"risk\":%d,\"time_ms\":%.6f,\"memory_bytes\":%zu,\"exact\":%s,\"assets\":[",r[i].name,r[i].portfolio.cost,r[i].portfolio.return_score,r[i].portfolio.risk,r[i].time_ms,r[i].memory_bytes,r[i].exact?"true":"false");for(j=0;j<r[i].portfolio.count;j++)fprintf(f,"\"%s\"%s",a[r[i].portfolio.selected[j]].symbol,j+1==r[i].portfolio.count?"":",");fprintf(f,"]}%s\n",i+1==n?"":",");}fprintf(f,"  ]\n}\n");fclose(f);return 1;}
