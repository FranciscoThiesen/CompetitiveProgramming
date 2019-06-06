#include <bits/stdc++.h>
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define all(v) (v).begin(), (v).end()

using namespace std;

using ll = long long;

constexpr int ms = 1e5 + 13;
constexpr ll base = 256;

constexpr array<long long, 2> p = { 1000LL * 1000LL * 1000LL + 7, 1000LL * 1000LL * 1000LL + 37 };
ll basePow[2][ms];

struct Hash {
    array<ll, 2> h = {0LL, 0LL};
    int len = 0;
    Hash() {}
    void addChar( char c ) {
        int val = (c - ' ') + 1;
        rep(x, 0, 2) {
            ll inc = (1LL * val * basePow[x][len]) % p[x];
            h[x] = (h[x] + inc) % p[x];
        }
        ++len;
    }
    void addStr( string s) { for(char c : s) addChar(c); }
    pair<ll, ll> val() { return make_pair(h[0], h[1]); }
};


int main()
{
    ios::sync_with_stdio(0); cin.tie(NULL);
    basePow[0][0] = basePow[1][0] = 1;
    rep(x, 0, 2) rep(i, 1, ms) basePow[x][i] = (basePow[x][i - 1] * base) % p[x]; 
    map< pair<ll, ll>, vector< tuple<int, int, int, int> > > memo;
    int n;
    cin >> n;
    
    vector<string> vec(n);
    vector<int> tam(n);
    
    for(string& s : vec) cin >> s;
    
    rep(i, 0, n) tam[i] = (int) vec[i].size();
    
    int sumLen = accumulate( all(tam), 0 );
    sumLen += (n - 1);
    
    char space = ' ';
    rep(i, 0, n) 
    {
        Hash v = Hash();
        int st = i;
        int nd = 0;
        int wrd = 0;
        int len = 0;
        rep(j, i, n)
        {
            len += tam[j];
            ++wrd;
            v.addChar(space);
            nd = j;
            v.addStr( vec[j] );
            memo[ v.val() ].emplace_back(st, nd, wrd, len);
        }
    }
    
    int best = 0;
    for(const auto& elem : memo )
    {
        int countDisjoint = 0;
        int curEnd = -1;
        int saving = 0;
        for(const auto& cand : elem.second)
        {
            int w,x,y,z;
            tie(w,x,y,z) = cand;
            if( w > curEnd )
            {
                countDisjoint++;
                curEnd = x;
                int newLen = y;
                int oldLen = z + (y - 1);
                saving += (oldLen - newLen);
            }
        }
        if( countDisjoint >= 2) best = max(saving, best);
    }
    cout << sumLen - best << endl;
    return 0;
}
