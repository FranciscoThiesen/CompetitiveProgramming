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

constexpr ll ms = 1e5 + 13;
vll primes;
deque<bool> mrk(ms, true);
vector< int > squeeze(ms, 0);

inline void sieve()
{
    iota( all(squeeze), 0 );
    mrk[0] = mrk[1] = false;
    for(int i = 2; i < ms; ++i)
    {
        if(mrk[i])
        {
            primes.pb(i);
            for(int j = i + i; j < ms; j += i)
            {
                squeeze[j] = min(squeeze[j], i);
                mrk[j] = false;
            }
        }
    }
}

bool checkPrime(long long n)
{
    if(n < 2) return false;
    for(ll i = 2; i * i <= n; ++i) if(n % i == 0) return false;
    return true;
}

inline long long findSmallestDiv(long long n)
{
    if( checkPrime(n) ) return n;
    for(const ll& p : primes)
    {
        if(n % p == 0) return p;
    }
    return -1;
}

int main() 
{
    buff();
    sieve();
    long long n;
    cin >> n;
    long long c = 0;
    vector< long long > freq;
    while( n > 0 )
    {
        long long d = findSmallestDiv(n);
        if(d == 2) 
        {

            c += n / d;
            n -= (d * ( n / d) );
        }
        else
        {
            ++c;
            n -= d;
        }
    }
    cout << c << endl;
    return 0;
}
