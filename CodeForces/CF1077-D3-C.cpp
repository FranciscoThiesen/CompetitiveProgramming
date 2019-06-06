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
    int n;
    buff();
    cin >> n;
    vll v(n);
    unordered_map< long long, int> freq;
    for( auto& x : v) cin >> x;
    for( auto& x : v) freq[x]++;
    long long soma = accumulate(all(v), 0ll, [] (ll a, ll b) { return a + b; } );
    vi good;
    for(int i = 0; i < n; ++i)
    {
        ll x = v[i];
        long long rem = soma - x;
        if(rem % 2) continue;
        long long want = rem / 2;
        if(want == x)
        {
            if(freq[want] > 1) good.pb(i + 1); 
        }
        else{
            if(freq[want]) good.pb(i + 1);
        }
    }
    cout << sz(good) << endl;
    for(const int& x : good) cout << x << " ";
    cout << endl;
}