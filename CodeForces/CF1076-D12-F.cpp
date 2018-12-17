#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

constexpr int ms = 3 * 1e5 + 13;
constexpr int inf = 1e9;

int dp[ms][2];

int n, k;
int a[ms], b[ms];

inline int doit(int pa, int pb, int a, int b)
{
	int ans = inf;
	if (pa <= k)
    {
		int tot = pa + a;
		int cnt = (tot + k - 1) / k - 1;
		if (b == cnt) ans = min(ans, tot - cnt * k);
		else if (b > cnt && b <= a * ll(k)) ans = min(ans, 1);
	}
	if (pb <= k)
    {
		int cnt = (a + k - 1) / k - 1;
		if (b == cnt) ans = min(ans, a - cnt * k);
		else if (b > cnt && b <= (a - 1) * ll(k) + (k - pb)) ans = min(ans, 1);
	}
	return ans;
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> k;
    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < n; ++i) cin >> b[i];
    for(int i = 0; i < ms; ++i) for(int j = 0; j < 2; ++j) dp[i][j] = inf;
	dp[0][0] = dp[0][1] = 0;
	for(int i = 0; i < n; ++i)
    {
		dp[i + 1][0] = doit(dp[i][0], dp[i][1], a[i], b[i]);
		dp[i + 1][1] = doit(dp[i][1], dp[i][0], b[i], a[i]);
	}
    if( dp[n][0] <= k || dp[n][1] <= k) cout << "YES" << endl;
    else cout << "NO" << endl;
	return 0;
}
