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
#define gcd __gcd
using vi  = vector<int>;
using ll  = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vvi = vector<vi>;

constexpr ll mod = 1000000007;
constexpr int inf = 0x3f3f3f3f;

ll pot2[551];
inline ll lcm(ll a, ll b) { return ( (a / gcd(a, b) ) * b); }
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

map<int, ll> fatCache;
inline ll fat(ll n)
{
    if(fatCache[n] != 0) return fatCache[n]; 
    if(n <= 1) return fatCache[n] = 1;
    return fatCache[n] = ( ( n * fat(n - 1) ) % mod);
}

map< pii, vector< vector< pll> > > genCache;
inline vector< vector< pll > > gen_vars( int n, int lim ) {
    vector< vector< pll > > sol;
    if(n > 0) {
        if( !genCache[ {n, lim} ].empty() ) return genCache[{n, lim}];
        for(int x = lim; x > 0; --x) {
            if(x == 1) sol.push_back( { {1, n} } );
            else {
                for(int y = n / x; y > 0; --y) {
                    auto recurse = gen_vars(n - x * y, x - 1);
                    if( sz(recurse) == 0) sol.push_back( { {x, y} } );
                    for( const auto& elem : recurse) {
                        vector< pll > lista;
                        lista.emplace_back(x, y);
                        for(const auto& R : elem) lista.emplace_back( R );
                        sol.push_back( lista );
                    }
                }
            }
        }
    }
    genCache[ {n, lim} ] = sol;
    return sol;
}

ll coeff( vector< pll >& fuck ) {
    ll val = 1LL;
    for( auto&[x, y] : fuck ) {
        ll prod = fat(y);
        ll pot = powmod(x, y);
        prod = (prod * pot) % mod;
        val = (val * prod) % mod;
    }
    return powmod(val, mod - 2);
}

map<int, vector<pair<ll, vector<pll> > > > cycleCache;
inline vector<pair<ll, vector<pll> > > cycle_index( int n) {
    if( !cycleCache[n].empty() ) return cycleCache[n];
    vector< pair< long long, vector< pll > > > ret;
    auto X = gen_vars(n, n);
    for(auto& term : X) {
        ret.emplace_back( coeff(term), term );
    }
    return cycleCache[n] = ret;
}


inline vector< pll > combine( vector<pll>& termA, vector<pll>& termB) {
    vector< pll > combined;
    for( auto&[ len_a, freq_a ] : termA ) {
        for( auto&[ len_b, freq_b] : termB ) {
            ll LCM = lcm( len_a, len_b );
            ll fi = len_a * freq_a;
            ll se = len_b * freq_b;
            fi %= mod;
            se %= mod;
            ll invMd = powmod(LCM, mod - 2);
            fi = (fi * se) % mod;
            fi = (fi * invMd) % mod;
            combined.emplace_back( LCM, fi);
        }
    }
    return combined;
}

inline long long answer( int w, int h )
{
    ll res = 0LL;
    auto C_cols = cycle_index(w);
    auto C_rows = cycle_index(h);
    for( auto&[C_coeff, C_cycle] : C_cols ) {
        for( auto&[ R_coeff, R_cycle] : C_rows) {
            long long coeff = (C_coeff * R_coeff) % mod;
            auto cycle = combine(C_cycle, R_cycle);
            long long val = 1;
            for( auto&[_, power] : cycle ) {
                val = (val * powmod(2, power) ) % mod;
            }
            long long inc = (coeff * val) % mod;
            res  = (res + inc) % mod;
        }
    }
    return res;
}

int main() {
    ofstream out("vamo2.txt");
    out << "{";
    for(int i = 100; i <= 550; ++i)
    {
        for(int j = 1; j <= i; ++j)
        {
            if(i * j > 550) break;
            out << "( " << i << "," << j << "," << answer(i, j) << " ) "<< ",";
            cerr << i << " " << j << " " << " done! " << endl;
        }
    }
    out << "}";
    return 0;
}

