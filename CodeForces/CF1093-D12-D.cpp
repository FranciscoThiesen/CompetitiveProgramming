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
using vvi = vector<vi>;

constexpr int INF = 0x3f3f3f3f;
constexpr int NINF = 0xc0c0c0c0;
constexpr double EPS = 1e-8;
constexpr long long MOD = 998244353LL;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ostream &operator<<(ostream& os, const pair<auto, auto>& p) {
    return os << "(" << p.first << "," << p.second << ")";
}

inline ll powm( ll a, ll b, ll mod = MOD) {
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

inline ll solve(int i, vvi& g, vi& colors)
{
    queue<int> q;
    q.push(i);
    array<int, 2> c = {1LL, 0LL};
    ll ans = 0LL; 
    colors[i] = 0;
    while( !q.empty() ) 
    {
        int top = q.front();
        q.pop();
        for(const int& x : g[top])
        {
            if( colors[x] == colors[top]) return ans;
            if( colors[x] == -1 ) 
            { 
                colors[x] = ( colors[top] ^ 1);
                c[ colors[x] ]++;
                q.push(x); 
            }
        }
    }
    ans = (powm(2LL, c[0]) + powm(2LL, c[1])) % MOD;
    return (ans % MOD);  
}

int main() 
{
    ios::sync_with_stdio(0);cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) 
    {
        int n, m;
        cin >> n >> m;
        vvi g(n);
        rep(i, 0, m) 
        {
            int a, b;
            cin >> a >> b;
            --a;--b;
            g[a].pb(b); g[b].pb(a);
        }
        vi colors(n, -1);
        ll ans = 1LL;
        rep(i, 0, n) if(colors[i] == -1) ans = ( ans * solve(i, g, colors) ) % MOD;
        cout << ans << endl; 
    }
    return 0;
}

