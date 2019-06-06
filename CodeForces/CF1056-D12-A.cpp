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

int main() 
{
    buff();
    int n;
    cin >> n;
    set<int> cand;
    for(int i = 0; i < n; ++i)
    {
        int k;
        cin >> k;
        if( i == 0)
        {
            for(int j = 0; j < k; ++j) 
            {
                int x;
                cin >> x;
                cand.insert(x);
            }
        }
        else
        {
            set<int> cur;
            for(int j = 0; j < k; ++j) 
            {
                int x;
                cin >> x;
                if( cand.find(x) != cand.end() ) cur.insert(x);
            }
            cand = cur;
        }
    }
    for(const int& x : cand) cout << x << " ";
    cout << endl;
    return 0;
}

