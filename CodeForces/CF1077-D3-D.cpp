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

set<pii> cand;
int n, k;
vector<int> ans;
inline bool can(const int qnt)
{
    auto localCand = cand;
    vi tenta;
    rep(i, 0, k) 
    {
        auto it = *( localCand.begin() );
        localCand.erase(localCand.begin() );
        int av = - it.first;
        if(av < qnt) return false;
        else{
            int good = av - qnt;
            tenta.pb(it.second);
            localCand.emplace( - good, it.second);
        }
    }
    ans = tenta;
    return true;
}


int main() {
    buff();
    cin >> n >> k;
    map<int, int> freq;
    vi v(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> v[i];
        freq[v[i]]++;
    }
    for(const auto& v : freq) cand.emplace( -v.second, v.first);
    int lo = 0, hi = n / k;
    while(lo < hi)
    {
        int mid = (lo + hi + 1) >> 1;
        if( can(mid) ) lo = mid;
        else hi = mid - 1;
    }
    for(const int& x : ans) cout << x << " ";
    cout << endl;
    return 0;
    
}
