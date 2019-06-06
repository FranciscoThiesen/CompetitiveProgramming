#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define TRACE(x) x
#define WATCH(x) TRACE( cout << #x" = " << x << endl)
#define PRINT(x) TRACE(printf(x))
#define WATCHR(a, b) TRACE( for(auto c = a; c != b;) cout << *(c++) << " "; cout << endl)
#define WATCHC(V) TRACE({cout << #V" = "; WATCHR(V.begin(), V.end()); } )

#define all(v) (v).begin(), (v).end()
#define sz(v) (int) (v).size()

#define fu(i,a,b) for(int (i) = (a); (i) < (b); ++(i))

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define shandom_ruffle random_shuffle
#define funoredered_map __fast_unordered_map
template<class Key, class Value, class Hash = std::hash<Key>>
using funordered_map = __gnu_pbds::gp_hash_table<Key, Value, Hash>;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;

constexpr int INF = 0x3f3f3f3f;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct UF { 
    vi p, rank;
    UF(int n) {
        p = vi(n);
        rank = vi(n, 0);
        iota( all(p), 0);
    }

    int rep(int v) {
        if( p[v] != v) p[v] = rep( p[v] );
        return p[v];
    }

    bool unio(int a, int b) {
        a = rep(a), b = rep(b);
        if( a == b ) return false;
        if( rank[a] < rank[b] ) p[a] = b;
        else p[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); 
    int n, m;
    cin >> n >> m;
    vector< tuple<int, int, int> > edges;
    fu(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        edges.emplace_back( c, a, b );
    }
    UF xablau(n);
    sort( all(edges) );
    int bufferCost = 0;
    vector< tuple< int, int, int> > bufferEdges;
    int ans = 0;
    
    for(int i = 0; i < m; ++i) {
        int last = i;
        int cost = get<0>( edges[i] );
        TRACE( cout << "processando as arestas de custo = " << cost << endl; )
        if( bufferEdges.empty() ) bufferCost = cost + 1;
        while( bufferCost < cost ) {
            // process bufferEdges
            TRACE( cout << "vou processar as arestas do buffer" << endl;)
            vector< tuple<int, int, int> > aux;
            for(const auto& e : bufferEdges ) {
                TRACE( printf("Olhando a aresta (%d, %d, %d)\n", get<0>(e), get<1>(e), get<2>(e) ); )
                if( xablau.unio( get<1>(e), get<2>(e) ) == false ) {
                    aux.emplace_back( e );
                    ++ans;
                }
            }
            bufferEdges.clear();
            if( !aux.empty() ) {
                bufferEdges = aux;
                bufferCost++;
            }
            else bufferCost = cost + 1;
        }
        // agora vou processar todas as bufferEdges
        vector< tuple<int, int, int> > aux;
        TRACE( printf("Olhando as arestas do buffer de custo = %d\n", cost );) 
        for(const auto& e : bufferEdges ) {
            TRACE( printf("Olhando a aresta (%d, %d, %d)\n", get<0>(e), get<1>(e), get<2>(e) ); )
            if( xablau.unio( get<1>(e), get<2>(e) ) == false ) {
                ans++;
                aux.emplace_back( e );
            }
        }
        bufferEdges.clear();
        bufferEdges = aux;

        for(int j = i; j < m; ++j) {
            if( get<0>( edges[j] ) != get<0> ( edges[i] ) ) {
                last = j - 1;
                break;
            }
        }
        

        for(int x = i; x <= last; ++x) {
            TRACE( printf("Olhando a aresta (%d, %d, %d)\n", get<0> (edges[x] ), get<1>(edges[x]), get<2>(edges[x]) ) ) ;
            if( xablau.unio( get<1>(edges[x]), get<2>(edges[x]) ) == false ) {
                bufferEdges.emplace_back( edges[x] ); 
                ans++;
            }
        }
        bufferCost++;
        i = last;
        TRACE( cout << "resp parcial = " << ans << endl; )
    }
    cout << ans << endl;

}

