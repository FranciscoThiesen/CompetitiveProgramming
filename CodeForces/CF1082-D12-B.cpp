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
    vector<pair<char, int> > segments;
    int n;
    cin >> n;
    string s;
    cin >> s;
    char cur = s[0];
    int  tam = 1;
    int ans = 0; 
    for(int i = 1; i < n; ++i)
    {
        if( s[i] == cur) ++tam;
        else
        {
            segments.emplace_back(cur, tam);
            tam = 1;
            cur = s[i];
        }
    }
    segments.emplace_back(cur, tam);
    int countG = 0;
    int countS = 0;
    for(const auto& v : segments) if( v.first == 'G') ans = max(ans, v.second);
    int len = sz(segments);
    
    for(const auto& v : segments)
    {
        if( v.first == 'G') countG++;
        else countS++;
    }

    for(int i = 0; i < len - 2; ++i)
    {
        if( segments[i].first == 'G')
        {
            if( segments[i + 1].second == 1)
            {
                //caso interessante
                if(countG > 2)
                {
                    ans = max( ans, segments[i].second + segments[i + 2].second + 1);
                }
                else if(countG == 2)
                {
                    ans = max( ans, segments[i].second + segments[i + 2].second);
                }
            }
            else
            {
                if( countG >= 2 ) ans = max( ans, max( segments[i].second, segments[i + 2].second) + 1 );
            }
        }
    }
    cout << ans << endl;
    return 0;
}

