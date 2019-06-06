#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

constexpr long long inf = 0x3f3f3f3f3f3f3f3fLL;


int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    vector< vector< tuple<int, int, int> > > g(n);
    
    deque<bool> edges(m + 1, false); 
    vector< long long > dist(n, inf);
    vector< int > bestEdge(n, -1);
    
    for(int i = 0; i < m; ++i)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        --a;--b;
        g[a].emplace_back(c, b, i);
        g[b].emplace_back(c, a, i);
    }

    set< tuple<long long, int, int> > q;
    int used = -1;
    dist[0] = 0ll;
    
    q.insert( make_tuple(0ll, 0, m) );
    
    while(used < k && !q.empty() )
    {
        auto [cost, node, edgeIndex] = *(q.begin() );
        q.erase(q.begin());
        edges[ edgeIndex ] = true;
        ++used; 
        for(const auto& edg : g[ node ])
        {
            auto [dst, adjNode, edgeIdx] = edg;
            if(cost + 1LL * dst < dist[ adjNode ])
            {
                if( bestEdge[ adjNode ] != -1) q.erase( make_tuple(dist[adjNode], adjNode, bestEdge[adjNode] ) );
                dist[ adjNode ] = cost + 1LL * dst;
                bestEdge[ adjNode ] = edgeIdx; 
                q.emplace( make_tuple( dist[adjNode], adjNode, edgeIdx ) ); 
            }
        }
    }
    vi ans;
    auto sz = [&] ( vector<int> x) { return (int) x.size(); };
    for(int i = 0; i < m; ++i) if(edges[i]) ans.push_back(i + 1);
    printf("%d\n", sz(ans) );
    for(const int& v : ans) printf("%d ", v);
    puts("");
    return 0;
}
