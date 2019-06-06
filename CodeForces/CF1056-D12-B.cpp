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
bool debug = true;
int main() 
{
    buff();
    long long n, m;
    cin >> n >> m;
    if(m == 1)
    {
        cout << n * n << endl;
        return 0;
    }
    unordered_map<long long, long long> calcMod;
    long long each = n / m;
    for(long long i = 0; i < m; ++i) calcMod[ (i * i) % m] += each;
    long long resta = n % m;
    for(long long i = 1; i <= m; ++i)
    {
        if(resta == 0LL) break;
        --resta;
        calcMod[ (i * i) % m] += 1LL;
    }
    long long ans = 0;
    for(long long i = 0; i < m; ++i)
    {
        long long complemento = (m - i) % m;
        ans += ( calcMod[i] * calcMod[complemento] );
    }
    cout << ans << endl;
    return 0;
}

