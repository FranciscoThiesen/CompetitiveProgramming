#include <bits/stdc++.h>

using namespace std;

// Debugging macros 
#define TRACE(x) x
#define WATCH(x) TRACE( cout << #x" = " << x << endl)
#define PRINT(x) TRACE(printf(x))
#define WATCHR(a, b) TRACE( for(auto c = a; c != b;) cout << *(c++) << " "; cout << endl)
#define WATCHC(V) TRACE({cout << #V" = "; WATCHR(V.begin(), V.end()); } )
// End of Debugging macros 

// Macros for faster typing
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) (int) (v).size()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define pb push_back

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
// End of macros for faster typing

constexpr int inf = 0x3f3f3f3f;
constexpr ll MOD = 1000000007LL;
constexpr double tol = 1e-8;

inline ll powmod( ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1) {
        if(b&1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
constexpr int ms = 1010;

char mat[ms][ms];
int f[ms][ms]; // intermediate state = -1
int seen[ms][ms];
unordered_map<char, pii> delta;
int n, m;

pii add_pairs(pii& a, pii& b) {
    return {a.first + b.first, a.second + b.second};
}

inline bool valid( pii pos ) { return ( pos.first >= 0 && pos.first < n && pos.second >= 0 && pos.second < m); }

void visit( pii pos ) {
    if(f[pos.first][pos.second]) return;
    vector< pii > proc;
    seen[pos.first][pos.second] = 1; 
    proc.emplace_back( pos );
    pair<int, int> cur = pos;
    bool out_of_bounds = false;
    bool found_cycle = false;
    bool just_stopped = false;
    while(true) {
        pii next_pos = add_pairs(cur, delta[mat[cur.first][cur.second]]);
        if( valid(next_pos) == false ) {
            int cur_value = 1;
            out_of_bounds = true;
            for(auto it = proc.rbegin(); it != proc.rend(); ++it) {
                auto P = *it;
                seen[P.first][P.second] = 2;
                f[P.first][P.second] = cur_value++;
            }
            return;
        }
        else {
            if(seen[next_pos.first][next_pos.second] == 2) {
                int cur_value = f[next_pos.first][next_pos.second] + 1;
                out_of_bounds = true;
                for(auto it = proc.rbegin(); it != proc.rend(); ++it) {
                    auto P = *it;
                    seen[P.first][P.second] = 2;
                    f[P.first][P.second] = cur_value++;
                }
                return;
            }
            else if( seen[next_pos.first][next_pos.second] == 1) {
                // tricky case, found cycle
                int c_size = 0;
                bool cycle_end = false;
                vector< pii > in_cycle;
                vector< pii > out_of_cycle;
                for(auto it = proc.rbegin(); it != proc.rend(); ++it) {
                    auto P = *it;
                    if( cycle_end == false) {
                        in_cycle.push_back( P );
                    }
                    else {
                        out_of_cycle.push_back(P);
                    }
                    if( P == next_pos ) cycle_end = true;
                }
                c_size = sz( in_cycle );
                for(const auto& P : in_cycle ) {
                    seen[P.first][P.second] = 2;
                    f[P.first][P.second] = c_size;
                }
                int inc = 1;
                for(const auto& P : out_of_cycle ) {
                    seen[P.first][P.second] = 2;
                    f[P.first][P.second] = c_size + inc;
                    inc++;
                }
                return;
            }
            else
            {
                seen[next_pos.first][next_pos.second] = 1;
                proc.emplace_back( next_pos );
                cur = next_pos;
            }
        }
    }
}

int main() 
{
    ios::sync_with_stdio(0);cin.tie(NULL);
    cin >> n >> m;
    delta['N'] = {-1, 0};
    delta['S'] = {1, 0};
    delta['W'] = {0, -1};
    delta['E'] = {0, 1};
    
    rep(i, 0, n) {
        rep(j, 0, m) {
            cin >> mat[i][j];
        }
    }

    rep(i, 0, n) {
        rep(j, 0, m) {
            if( seen[i][j] == 0 ) {
                visit( make_pair(i, j) );
            }
        }
    }

    long long soma = 0;
    rep(i,0,n) rep(j,0,m) soma += f[i][j];
    
    cout << soma << endl;
    return 0;
}

