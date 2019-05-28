#include <bits/stdc++.h>

using namespace std;
#define all(v) (v).begin(), (v).end()
#define sz(v) (int) (v).size()

using ll = long long;
using pll = pair<ll, ll>;

constexpr ll MOD = 1000000007LL;

inline ll powmod(ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod;
    for(;b;b>>=1) {
        if(b&1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}

inline ll inv(ll a, ll mod = MOD) { return powmod(a, mod - 2, mod); }

vector<pll> factorize(ll n) {
    
    vector<pll> factors;
    
    for(ll i = 2; i * i <= n; ++i) {
        if(n % i == 0) {
            ll c = 0;
            while( n % i == 0) {
                n /= i;
                ++c;
            }
            factors.emplace_back(i, c);
        }
    }
    
    if( n > 1 ) factors.emplace_back( (n % MOD), 1);
    
    return factors;
}


int main() {
    
    ios::sync_with_stdio(0); cin.tie(0);
    ll n; int k;
    cin >> n >> k;

    long long ans = 1LL;

    auto F = factorize( n );

    vector<long long> invMod(64, 0LL);
    for(int i = 1; i < 64; ++i) invMod[i] = inv(i);

    auto calc = [&] ( const pll& factor ) {
        vector< vector<long long> > DP(k + 1, vector<long long>( factor.second + 1, 0LL));
        DP[0][factor.second] = 1LL;

        for(int i = 1; i <= k; ++i) {
            for(int pot = 0; pot <= factor.second; ++pot) {
                DP[i][pot] = 0LL;
                for(int prev = pot; prev <= factor.second; ++prev) {
                    long long inc = ( DP[i - 1][ prev ] * invMod[prev + 1] ) % MOD;
                    DP[i][pot] = ( DP[i][pot] + inc ) % MOD;
                }
            }
        }
  			
        long long value = 1LL;
        long long expectedValue = 0;
    
        for(int pot = 0; pot <= factor.second; ++pot) {
            long long contribute = ( value * DP[k][pot] ) % MOD;
            expectedValue = (expectedValue + contribute) % MOD;
            value = ( value * factor.first) % MOD;
        }
        ans = (ans * expectedValue) % MOD;
    };
    
    for(const auto& X : F) calc(X);
    
    cout << ans << endl;
    
    return 0;
}
