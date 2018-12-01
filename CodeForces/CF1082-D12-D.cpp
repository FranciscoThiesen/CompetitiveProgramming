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
#define debug(x) if( debug) x
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
constexpr int ms = 510;
int n;
vector<int> g[ms];

pair<int, int> encontraMaisDistante( int root )
{
    vector<int> dist(n, mod);
    dist[root] = 0;
    queue<int> vizi;
    vizi.push( root );
    while( !vizi.empty() )
    {
        int topo = vizi.front();
        vizi.pop();
        for(const int& v : g[ topo ])
        {
            if( dist[ v ] == mod)
            {
                dist[v] = dist[topo] + 1;
                vizi.push( v );
            }
        }
    }
    int maisLonge = 0;
    for(int i = 0; i < n; ++i)
    {
        if( dist[i] > dist[maisLonge] ) maisLonge = i;
    }
    return make_pair( maisLonge, dist[maisLonge] );
}

int retornaDiametro()
{
    auto x = encontraMaisDistante(0);
    auto z = encontraMaisDistante( x.first );
    return z.second;
}

int distFromRoot[ms];
int rem[ms];
int main() 
{
    buff();
    cin >> n;
    set< pair<int, int > > keru;
    set< pair<int, int> > keruReserva;
    vector<pair<int, int> > nudes;
    for(int i = 0; i < n; ++i)
    {
        int deg;
        cin >> deg;
        nudes.emplace_back( - deg, i);
        rem[ i ] = deg;
    }
    sort(all(nudes));
    for(int i = 0; i < n; ++i)
    {
        if( i == 0) keru.emplace( 0, nudes[i].second ); // vai ser -dist, e indice
        else
        {
            if( keru.empty() && keruReserva.empty() ) {
                cout << "NO" << endl;
                return 0;
            }
            else if( !keru.empty() ) {
                auto it = *(keru.begin());
                keru.erase( keru.begin() );
                int distCenter = -(it.first);
                int nodeIndex  = it.second;
                rem[ nodeIndex ] -= 1;
                rem[ nudes[i].second ] -= 1;
                g[nodeIndex].push_back(nudes[i].second);
                g[nudes[i].second].push_back(nodeIndex);
                if( rem[ nudes[i].second ] > 0) keru.emplace( it.first - 1, nudes[i].second );
                if( rem[nodeIndex] > 0) keruReserva.emplace(distCenter, nodeIndex ) ;
            }
            else {
                auto it = *(keruReserva.begin());
                keruReserva.erase(keruReserva.begin( ));
                int distCenter = it.first;
                int nodeIndex  = it.second;
                rem[ nodeIndex ] -= 1;
                rem[ nudes[i].second ] -= 1;
                g[nodeIndex].push_back(nudes[i].second);
                g[nudes[i].second].push_back(nodeIndex);
                if( rem[ nudes[i].second ] > 0) keru.emplace( - distCenter - 1, nudes[i].second);
                if( rem[nodeIndex] > 0) keruReserva.emplace( distCenter, nodeIndex );
            }
        }
    }
    vector< pair<int, int> > arestas;
    for(int i = 0; i < n; ++i) for(const auto& v : g[i]) arestas.emplace_back( min( i, v), max(i, v) );
    sort(all(arestas));
    arestas.erase( unique( all(arestas) ), arestas.end() );
    int d = retornaDiametro();
    cout << "YES " << d << endl;
    cout << sz(arestas) << endl;
    for(const auto& v : arestas ) cout << v.first + 1 << " " << v.second + 1<< endl;


    return 0;
}

