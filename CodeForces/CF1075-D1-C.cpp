#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()

using namespace std;

using pii = pair<int, int>;

constexpr int inf = 1e8 + 1;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin >> n;
    vector<pii> poly(n);
    for(int i = 0; i < n; ++i) cin >> poly[i].first >> poly[i].second;

    int maxX, maxY, minX, minY;
    
    vector<pii> xtreme;

    sort(all(poly), [] (const pii& a, const pii& b) { return a.first < b.first; } );
    minX = poly[0].first;
    maxX = poly[n - 1].first;
    xtreme.push_back(poly[0]);
    xtreme.push_back(poly[n - 1] );

    sort(all(poly), [] (const pii& a, const pii& b) { return a.second < b.second; } );
    minY = poly[0].second;
    maxY = poly[n - 1].second;
    xtreme.push_back(poly[0]);
    xtreme.push_back(poly[n - 1] );

    long long largerThan3 = 2LL * ( maxX - minX + maxY - minY);

    long long best = 0;
    sort(all(xtreme) );
    xtreme.erase( unique(all(xtreme) ), xtreme.end() ); 

    for(int i = 0; i < (int) xtreme.size(); ++i)
    {
        for(int j = i + 1; j < (int) xtreme.size(); ++j)
        {
            for(int x = 0; x < n; ++x)
            {
                if(poly[x] == xtreme[i] || poly[x] == xtreme[j]) continue;
                long long ans = 0;
                maxX = max( poly[x].first, max(xtreme[i].first, xtreme[j].first) );
                minX = min( poly[x].first, min(xtreme[i].first, xtreme[j].first) );
            
                maxY = max( poly[x].second, max(xtreme[i].second, xtreme[j].second) );
                minY = min( poly[x].second, min(xtreme[i].second, xtreme[j].second) );
                
                ans = 2LL * ( maxX - minX + maxY - minY);
                best = max(best, ans);
            }
        }
    }
    cout << best << " ";
    for(int i = 4; i <= n; ++i) cout << largerThan3 << " ";
    return 0;
}
