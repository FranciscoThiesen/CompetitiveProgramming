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
    vector< tuple<int, int, int> > boxes;
    rep(i,0,n) {
        int a, b, c;
        cin >> a >> b >> c;
        vector<int> v = {a, b, c};
        sort(all(v));
        boxes.emplace_back(v[2],v[1],v[0]);
    }
    sort( all(boxes), [&] (const tuple<int, int, int>& A, const tuple<int, int, int>& B) {
        if( get<0>(A) != get<0>(B) ) return get<0>(A) < get<0>(B);
        if( get<1>(A) != get<1>(B) ) return get<1>(A) < get<1>(B);
        if( get<2>(A) != get<2>(B) ) return get<2>(B) < get<2>(B);
    });
    auto fit = [&] (const tuple<int, int, int>& A, const tuple<int, int, int>& B) {
        int xA = get<0>(A), yA = get<1>(A), zA = get<2>(A);
        int xB = get<0>(B), yB = get<1>(B), zB = get<2>(B);
        return ( (xA < xB && yA < yB) && zA < zB ) ? true : false;
    };
    for(int i = 1; i < n; ++i) {
        if( fit(boxes[i - 1], boxes[i] ) == false ) {
            cout << "N" << endl;
            return 0;
        } 
    }
    cout << "S" << endl;

    return 0;
}

