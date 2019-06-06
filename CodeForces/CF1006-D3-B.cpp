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

constexpr int ms = 2010;


int good[ms];

int main() {
    int n, k;
    buff();
    cin >> n >> k;
    vector<int> p(n);
    set< pair<int, int> > ord;
    rep(i, 0, n)
    {
        cin >> p[i];
        ord.emplace( -p[i], i );
    }
    long long fuck = 0;
    for(int i = 0; i < k; ++i)
    {
        auto it = *(ord.begin() ) ;
        ord.erase(ord.begin() );
        good[ it.second ] = 1;
        fuck -= ( it.first );
    }
    good[n] = 1;
    vector< pair<int, bool > > miau;  
    int cur = 0;
    bool hasGood = false;
    for(int i = 0; i < n + 1; ++i)
    {
        if( good[i] )
        {
            miau.emplace_back(cur, hasGood);
            cur = 1;
            hasGood = true;
        }
        else ++cur;
    }
    if( miau[0].second == false )
    {
        miau[1].first += miau[0].first;
    }
    vi ans;
    for(auto& par : miau) if(par.second == true) ans.push_back(par.first);
    
    cout << fuck << endl;
    for(const auto& v : ans) cout << v << " ";
    cout << endl;
    return 0;
}