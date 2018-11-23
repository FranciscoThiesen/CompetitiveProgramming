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

constexpr int ms = 2 * 1e5 + 12;

set<int> g[ms];
int visitTime[ms];
int inverseVisitTime[ms];
int exitTime[ms];
int globalTime = 0;

void dfs(int root)
{
    visitTime[root] = globalTime++;
    for(const int& v : g[root]) dfs( v );
    exitTime[root] = globalTime - 1;
    for(const int& v : g[root]) exitTime[root] = max( exitTime[root], exitTime[v] );
}



int main() {
    buff();
    int n, q;
    cin >> n >> q;
    for(int i = 1; i < n; ++i)
    {
        int pai;
        cin >> pai;
        --pai;
        g[pai].insert( i );
    }
    dfs(0);
    for(int i = 0; i < n; ++i) inverseVisitTime[ visitTime[i] ] = i; 
    rep(i, 0, q)
    {
        int x, u;
        cin >> x >> u;
        --x;
        int val = visitTime[x];
        int keru = val + u - 1;
        if(keru >= visitTime[x] && keru <= exitTime[ x ])
        {
            cout << inverseVisitTime[ keru ] + 1<< endl;
        }
        else cout << -1 << endl;
        
    }

    return 0;
}