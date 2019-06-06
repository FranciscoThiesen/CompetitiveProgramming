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
#define trav(a, x) for(auto& a : x)

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

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

inline ll modPow( ll a, ll b, ll mod = MOD) {
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

int main()
{
	ios::sync_with_stdio(0); cin.tie(NULL);
    int n, d, k;
    cin >> n >> d >> k;
    ++d;
    if(n < d){
        cout << "NO" << endl;
        return 0;
    }
    int totalEdges = 0;
    vector< vector<int> > g(n + 1);
    vector<int> remDeg(n + 1, k); 
    vi maxDepthAllowed(n + 1, k);
    // vamos fazer uma reta com D vertices
    queue<int> good;
    for(int i = 1; i < d; ++i)
    {
        TRACE( cout << "fazendo aresta " << i << " " << i + 1 << endl; ) 
        g[i].push_back(i + 1);
        remDeg[i]--;
        remDeg[i + 1]--;
        if( remDeg[i] < 0 || remDeg[i + 1] < 0) {
            cout << "NO" << endl;
            return 0;
        }
        maxDepthAllowed[i] = min( i - 1, d - i);
        totalEdges++;
        if( remDeg[i] > 0 && maxDepthAllowed[i] > 0) good.push(i);
    }
    maxDepthAllowed[d] = 0;
    // Falta ligar os vertices de D + 1 ate N + 1, se existir
    for(int i = d + 1; i <= n; ++i)
    {
        // temos que achar alguem livre
        TRACE( cout << "entramos aqui" << endl; )
        if( good.empty() )
        {
            cout << "NO" << endl;
            return 0;
        }
        int res = good.front();
        TRACE( cout << "topo = " << res << endl; )
        good.pop();
        g[ res ].push_back( i );
        maxDepthAllowed[i] = maxDepthAllowed[ res ] - 1;
        remDeg[ res ]--;
        remDeg[ i ]--;

        if( remDeg[ res ] > 0) good.push(res);
        if( remDeg[ i ] && maxDepthAllowed[i] ) good.push(i);
    }
    cout << "YES" << endl;
    for(int i = 1; i <= n; ++i)
    {
        for(auto& x : g[i])
        {
            cout << i << " " << x << endl;
        }
    }
    return 0;
}

