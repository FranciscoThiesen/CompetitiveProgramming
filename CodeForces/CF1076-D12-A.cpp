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

inline ll powmod(ll a, ll b)
{
    ll res = 1;
    a %= mod;
    assert(b >= 0);
    for(;b;b>>=1) 
    {
        if(b&1) res = (res * a) % mod;
        a = (a*a) % mod;
    }
    return res;
}


int main() 
{
    int n;
    string s;
    cin >> n >> s;
    int smallestPos = n - 1;
    vi rem(n, 0);
    rem[n - 1] = true;
    for(int i = n - 2; i >= 0; --i)
    {
        if( s[i] > s[smallestPos] )
        {
            rem[i] = 1;
            smallestPos = i;
        }
        if( s[i] < s[smallestPos] ) smallestPos = i;
    }
    bool seen = false;
    string res;
    for(int i = 0; i < n; ++i)
    {
        if(seen) res += s[i];
        else
        {
            if(rem[i] == 1)
            {
                seen = true;
            }
            else res += s[i];
        }
    }
    cout << res << endl;
    return 0;
}
