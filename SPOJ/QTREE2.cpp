#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define st first
#define nd second

constexpr int MAXN = 10010;
constexpr int LOGMAXN = 14;

int n, m, u, v;
int anc[MAXN][LOGMAXN], dad[MAXN], lvl[MAXN];
long long dist[MAXN];
vector<pair<int, long long> > g[MAXN];

void dfs(int u) {
    for (int i = 0; i < (int) g[u].size(); i++) {
        int v = g[u][i].st;
        long long w = g[u][i].nd;
        if (v != dad[u]) {
            dad[v] = u;
            lvl[v] = lvl[u] + 1;
            dist[v] = dist[u] + w;
            dfs(v);
        }
    }
}


void pre() {
    dad[0] = lvl[0] = dist[0] = 0;
    dfs(0);
    for (int i = 0; i < n; i++)
        anc[i][0] = dad[i];
    for (int j = 1; 1<<j < n; j++)
        for (int i = 0; i < n; i++)
            anc[i][j] = anc[anc[i][j-1]][j-1];
}

int lca(int u, int v) {
    if (lvl[u] < lvl[v])
        swap(u, v);
    int log;
    for (log = 1; (1<<log) <= lvl[u]; log++);
    log--;
    for (int i = log; i >= 0; i--)
        if (lvl[u] - lvl[v] >= (1<<i))
            u = anc[u][i];
    if (u == v)
        return u;
    for (int i = log; i >= 0; i--)
        if (anc[u][i] != anc[v][i])
            u = anc[u][i], v = anc[v][i];
    return dad[u];
}

inline long long D(int u, int v) {
    int X = lca(u, v);
    return (dist[u] + dist[v] - 2 * dist[X] );
}

inline int kth(int u, int v, int K) {
    int X = lca(u, v);
    int pathULen = lvl[u] - lvl[X] + 1;
    int pathVLen = lvl[v] - lvl[X];
    int up, current;
    if( K <= pathULen ) {
        up = K - 1;
        current = u;
        for(int i = 0; i < LOGMAXN; ++i) if((1 << i) & up) current = anc[current][i];
    } 
    else {
        K -= pathULen;
        up = pathVLen - K;
        current = v;
        for(int i = 0; i < LOGMAXN; ++i) if((1 << i) & up) current = anc[current][i];
    }
    return current + 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) {
            dad[i] = -1;
            g[i].clear();
        }
        for(int i = 0; i < n - 1; ++i) {
            int a, b;
            long long w;
            scanf("%d %d %lld", &a, &b, &w);
            --a;--b;
            g[a].emplace_back(b, w);
            g[b].emplace_back(a, w);
        }
        pre();
        char buff[100];
        while(scanf("%s", buff) ) {
            if(buff[1] == 'O') {
                break;
            }
            else if( buff[0] == 'D') {
                int a, b;
                scanf("%d %d", &a, &b);
                --a;--b;
                printf("%lld\n", D(a, b) );
            }
            else {
                int a, b, c;
                scanf("%d %d %d", &a, &b, &c);
                --a;--b;
                printf("%d\n", kth(a, b, c));
            }
        }
    }
    return 0;
}
