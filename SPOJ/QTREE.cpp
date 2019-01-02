#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair

using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>; 
constexpr int ms = 10010;
constexpr int mlog = 17;


vii g[ms];

// related to LCA
int parent[ms], depth[ms];

void initLCA(int n) {
    memset( parent, -1, sizeof parent);
    memset( depth, -1, sizeof depth );
    for(int i = 0; i < n; ++i) g[i].clear();
}


int main()
{
    ios::sync_with_stdio(0); cin.tie(NULL);
    int t;
    cin >> t;
    while( t-- ) {
        int n;
        cin >> n;
        initLCA(n);
        for(int i = 0; i < n - 1; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            --a;--b;
            g[a].emplace_back(c, b);
            g[b].emplace_back(c, a);
        }
    }

}

