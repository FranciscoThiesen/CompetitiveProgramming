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
    while(t--) {
        int n;
        cin >> n;
        unordered_map<int, int> memo;
        for(int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            int x = 0;
            for(const char& c : s) {
                if( c == 'a' ) x |= 1;
                else if( c == 'e' ) x |= 2;
                else if( c == 'i' ) x |= 4;
                else if( c == 'o' ) x |= 8;
                else if( c == 'u' ) x |= 16;
            }
            memo[x]++;
        }
        constexpr int MAGIC = 31;
        long long ans = 0;

        for(const auto& v : memo ) {
            for(const auto& u : memo ) {
                if( v.first <= u.first && (v.first | u.first ) == MAGIC ) {
                    if( v.first == u.first ) {
                        long long sum = ( (1LL + v.second - 1LL) * (v.second - 1) )  / 2LL;
                        ans += sum;
                    }
                    else ans += 1LL * v.second * u.second; 
                }        
            }
        }
        cout << ans << endl; 
    }
    return 0;
}

