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

int main() {
    int t;
    scanf("%d", &t);
    rep(i, 0, t)
    {
        long long d;
        scanf("%lld", &d);
        long long delta = d * d - 4 * d;
        if( delta < 0 ) puts("N");
        else
        {
            if(d == 0)
            {
                puts("Y 0.00000000 0.00000000");
                continue;
            }
            double D = (double) d;
            double DELTA = (double) delta;
            double b = D + sqrt(DELTA);
            b /= 2.0;
            double a = D / b;
            printf("Y %.9lf %.9lf\n", a, b);
        }
    }
    return 0;
}
