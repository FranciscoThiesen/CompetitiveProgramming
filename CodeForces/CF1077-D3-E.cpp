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

vector<pii> levelFreq;
int n;
int vec[200010];
int calc(int startFreq)
{
    int ans = 0;
    int startIdx = lower_bound(all(levelFreq), make_pair(startFreq, -1) ) - levelFreq.begin();
    int need = startFreq;
    while(startIdx < sz(levelFreq) )
    {
        if( levelFreq[startIdx].first  >= need)
        {
            ans += need;
            need *= 2;
        }
        startIdx++;
    }   
    return ans;
}

int main() {
    scanf("%d", &n);
    map<int, int> freq;
    rep(i,0,n) {
        scanf("%d", &vec[i]);
        freq[vec[i]]++;
    }
    for(const auto& v : freq) levelFreq.emplace_back(v.second, v.first);
    sort(all(levelFreq) );
    int maxF = levelFreq.back().first;
    int res = 0;
    for(int i = 1; i <= maxF; ++i)
    {
        res = max(res, calc(i) );
    }
    printf("%d\n", res);
    return 0;

}