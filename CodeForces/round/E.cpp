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

constexpr int inf = 0x3f3f3f3f;
constexpr double EPS = 1e-8;
constexpr ll  MOD = 1000000007LL;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// online for debugging pairs with modern cpp ( >= 17 )
/*ostream &operator<<(ostream& os, const pair<auto, auto>& p) {
    return os << "(" << p.first << "," << p.second << ")";
}*/

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

inline bool gallai(vector<int>& v) {
  vector<ll> sum;
  sum.resize(v.size());

  sort(v.begin(), v.end(), greater<int>());
  sum[0] = v[0];
  for (int i = 1; i < v.size(); i++) sum[i] = sum[i-1] + v[i];
  if (sum.back() % 2) return 0;

  for (int k = 1; k < v.size(); k++) {
    int p = lower_bound(v.begin(), v.end(), k, greater<int>()) - v.begin();
    if (p < k) p = k;
    if (sum[k-1] > 1ll*k*(p-1) + sum.back() - sum[p-1]) return 0;
  }
  return 1;
}

int main()
{
    int n;
    scanf("%d", &n);
    int c = 0;
    vi vec(n);
    ll tot = 0;
    for(int& x : vec) scanf("%d", &x); 
    tot = accumulate(all(vec), 0LL, [] (ll a, ll b) { return a + b; } );
    vi cpy;
    int x = 0;
    if( tot & 1LL ) {
        // busca impar
        int st = 1;
        while(st <= n) {
            cpy = vec;
            cpy.pb(st);
            bool ok = gallai(cpy);
            if(ok == true) {
                int lo = st, hi = n;
                if(hi % 2 == 0) --hi;
                while(lo < hi) {
                    int mid = (lo + hi) / 2;
                    if(mid % 2 == 0) {
                        ++mid;
                    }
                    cpy = vec;
                    cpy.pb(mid);
                    bool can = gallai(cpy);
                    if( can ) lo = mid;
                    else hi = mid - 2;
                }
                while(st <= lo) {
                    printf("%d ", st);
                    st += 2;
                    ++c;
                }
                return 0;
            }
            st += 2;
            if(x > 100) goto REV;
        }
    }
    else {
        int st = 0;
        while(st <= n) {
            cpy = vec;
            cpy.pb(st);
            bool ok = gallai(cpy);
            if(ok == true) {
                int lo = st, hi = n;
                if(hi % 2 == 1) --hi;
                while(lo < hi) {
                    int mid = (lo + hi) / 2;
                    if(mid % 2 == 1) {
                        ++mid;
                    }
                    cpy = vec;
                    cpy.pb(mid);
                    bool can = gallai(cpy);
                    if( can ) lo = mid;
                    else hi = mid - 2;
                }
                while(st <= lo) {
                    printf("%d ", st);
                    st += 2;
                    ++c;
                }
                return 0;
            }
            st += 2;
            ++x;
            if(x > 100) goto REV;
        }
    }
REV:
	if( tot & 1LL ) {
        // busca impar
        int st = n;
        if(st%2 == 0) st--;
        while(st >= 0) {
            cpy = vec;
            cpy.pb(st);
            bool ok = gallai(cpy);
            if(ok == true) {
                int lo = 1, hi = st;
                if(hi % 2 == 0) --hi;
                while(lo < hi) {
                    int mid = (lo + hi) / 2;
                    if(mid % 2 == 0) {
                        --mid;
                    }
                    cpy = vec;
                    cpy.pb(mid);
                    bool can = gallai(cpy);
                    if( can ) hi = mid;
                    else lo = mid + 2;
                }
                while(lo <= st) {
                    printf("%d ", st);
                    lo += 2;
                    ++c;
                }
                return 0;
            }
            st -= 2;
        }
    }
    else {
        int st = n;
        if(st%2 == 1) st--;
        while(st >= 0) {
            cpy = vec;
            cpy.pb(st);
            bool ok = gallai(cpy);
            if(ok == true) {
                int lo = 0, hi = st;
                while(lo < hi) {
                    int mid = (lo + hi) / 2;
                    if(mid % 2 == 1) {
                        --mid;
                    }
                    cpy = vec;
                    cpy.pb(mid);
                    bool can = gallai(cpy);
                    if( can ) hi = mid;
                    else lo = mid + 2;
                }
                while(lo <= st) {
                    printf("%d ", st);
                    lo += 2;
                    ++c;
                }
                return 0;
            }
            st -= 2;
        }
    }
    if(c == 0) puts("-1");

    return 0;
}

