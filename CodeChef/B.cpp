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

int a, b, x;
pair<bool, vi> good(int st)
{
    vi ans(a + b, 0);
    ans[0] = st;
    int left0 = a - (st == 0);
    int left1 = b - (st == 1);
    int leftChange = x;
    for(int i = 1; i < a + b; ++i)
    {
        if( leftChange > 1) {
            if(ans[i - 1] == 0) {
                if( left1 ) { ans[i] = 1; left1--; leftChange--; }
                else { ans[i] = 0; left0--; }
            }
            else if(ans[i - 1] == 1) {
                if(left0) { ans[i] = 0; left0--; leftChange--; }
                else { ans[i] = 1; left1--; }
            }
        }
        else {
            if(ans[i - 1] == 0) {
                if(left0) { ans[i] = 0; left0--; }
                else { ans[i] = 1; left1--; }
            }
            else {
                if( left1 ) { ans[i] = 1; left1--; }
                else { ans[i] = 0; left0--; }
            }
        }
    }
    int c0 = 0, c1 = 0, ch = 0;
    rep(i, 0, a + b) {
        if(i) if( ans[i] != ans[i - 1]) ch++;
        c0 += (ans[i] == 0);
        c1 += (ans[i] == 1);
    }
    if( c0 == a && (c1 == b && ch == x) ) return make_pair(true, ans);
    return make_pair( false, ans);
}


int main()
{
	ios::sync_with_stdio(0); cin.tie(NULL);
    cin >> a >> b >> x;
    for(int i = 0; i < 2; ++i)
    {
        auto res = good(i);
        if( res.first == true)
        {
            for(const int& v : res.second) cout << v;
            cout << endl;
            return 0;
        }
    }
    return 0;
}

