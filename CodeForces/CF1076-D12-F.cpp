#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define repit(i, x) for( auto (i) = begin(x); i != end(x); ++i)
#define buff() ios::sync_with_stdio(0);cin.tie(0)
#define sz(x) ( (int) (x).size() )

using vi  = vector<int>;
using ll  = long long;
using pii = pair<int, int>;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using ld  = long double;

constexpr int inf = 0x3f3f3f3f;

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
constexpr int ms = 3 * 1e5 + 13;

int dp[ms][2], days[ms][2];

int main() 
{
    buff();
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) cin >> days[i][0];
    for(int i = 1; i <= n; ++i) cin >> days[i][1];
    
    auto check = [&] (int day, int ans, int digit)
    {
        if( ans > days[day][value]) return false;
        int good[2];
        good[0] = days[day][0];
        good[1] = days[day][1];
        good[ digit ] -= ans;
        
        if(good[0] == inf || good[1] == inf) return false;
        
        bool ok = false;
        for(int initialDigit = 0; initialDigit < 2; ++initialDigit)
        {
            for(int previousEnd = 0; previousEnd < 2; ++previousEnd)
            {
                if(initialDigit == previousEnd)
                {
                    
                }
                else
                {

                }
            }
        }

    };

    for(int i = 1; i <= n; ++i)
    {
        for(int val = 0; val < 2; ++val)
        {
            int lo = 1, hi = days[i][val];
            while(lo < hi)
            {
                int mid = (lo + hi) / 2;
                
            }
        }
    }



}

