#include <bits/stdc++.h>

using namespace std;

constexpr int ms = 2 * 1e5 + 13;

int arr[ms];
vector<int> factors[ms], g[ms];
bitset<ms> isPrime;
int ans = 0;
unordered_map<int, int> dp[ms];

void sieve() {
    isPrime.set();
    isPrime[0] = isPrime[1] = false;
    for(long long i = 2; i < ms; ++i ) {
        if( isPrime[i] ) {
            for(long long j = i; j < ms; j += i) {
                isPrime[j] = false;
                factors[j].push_back(i);
            }
        }
    }
}

inline void dfs(int loc, int par = -1) {
    for(const int& nei : g[loc] ) {
        if(nei != par) {
            dfs(nei, loc);
            for(const int f : factors[ arr[loc] ] ) {
                ans = max( ans, dp[loc][f] + dp[nei][f] + 1);
                dp[loc][f] = max( dp[loc][f], dp[nei][f]);
            }
        }
    }
    for(const int f : factors[arr[loc]] ) {
        dp[loc][f] += 1;
        ans = max( ans, dp[loc][f]);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", arr + i);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a;--b;
        g[a].push_back(b), g[b].push_back(a);
    }
    sieve();
    dfs(0);
    cout << ans << endl;
}
