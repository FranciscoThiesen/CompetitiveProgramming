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
    int n;
    buff();
    cin >> n;
    string s, t;
    cin >> s >> t;
    string S, T;
    S = s;
    T = t;
    sort(all(S));
    sort(all(T));
    vi moves;
    if(S != T) {
        cout << -1 << endl;
        return 0;
    }
    else
    {
        for(int i = 0; i < n; ++i)
        {
            if(s[i] == t[i]) continue;
            else
            {
                for(int j = i + 1; j < n; ++j)
                {
                    if(s[j] == t[i])
                    {
                        for(int k = j; k > i; --k)
                        {
                            moves.pb(k);
                            swap(s[k], s[k - 1]);
                        }
                        break;
                    }
                }
            }
        }
    }
    cout << sz(moves) << endl;
    for(const int& x : moves) cout << x << " ";
}