#include <bits/stdc++.h>
#define sz(x) (int) (x).size()
using namespace std;

constexpr int MAXN = 1000100;
constexpr int BASE = 31;
constexpr array<long long, 2> MD = { 1000LL * 1000LL * 1000LL + 7, 1000LL * 1000LL * 1000LL + 9};
long long hashVal[2][MAXN];
long long basePow[2][MAXN];

inline long long powMod(long long a, long long b, long long mod)
{
    long long res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1)
    {
        if(b&1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}

inline array<long long, 2> subHash(const int pos, const int len)
{
    array<long long, 2> ans = {0LL, 0LL};
    long long invMod[2];
    for(int i = 0; i < 2; ++i)
    {
        invMod[i] = powMod( basePow[i][pos], MD[i] - 2LL, MD[i]);
        ans[i] = (hashVal[i][pos + len] - hashVal[i][pos] + MD[i]) % MD[i];
        ans[i] = ( ans[i] * invMod[i] ) % MD[i];
    }
    return ans; 
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    basePow[0][0] = basePow[1][0] = 1LL;
    for(int x = 0; x < 2; ++x) for(int i = 1; i < MAXN; ++i) basePow[x][i] = ( basePow[x][i - 1] * BASE ) % MD[x];
    
    string s, t;
    cin >> s >> t;
    
    int N = sz(s), M = sz(t);
    
    hashVal[0][0] = hashVal[1][0] = 0LL;
    for(int x = 0; x < 2; ++x) for(int i = 0; i < M; ++i) hashVal[x][i + 1] = (hashVal[x][i] + basePow[x][i] * (t[i] - 'a' + 1LL) ) % MD[x];
    
    int n0 = 0, n1 = 0;
    for(int i = 0; i < N; ++i) n0 += ( s[i] == '0');
    n1 = N - n0;
    
    int ans = 0;
    for(int nLeft = 1; nLeft * n0 <= M; ++nLeft)
    {
        int nRight = (M - nLeft * n0) / n1;
        if( nRight < 1 || nRight * n1 + nLeft * n0 != M) continue;
        array<long long, 2> h0, h1, hCur;
        array<bool, 2> ok = { false, false };
        bool bad = false;
        int pos = 0;
        for(int i = 0; i < N; ++i)
        {
            if(s[i] == '0')
            {
                hCur = subHash( pos, nLeft );
                if( !ok[0] ) { h0 = hCur; ok[0] = true;}
                else if( h0 != hCur) bad = true;
                pos += nLeft;
            }
            else
            {
                hCur = subHash( pos, nRight );
                if( !ok[1] ) { h1 = hCur; ok[1] = true; }
                else if( h1 != hCur) bad = true;
                pos += nRight;
            }
        }
        if( (h0[0] == h1[0] && h0[1] == h1[1] ) && nLeft == nRight ) bad = true;
        if(!bad) ++ans;
    }
    cout << ans << endl;
    return 0;
}
