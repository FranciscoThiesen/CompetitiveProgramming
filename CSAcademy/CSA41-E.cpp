#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()

using namespace std;

int n, m;
vector<int> candleHeights, dailyDemand;

bool f(int v)
{
    vector< int > demands(v);
    long long maxFlow = 0;
    
    for(int i = 0; i < v; ++i)
    {
        demands[i] = dailyDemand[i];
        maxFlow += dailyDemand[i];
    }
    sort( all( demands ) );
   

    int leftIdx = 0;
    
    array<long long, 2> s = { 0, maxFlow };
    
    long long minC = maxFlow;

    for(int i = v - 1; i >= 0; --i)
    {
        s[1] -= demands[i]; 
    
        while( leftIdx < n && candleHeights[leftIdx] < v - i)
        {
            s[0] += candleHeights[leftIdx++];
        }
        
        minC = min( minC, 0LL + s[0] + s[1] + 1LL * ( v - i ) * ( n - leftIdx) ); 
    }

    return (minC == maxFlow);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    candleHeights.resize(n); 
    dailyDemand.resize(m);
    
    for(int& x : candleHeights) cin >> x;
    for(int& x : dailyDemand) cin >> x;
    
    sort(all( candleHeights ) );
    
    int lo = 0, hi = m;
    while(lo < hi)
    {
        int mid = lo + (hi - lo + 1) / 2;
        if( f(mid) ) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << endl;
    
    return 0;

}
