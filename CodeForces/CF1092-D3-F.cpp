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

constexpr int inf = 0x3f3f3f3f;
constexpr double EPS = 1e-8;
constexpr ll  MOD = 1000000007LL;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// online for debugging pairs with modern cpp ( >= 17 )
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

constexpr int ms = 2 * 1e5 + 13;

vector<long long> soma(ms, 0LL);
vector<long long> resp(ms, 0LL);
vector<long long> val(ms, 0LL);
vector< vector<int> > g(ms);
long long ans = 0LL;
long long S = 0LL;

void dfs(int x, int parent = -1, int h = 0) {
    soma[x] = val[x];
    resp[0] += h * 1ll * val[x];
    for(const int& v : g[x] ) {
        if(v != parent) {
            dfs(v, x, h + 1);
            soma[x] += soma[v];
        }
    }
}

void doit(int x, int parent = -1) {
    for(const int& v : g[x]) {
        if(v != parent) {
            resp[v] = resp[x] - soma[v];
            resp[v] += ( S - soma[v] );
            doit(v, x);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(NULL);
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> val[i];
        S += val[i];
    }
    for(int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        --x;--y;
        g[x].pb(y);
        g[y].pb(x);
    }
    
    dfs(0);
    doit(0);
    
    ans = accumulate(all(resp), 0LL,[&]( ll a, ll b) { return max(a, b); } );
    
    cout << ans << endl;
    
    return 0;
}

