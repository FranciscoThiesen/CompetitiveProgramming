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
constexpr ll  mod = 111000000007LL;

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

int main() 
{
    buff();
    int t;
    cin >> t;
    while( t-- )
    {
        long long n, x, y, d;
        cin >> n >> x >> y >> d;
        long long diff = max(x - y, y - x);
        if( diff % d == 0) 
        {
            cout << diff / d << endl;
        }
        else
        {
            long long dFim = n - y;
            long long dInicio = y - 1;
            long long ateFim = (n - x) / d + !!( ( n - x ) % d);
            long long ateInicio = (x - 1ll ) / d + !!( (x - 1LL ) % d);
            long long best1 = mod, best2 = mod;

            if( dFim % d == 0LL ) best1 = ateFim + dFim / d;
            if( dInicio % d == 0LL ) best2 = ateInicio + dInicio / d;
            if( best1 == mod && best2 == mod)
            {
                cout << -1 << endl;
            }
            else cout << min(best1, best2 ) << endl;
        }
    }
    return 0;
}

