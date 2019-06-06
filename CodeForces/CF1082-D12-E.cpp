#include <bits/stdc++.h>

using namespace std;

constexpr int ms = 5 * 1e5 + 13;

vector<int> occ[ms];
vector<int> acc;
inline int kadane(const vector<int>& vec)
{
    int cur = 0, best = 0;
    for(const int& x : vec)
    {
        cur = max(cur + x, 0);
        best = max(cur, best);
    }
    return best;
}

inline int calcFreq(int left, int right) { return acc[right] - acc[left - 1]; }

inline int doit(const int value)
{
    int lastOcc = 1; 
    vector<int> solver;
    for(const int& position : occ[value] )
    {
        solver.push_back( - calcFreq(lastOcc, position) );
        solver.push_back(1);
        lastOcc = position;
    }
    return kadane( solver );
}


int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n, c;
    cin >> n >> c;
    acc.assign(n + 1, 0);
    int ans = 0;
    int inc = 0;
    int last = 0;
    
    for(int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        last = max(x, last);
        if(x == c) ++ans;
        occ[x].push_back(i + 1);
        acc[i + 1] = acc[i] + ( x == c );
    }
    
    for(int i = 1; i <= last; ++i)
    {
        if(!occ[i].empty() && i != c) inc = max( inc, doit( i) ); 
    }

    cout << ans + inc << endl;
    return 0;
}
