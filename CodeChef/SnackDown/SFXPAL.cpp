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

long long norm( ll a, ll MOD)
{
    a %= MOD;
    if( a < 0) a += MOD;
    return a;
}

/*
inline bool checkPal( vector<int> s) {
    vector<int> t = s;
    reverse(all(t));
    if( s == t ) return true;
    return false;
}

bool good( vector<int> s)
{
    vi res;
    for(int i = 0; i < sz(s); ++i)
    {
        res.push_back( s[ sz(s) - 1 - i] );
        if( sz(res) > 1 && checkPal( res ) ) return false;
    }
    return true;
}

long long brute()
{
    long long count = 0;
    rep(i, 0, 4){
        rep(j, 0, 4){
            rep(k, 0, 4){
                rep(x, 0, 4)
                {
                    rep(z, 0, 4) {
                        vi v = {i, j, k, x, z};
                        if( good( v ) ) ++count;
                    }
                }
            }
        }
    }
    return count;
} */
int main() {
    ll n, s, m;
    buff();
    cin >> n >> s >> m;
    if(n == 1)
    {
        cout << s % m << endl;
        return 0;
    }
    vector< long long > cand( n + 1, 0LL);
    vector< long long > exclusivePal(n + 1, 0ll);
    cand[0] = 1LL;
    cand[1] = (s % m);
    for(int i = 2; i <= n; ++i)
    {
        cand[i] = (cand[i - 1] * s) % m;
    }
    exclusivePal[1] = 0LL;
    exclusivePal[2] = (s % m);
    exclusivePal[3] = (s * (s - 1) ) % m;
    for(int len = 4; len <= n; ++len)
    {
        int mid = (len / 2 + (len % 2) );
        long long tot = cand[mid];  
        for(int exc = 1; exc <= mid; ++exc)
        {
            long long bad = exclusivePal[exc]; 
            bad = ( bad * cand[mid - exc] ) % m;
            tot = norm( tot - bad, m); 
        }
        exclusivePal[len] = tot;
    }
    long long allBad = 0LL;
    for(int len = 2; len <= n; ++len)
    {
        long long inc = ( exclusivePal[len] * cand[ n - len ] ) % m;
        allBad = (allBad + inc) % m;
    }
    
    cout << norm(cand[n] - allBad, m) << endl;
    
    return 0;
}

