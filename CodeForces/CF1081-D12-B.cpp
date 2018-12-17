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

int main()
{
    ios::sync_with_stdio(0);cin.tie(NULL);
    int n;
    cin >> n;
    map<int, vi> freq;
    map<int, int> pinta;
    int cur = 0;
    vi ans(n);
    vi a(n);
    rep(i,0,n) {
        cin >> a[i];
        freq[a[i]].pb(i);
    }
    for(const auto& v : freq)
    {
        int diff = n - sz(v.se);
        int totalV = sz(v.se);
        if( v.first < diff )
        {
            cout << "Impossible" << endl;
            return 0;
        }
        else if( v.first > diff) {
            int good = -1;
            rep(i, 2, totalV + 1) {
                if( totalV % i == 0 ) {
                    int diferente = totalV - totalV / i;
                    if( diff + diferente == v.first ) {
                        good = totalV / i;
                        break;
                    }
                }
            }
            if( good == -1) {
                cout << "Impossible" << endl;
                return 0;
            }
            else
            {
                for(int i = 0; i < totalV; ++i)
                {
                    if( i % good == 0) ++cur;
                    ans[ v.second[i] ] = cur;
                }
            }
        }
        else {
            ++cur;
            for(const int& x : v.second) ans[x] = cur;
        }
    }
    if( cur > n) cout << "Impossible" << endl;
    else {
        cout << "Possible" << endl;
        for(auto& x : ans) cout << x << " ";
        cout << endl;
    }
    return 0;
}

