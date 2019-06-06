#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define sz(x) (int) (x).size()
#define fast() ios::sync_with_stdio(false); cin.tie(NULL)
#define fi(x) get<0>(x)
#define se(x) get<1>(x)
#define th(x) get<2>(x)
using ll = long long;
using ii = pair<int, int>;

struct UF {
    vector<int> parent, rank;
    UF(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        iota( all(parent), 0 );
    }
    int pai(int v) {
        if(parent[v] != v) parent[v] = pai( parent[v] );
        return parent[v];
    }
    bool unite(int a, int b) 
    {
        a = pai(a), b = pai(b);
        if(a == b) return false;
        if( rank[a] < rank[b] ) parent[a] = b;
        else parent[b] = a;
        rank[a] += (rank[a] == rank[b]);
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    UF uf(n);
    vector< tuple<int, int, int> > edges;
    
    for(int i = 0; i < m; ++i)
    {
        int u, v, c;
        cin >> u >> v >> c;
        edges.emplace_back(c, u - 1, v - 1);
    }
    
    vector<tuple<int, int, int> > sorted = edges;
    sort( all(sorted) );
    
    int q;
    cin >> q;
    deque<bool> ans(q, true );
    vector< tuple<int, int, int> > queries;
    for(int i = 0; i < q; ++i)
    {
        int k;
        cin >> k;
        while(k--)
        {
            int x;
            cin >> x;
            queries.emplace_back(fi(edges[x - 1]), i, x - 1);
        }
    }
    
    sort( all(queries ) );
    int stQ = 0; 
    int szQ = sz(queries);
    for(const auto& edge : sorted)
    {
        while( stQ < szQ && fi(queries[stQ]) <= fi(edge) )
        {
            int ndQ = stQ;
            auto good = [] ( const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
                return ( fi(a) == fi(b) && se(a) == se(b) );
            };
            while(ndQ < szQ && good(queries[stQ], queries[ndQ] ) ) ndQ++;
            auto proc = [&] () 
            {
                vector<int> nodes;
                for(int i = stQ; i < ndQ; ++i)
                {
                    auto& ed = edges[ th( queries[i] ) ];        
                    int v1 = uf.pai( se(ed) );
                    int v2 = uf.pai( th(ed) );
                    if(v1 == v2) return true;
                    nodes.push_back(v1);
                    nodes.push_back(v2);
                }
                sort( all(nodes) );
                nodes.erase(unique(all(nodes)), nodes.end() );
                UF tempUF( sz(nodes ) );
                for(int i = stQ; i < ndQ; ++i)
                {
                    auto& ed = edges[ th( queries[i] ) ];
                    int v1 = uf.pai( se(ed) );
                    int v2 = uf.pai( th(ed) );
                    v1 = lower_bound( all(nodes), v1) - nodes.begin();
                    v2 = lower_bound( all(nodes), v2) - nodes.begin();
                    bool ok = tempUF.unite(v1, v2);
                    if(!ok) return true;
                }
                return false;
            };
            if( proc() ) ans[ se(queries[stQ] ) ] = false;
            stQ = ndQ;
        }
        uf.unite(se(edge), th(edge) );
    }
    for(const auto& b : ans ) cout << ( b ? "YES" : "NO" ) << "\n";
    return 0;
}
