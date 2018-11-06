#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()

using namespace std;

using vi = vector<int>;

int n, m;
vi h, c;

bool f(int v)
{
    vector< int > candles(v);
    long long maxFlow = 0;
    for(int i = 0; i < v; ++i)
    {
        candles[i] = c[i];
        maxFlow += c[i];
    }
    sort( all(candles ) );
    
    int leftIdx = 0;
    
    array<long long, 2> s = { 0, maxFlow };
    
    long long minC = maxFlow;

    for(int i = v - 1; i >= 0; --i)
    {
        // Removing edge from candle[i] -> superSink, from the cut
        s[1] -= candles[i]; 
    
        while( leftIdx < n && h[leftIdx] < v - i)
        {
            s[0] += h[leftIdx++]; // adding adge superSource -> h[idx], to the cut
        }
        
        minC = min( minC, 0LL + s[0] + s[1] + 1LL * ( v - i ) * ( n - leftIdx) ); 
    }
    cerr << " mid = " << v << " minCut = " << minC << " maxFlow = " << maxFlow << endl;
    return (minC == maxFlow);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    h.resize(n); c.resize(m);
    for(int& x : h) cin >> x;
    for(int& x : c) cin >> x;
    sort(all(h) );
    
    int bl = 0, br = m;
    while( bl < br)
    {
        int bm = bl + br >> 1;
        if( f(bm) ) bl = bm;
        else br = max( bm - 1, 0);
        if(bl == br - 1)
        {
            if(f(br) ) bl = br;
            else br = bl;
        }
    }
    cout << bl << endl;
    return 0;


}
