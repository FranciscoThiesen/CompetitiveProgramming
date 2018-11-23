#include <bits/stdc++.h>

using namespace std;

constexpr int ms  = 3 * 1e5 + 13;
constexpr int inf = 0x3f3f3f3f;

int dp[ms][2];
int day[ms][2];
int n, k;
inline void remin(int& a, const int b) { a = min(a, b); }

int doit(const int pa, const int pb, const int a, const int b)
{
    int res = inf;
    if(pa <= k)
    {
        int cnt = (pa + a + k - 1) / k - 1;
        if(b == cnt) remin( res , pa + a - cnt * k);
    }
    if(pb <= k)
    {
        int cnt = (a + k - 1) / k - 1;
        if(b == cnt) remin( res , a - cnt * k);
        else if(b > cnt && b <= 1LL * (a - 1LL) * 1LL * k + 1LL * (k - pb) ) remin( res, 1);
    }
    return res;
};



int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 0; i < n; ++i) cin >> day[i + 1][0];
    for(int i = 0; i < n; ++i) cin >> day[i + 1][1];
    
    for(int i = 1; i <= n; ++i)
    {
        dp[i][0] = dp[i][1] = inf;
        dp[i][0] = doit( dp[i - 1][0], dp[i - 1][1], day[i - 1][0], day[i - 1][1] );
        dp[i][1] = doit( dp[i - 1][1], dp[i - 1][0], day[i - 1][1], day[i - 1][0] );
        cout << dp[i][0] << " " << dp[i][1] << endl;
    }
    remin( dp[n][0], dp[n][1]);
    cout << ( dp[n][0] <= k ? "YES" : "NO" ) << endl;
    return 0;
}
