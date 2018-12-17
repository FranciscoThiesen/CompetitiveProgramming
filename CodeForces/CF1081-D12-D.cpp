#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define TRACE(x)  
#define WATCH(x) TRACE( cout << #x" = " << x << endl)
#define PRINT(x) TRACE(printf(x))
#define WATCHR(a, b) TRACE( for(auto c = a; c != b;) cout << *(c++) << " "; cout << endl)
#define WATCHC(V) TRACE({cout << #V" = "; WATCHR(V.begin(), V.end()); } )
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) (int) (v).size()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define funoredered_map __fast_unordered_map
template<class Key, class Value, class Hash = std::hash<Key>>
using funordered_map = __gnu_pbds::gp_hash_table<Key, Value, Hash>;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr int NINF = 0xc0c0c0c0;
constexpr double EPS = 1e-8;
constexpr ll MOD = 1000000007LL;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ostream &operator<<(ostream& os, const pair<auto, auto>& p) {
    return os << "(" << p.first << "," << p.second << ")";
}

inline ll powmod( ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1) {
        if(b&1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}

inline int cmp_double( double x, double y, double tol = EPS) {
    return (x <= y + tol) ? ( x + tol < y) ? -1 : 0 : 1;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

constexpr int ms = 1e5 + 13;

int special[ms];
vector< pii > g[ms];

vector< tuple<int, int, int> > edges;
vector<int> uniqueEdgeCost;
int visited[ms];
inline void dfsSpecial(int root, int cc, int cost)
{
    visited[root] = cc;
    for(const auto& edg : g[root] ) {
        if(edg.first >= cost) continue;
        if( visited[ edg.second ] == 0) {
            dfsSpecial( edg.second, cc, cost);
        }
    }
}

int main()
{
    int n, m, k, st;
    scanf("%d %d %d", &n, &m, &k);
    rep(i,0,k) {
        int x;
        scanf("%d", &x);
        special[x - 1] = true;
        st = x - 1;
    }
    rep(i, 0, m)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        --a;--b;
        g[a].emplace_back(c, b);
        g[b].emplace_back(c, a);
        edges.emplace_back(c, a, b);
        uniqueEdgeCost.push_back(c);
    }
    sort( rall(edges ) );
    sort( all(uniqueEdgeCost ) );
    uniqueEdgeCost.erase( unique(all(uniqueEdgeCost ) ), uniqueEdgeCost.end() );
    int lo = 0, hi = sz(uniqueEdgeCost) - 1;
    while( lo < hi) {
        memset(visited, 0, sizeof visited);
        int mid = (lo + hi + 1) / 2;
        int cost = uniqueEdgeCost[ mid ];
        dfsSpecial(st, 1, cost);
        TRACE( cout << "fiz a DFS com cost = " << cost << endl; )
        TRACE( cout << " mid = " << mid << endl;)
        bool ok = false;
        rep(i, 0, n) {
            if( special[i] && visited[i] == 0) {
                TRACE( cout <<  "Ok because of " << i << endl; )
                ok = true;
                break;
            }
        }
        if( ok ) {
            lo = mid;
        }
        else hi = mid - 1;
        
    }
    memset(visited, 0, sizeof visited);
    int ans = uniqueEdgeCost[lo];  
    rep(i, 0, k) printf("%d ", ans);
    return 0;
}

