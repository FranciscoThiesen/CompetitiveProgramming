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
    int N, c;
    cin >> N >> c;
    int sqrtVal = 388;
    int sqrtSqrtVal = 20;
    int lo = 1, hi = N, result;
    int attempt = lo;
    while( attempt < N)
    {
        lo = attempt;
        attempt = min(N, (attempt + sqrtVal) );
        if( attempt == N )
        {
            hi = attempt;
            break;
        }
        cout << "1 " << attempt << endl;
        cin >> result;
        if( result == 1) 
        {
            hi = attempt;
            cout << 2 << endl;
            break;
        }
    }
    attempt = lo;
    if(lo == hi)
    {
        cout << "3 " << lo << endl;
        return 0;
    }
    while( attempt < hi )
    {
        lo = attempt;
        attempt = min( hi, attempt + sqrtSqrtVal );
        if( attempt == hi)
        {
            hi = attempt;
            break;
        }
        cout << "1 " << attempt << endl;
        cin >> result;
        if( result == 1) 
        {
            hi = attempt;
            cout << 2 << endl;
            break;
        }
    }
    for(int i = lo; i < hi; ++i)
    {
        cout << "1 " << i << endl;
        cin >> result;
        if( result == 1)
        {
            cout << 2 << endl;
            cout << "3 " << i << endl;
            return 0;
        }
    }
    cout << "3 " << hi << endl;
    return 0;
}

