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
#define debug(x) if(debug) x
using vi  = vector<int>;
using ll  = long long;
using pii = pair<int, int>;
using vll = vector<ll>;
using pll = pair<ll, ll>;

constexpr int inf = 0x3f3f3f3f;
constexpr ll  mod = 1000000007;
bool debug = true;
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
ll somaGeral[ms];
int quantidadeCorrente[ms];
long long somaCorrentePorDisciplina[ms];

int main() 
{
    buff();
    int n, m;
    cin >> n >> m;
    vector< pair<int, int> > s;
    for(int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        s.emplace_back(-b, a - 1);
    }
   
    sort( all(s) );
    for(const auto& dupla : s)
    {
        int skill = dupla.second;
        int talento = - dupla.first;
        somaCorrentePorDisciplina[ skill ] += 1LL * talento;
    
        quantidadeCorrente[ skill ] += 1;
        
        if( somaCorrentePorDisciplina[ skill ] > 0LL )
        {
            somaGeral[ quantidadeCorrente[skill] ] += somaCorrentePorDisciplina[skill];
        }
    }
    long long best = 0;
    for(int i = 1; i <= n; ++i) best = max( best, somaGeral[i] );
    cout << best << endl;
    return 0;
}

