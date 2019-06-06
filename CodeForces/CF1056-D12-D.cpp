#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define buff() ios::sync_with_stdio(0);cin.tie(0)
#define sz(x) ( (int) (x).size() )

using vi  = vector<int>;
using ll  = long long;
using pii = pair<int, int>;
using vll = vector<ll>;
using pll = pair<ll, ll>;

constexpr int inf = 0x3f3f3f3f;
constexpr ll  mod = 1000000007;

inline ll powmod(ll a, ll b) 
{
    ll res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1) 
    {
        if(b&1) res = (res * a) % mod;
        a = (a*a) % mod;
    }
    return res;
}
constexpr int ms = 1e5 + 13;

vector<int> g[ms];
vector<int> price(ms, 0);

void dfs(int x)
{
    if( sz(g[x]) == 0) {
        price[x] = 1;
        return;
    }
    for(const int& k : g[x])
    {
        dfs(k);
        price[x] += price[k];
    }
}

int main() 
{
    buff();
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int> > good;
    for(int i = 0; i < n - 1; ++i)
    {
        int x;
        cin >> x;
        --x;
        g[x].push_back(i + 1);
    }
    dfs(0);
    rep(i, 0, n) good.push( price[i] );
    int curCost = 0;
    for(int i = 1; i <= n; ++i)
    {
        int t = good.top();
        good.pop();
        curCost = max(curCost, t);
        cout << curCost << " ";
    }
    cout << endl;
    return 0;
}

