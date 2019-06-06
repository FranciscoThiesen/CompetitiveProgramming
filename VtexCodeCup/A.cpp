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
    int n;
    cin >> n;
    vector< pair<int, int> > arr;
    vector< pair<int, int> > fuck;
    rep(i, 0, n) {
        int a, b;
        cin >> a >> b;
        fuck.emplace_back(a, b);
        arr.emplace_back(a, 0);
        arr.emplace_back(b, 1);
    }
    sort( all(arr) );
    int ans = 0;
    int last_turned = 0;
    // try all-values
    int lo = 0, hi = 40000;
    while( lo < hi ) {
        int mid = (lo + hi) / 2;
        vector<int> freq(40001, 0);
        vector<int> occ(40001, 0);
        for(const auto& v : fuck) {
            occ[v.first]++;
            occ[v.second]--;
            freq[v.first]++;
            if( v.first + mid <= 40000 ) freq[v.first + mid]--;
        }
        for(int i = 1; i < 40001; ++i) {
            freq[i] += freq[i - 1];
            occ[i] += occ[i - 1];
        }
        
        bool good = true;
        for(int i = 0; i < 40001; ++i) {
            if(occ[i] > 0 && freq[i] == 0) {
                good = false;
                break;
            }
        }
        if( good ) hi = mid;
        else lo = mid + 1;
    }

    cout << lo << endl;
    return 0;
}

