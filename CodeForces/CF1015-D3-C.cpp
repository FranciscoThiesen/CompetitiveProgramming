#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define mset(x, v) memset((x), (v), sizeof (x) )
#define buff() ios::sync_with_stdio(0);cin.tie(0)
#define sz(x) ( (int) (x).size() )

using vi  = vector<int>;
using ll  = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vvi = vector<vi>;

constexpr int mod = 1000000007;
constexpr int inf = 0x3f3f3f3f;

inline ll powmod(ll a, ll b) {
    ll res = 1;
    a %= mod;
    assert(b >= 0);
    for(;b;b>>=1) {
        if(b&1) res = (res * a) % mod;
        a = (a*a) % mod;
    }
    return res;
}

int main() {
    ll n, m;
    buff();
    cin >> n >> m;
    vector<pll> S(n);
    rep(i,0,n) cin >> S[i].fi >> S[i].se;
    sort(all(S), [] (const pll& A, const pll& B) { return ( (A.se - A.fi) < (B.se - B.fi) ); } );
    long long acc = 0;
    rep(i,0,n) acc += S[i].fi;
    int ans = 0;
    for(const pll& dupla : S)
    {
        if(acc <= m) break;
        else {
            acc -= (dupla.first - dupla.second);
            ++ans;
        }   
    }
    if(acc <= m) cout << ans << endl;
    else cout << -1 << endl;
    return 0;
}