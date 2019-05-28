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


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector< pii > ranges;
    vector<int> accumulated(n + 1, 0);
    
    int ans = 0; 
    
    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        ranges.emplace_back( a, b );
        accumulated[a]++;
        accumulated[b + 1]--;
    }
    vector<int> cover[2];
    for(int i = 0; i < n; ++i) {
        if(i > 0) accumulated[i] += accumulated[i - 1];
        if( accumulated[i] == 1) { cover[0].emplace_back(i), cover[1].emplace_back(i); }
        else if( accumulated[i] == 2) cover[1].emplace_back(i);
        if( accumulated[i] > 0 ) ans++; 
    }
    
    int best = 0; 
    for(int i = 0; i < q; ++i) {
        for(int j = i + 1; j < q; ++j) {
            pii a = ranges[i], b = ranges[j];
            if( a > b) swap( a, b);
            if( a.second >= b.first ) {
                // fazer umas contas
                pii intersec = { b.first, a.second };
                pii i1 = {a.first, b.first - 1};
                pii i2 = {a.second + 1, b.second };
            
                int tira = 0;
                auto lastInter = upper_bound( all(cover[1]), a.second );
                auto firstInter = lower_bound( all(cover[1]), b.first );
                
                int idLast = distance( cover[1].begin(), lastInter);
                int idFirst = distance( cover[1].begin(), firstInter);

                tira += max(0, idLast - idFirst );
                
                lastInter = upper_bound( all(cover[0]), b.first - 1);
                firstInter = lower_bound( all(cover[0]), a.first );

                idLast = distance( cover[0].begin(), lastInter);
                idFirst = distance( cover[0].begin(), firstInter);

                tira += max( 0, idLast - idFirst );
            
            
                lastInter = upper_bound( all(cover[0]), b.second );
                firstInter = lower_bound( all(cover[0]), a.second + 1);
                
                idLast = distance( cover[0].begin(), lastInter);
                idFirst = distance( cover[0].begin(), firstInter);
            
                tira += max(0, idLast - idFirst );

                best = max( best, ans - tira ); 
            }
            else {
                int tira = 0;
                auto fst = lower_bound( all(cover[0]), a.first);
                auto lst = upper_bound( all(cover[0]), a.second);
                int idfst = distance( cover[0].begin(), fst);
                int idlst = distance( cover[0].begin(), lst);
                
                tira += max( 0, idlst - idfst );
            
                fst = lower_bound( all(cover[0]), b.first);
                lst = upper_bound( all(cover[0]), b.second);
               
                idfst = distance( cover[0].begin(), fst);
                idlst = distance( cover[0].begin(), lst);
                tira += max( 0, idlst - idfst );

                best = max( best, ans - tira );
            }
        }
    }
    cout << best << endl;
    return 0;
}


