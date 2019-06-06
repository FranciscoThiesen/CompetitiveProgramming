#include <bits/stdc++.h>

using namespace std;

// Debugging macros 
#define TRACE(x) x
#define WATCH(x) TRACE( cout << #x" = " << x << endl)
#define PRINT(x) TRACE(printf(x))
#define WATCHR(a, b) TRACE( for(auto c = a; c != b;) cout << *(c++) << " "; cout << endl)
#define WATCHC(V) TRACE({cout << #V" = "; WATCHR(V.begin(), V.end()); } )
// End of Debugging macros 

// Macros for faster typing
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) (int) (v).size()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define pb push_back

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// End of macros for faster typing

constexpr int inf = 0x3f3f3f3f;
constexpr ll MOD = 1000000007LL;
constexpr double tol = 1e-8;

inline ll powmod( ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1) {
        if(b&1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(0);cin.tie(NULL);
    int t;
    cin >> t;
    while( t-- ) {
        int x;
        cin >> x;
        vector<int> v(x);
        for(int& _ : v) cin >> _;
        array<int, 3> count = {0, 0, 0};
        for(const auto& e : v) {
            if( e < 0 ) count[0]++;
            else if( e == 0) count[1]++;
            else count[2]++;
        }
        cout << max( count[2], count[0] ) + count[1] << " ";
        int t2 = max( count[2], max( count[1], count[0] ) );
        if( count[1] ) t2 = 1;
        for(int i = 0; i < 3; ++i) {
            if( count[i] ) {
                t2 = min(t2, count[i]);
            }
        }
        cout << t2 << endl;
    }
    return 0;
}

