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

constexpr int ms = 3 * 1e5 + 13;
deque<bool> visited(ms, false);
vi g[ms];
vector< vector<pii>  > nodesPerHeight(ms);
int alt[ms];
vector< vector<long long>  > accu(ms);
long long propaga[ms];
long long valor[ms];
vector<pii> entradaSaida(ms, make_pair(0, 0) );
int globalTime = 0;
int n;
int maiorAltura = 0;

inline void dfs(int root, int altura)
{
    visited[root] = true;
    entradaSaida[root].first = globalTime++;
    alt[root] = altura;
    maiorAltura = max(maiorAltura, altura);
    nodesPerHeight[altura].emplace_back(entradaSaida[root].first, root);
    for(const int& v : g[root])
    {
        if(!visited[v])
        {
            dfs(v, altura + 1);
        }
    }
    entradaSaida[root].second = ++globalTime;
}

inline void dfs2(int root, long long desce)
{
    valor[root] += propaga[root] + desce;
    for(const int& v : g[root])
    {
        if(alt[v] == alt[root] + 1)
        {
            dfs2( v, desce + propaga[root] ); 
        }
    }
}

int main() 
{
    buff();
    cin >> n;
    rep(i, 0, n - 1)
    {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(0, 0);
    for(int i = 0; i < ms; ++i)
    {
        if( sz(nodesPerHeight[i]) > 0)
        {
            accu[i].assign( sz(nodesPerHeight[i]) + 2, 0 );
        }
    }
    int q;
    cin >> q;
    rep(i, 0, q)
    {
        int v, d, x;
        cin >> v >> d >> x;
        --v;
        propaga[v] += x;
        
        if(d == 0)
        {
            propaga[v] -= x;
            valor[v] += x;
            continue;
        }
        // hora do show porra
        int alturaMax = alt[v] + d + 1;
        if( alturaMax > maiorAltura) continue;
        else 
        {

            if(nodesPerHeight[alturaMax].empty() == false)
            {
                auto it = lower_bound(all(nodesPerHeight[alturaMax]), make_pair(entradaSaida[v].first, -1) );
                if(it != nodesPerHeight[alturaMax].end() ) 
                {
                    int idx = it - nodesPerHeight[alturaMax].begin();
                    accu[alturaMax][idx] -= x;
                    auto it2 = upper_bound(all(nodesPerHeight[alturaMax]), make_pair( entradaSaida[v].second, -1) );
                    if( it2 != nodesPerHeight[alturaMax].end() )
                    {
                        int idx2 = it2 - nodesPerHeight[alturaMax].begin();
                        accu[alturaMax][idx2] += x;
                    }
                }
            }
        }
    }
    rep(h, 0, maiorAltura + 1)
    {
        for(int i = 0; i < sz(nodesPerHeight[h]); ++i)
        {
            if(i > 0) accu[h][i] += accu[h][i - 1];
            propaga[ nodesPerHeight[h][i].second ] += accu[h][i];
        }
    }
    
    dfs2(0, 0);
    
    for(int i = 0; i < n; ++i)
    {
        cout << valor[i] << " ";
    }
    cout << endl;
}
