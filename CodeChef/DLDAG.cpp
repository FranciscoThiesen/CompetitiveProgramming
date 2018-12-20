#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define TRACE(x) x
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

constexpr int ms = 1e6 + 13;

vi g[ms];
vi rev[ms];
int deg[ms];
int active[ms];
set< tuple<int, int, int> > q; 
void update(int node) {
    active[node] = 0;
    for(const int& v : rev[node] ) {
        if( active[v] ) {
            q.erase( make_tuple( deg[v], - sz(rev[v]), v) );
            deg[v]--;
            q.insert( make_tuple( deg[v], -sz(rev[v]), v) );
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    // Degree, -sz(rev[idx]) , idx
    rep(i, 0, n) active[i] = 1;   
    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;
        --a;--b;
        rev[b].pb(a);
        deg[a]++;
    }
    vector< pii > res;
    rep(i,0,n) { q.insert( make_tuple(deg[i], -sz(rev[i]), i) ); }
    while( !q.empty() )
    {
        int st = -1, nd = -1;
        auto topo = *(q.begin());
        q.erase(q.begin());
        int x, y, z;
        tie(x, y, z) = topo;
        st = z;
        if(q.empty() ) {
            cout << "1 " << z + 1 << endl;
            return 0;
        }
        topo = *(q.begin());
        if( get<0>(topo) == 0) {
            tie(x, y, z) = topo;
            q.erase(q.begin());
            nd = z;
        }
        if( nd != -1) {
            cout << 2 << " " << st + 1 << " " << nd + 1<< endl;
            active[st] = active[nd] = 0;
            update(st);
            update(nd);
        }
        else {
            active[st] = 0;
            cout << 1 << " " << st + 1 << endl;
            update(st);
        }
    }
    return 0;
}

