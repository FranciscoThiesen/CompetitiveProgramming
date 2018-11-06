#include <bits/stdc++.h>

using namespace std;

constexpr int ms = 1e5 + 13;

vector<int> h, c;
vector<long long> accumulatedCandles;

// vou tentar preencher as velas do intervalo [0, x)
bool ok(int x)
{
    if(x == 0) return true; // 0 velas..
    
    long long desired = accumulatedCandles[ x - 1];
    long long cur = 0; 
    for(const int& v : h) cur += (long long ) min(x, v); 
   	cerr << " cur = " << cur << " desired = " << desired << endl;
    return (cur >= desired);
}



int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    h.resize(n);
    c.resize(m);
    for(int& x : h) cin >> x;
    for(int& x : c) cin >> x;
    accumulatedCandles.resize(m);
    accumulatedCandles[0] = c[0];
    for(int i = 1; i < m; ++i) accumulatedCandles[i] = accumulatedCandles[i - 1] + c[i];
      
    int lo = 0, hi = m;
    while(lo < hi)
    {
        int mid = lo + (hi - lo + 1) / 2;
        if(ok(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << endl;
    return 0;
}
