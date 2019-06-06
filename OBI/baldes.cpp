#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef vector<int> vi;
typedef pair<int, int> ii;

constexpr int ms = 1e5 + 13;
constexpr int inf = 0x3f3f3f3f;

// Essa arvore vai retornar o indice do balde que contem a menor bola e esse valor
template <typename T>
struct seg1{
	int N;
	vector<T> Tree;
	T id;

	// mudar de acordo com o problema!
	T combine(const T& a, const T& b){ return min(a,b); }

	seg1(int n, T dummy) : N(n), id(dummy) { Tree.assign(2*N, id); }
	
    void build() { for(int idx = N-1; idx > 0; --idx) Tree[idx] = combine(Tree[(idx << 1)], Tree[(idx << 1) | 1]); }
	
    void update(int p, T val){
		Tree[p += N] = val;
		while(p > 1) {
			Tree[p>>1] = combine(Tree[p], Tree[p^1]);
			p >>= 1;
		}
	}
	
    // Query of [l, r)
	T query(int l, int r){
		T res = id;
		for(l += N, r += N; l < r; l >>= 1, r >>= 1){
			if(l&1) res = combine(res, Tree[l++]);
			if(r&1) res = combine(res, Tree[--r]);
		}
		return res;
	}
};

// Essa arvore vai retornar o indice do balde que contem a maior bola e esse valor
template <typename T>
struct seg2{
	int N;
	vector<T> Tree;
	T id;

	// mudar de acordo com o problema!
	T combine(const T& a, const T& b){ return max(a,b); }

	seg2(int n, T dummy) : N(n), id(dummy) { Tree.assign(2*N, id); }
	
    void build() { for(int idx = N-1; idx > 0; --idx) Tree[idx] = combine(Tree[(idx << 1)], Tree[(idx << 1) | 1]); }
	
    void update(int p, T val){
		Tree[p += N] = val;
		while(p > 1) {
			Tree[p>>1] = combine(Tree[p], Tree[p^1]);
			p >>= 1;
		}
	}
	
    // Query of [l, r)
	T query(int l, int r){
		T res = id;
		for(l += N, r += N; l < r; l >>= 1, r >>= 1){
			if(l&1) res = combine(res, Tree[l++]);
			if(r&1) res = combine(res, Tree[--r]);
		}
		return res;
	}
};

int main() {
    ios::sync_with_stdio( false ); cin.tie( nullptr );
    int n, m;
    cin >> n >> m;
    vector< ii > vetor_inicial(n);
    vector< int > max_bola(n), min_bola(n);
    ii dummyMax = {-1, -1}; 
    ii dummyMin = {inf, inf};

    seg1< pair<int, int> > arvMin(n, dummyMin );
    seg2< pair<int, int> > arvMax(n, dummyMax );

    for(int i = 0; i < n; ++i)
    {
        cin >> max_bola[i];
        min_bola[i] = max_bola[i];
        
        arvMin.Tree[n + i].first = max_bola[i];
        arvMin.Tree[n + i].second = i;
    
        arvMax.Tree[n + i].first = max_bola[i];
        arvMax.Tree[n + i].second = i;
    }
    
    arvMin.build(); 
    arvMax.build();

    for(int i = 0; i < m; ++i)
    {
        int t, a, b;
        cin >> t >> a >> b;
        if( t == 1)
        {
            --b;
            if( a > max_bola[b] )
            {
                max_bola[b] = a;
                arvMax.update( b , make_pair(a, b ) );
            }
            if( a < min_bola[b] ) {
                min_bola[b] = a;
                arvMin.update( b, make_pair(a, b) );
            }
        }
        else
        {
            --a; --b;
            auto mais_leve = arvMin.query(a, b + 1);
            auto mais_pesada = arvMax.query(a, b + 1);
            
            if( mais_leve.second != mais_pesada.second )
            {
                cout << mais_pesada.first - mais_leve.first << endl;
            }
            else
            {
                int k = mais_leve.second;
                int maior_diff = 0;
                if( k < b )
                {
                    auto maior_direita = arvMax.query(k + 1, b + 1);
                    auto menor_direita = arvMin.query(k + 1, b + 1);
                    maior_diff = max( maior_diff, maior_direita.first - mais_leve.first );
                    maior_diff = max( maior_diff, mais_pesada.first - menor_direita.first );
                }
                if( k > a )
                {
                    auto maior_esquerda = arvMax.query(a, k);
                    auto menor_esquerda = arvMin.query(a, k); 
                    maior_diff = max( maior_diff, maior_esquerda.first - mais_leve.first );
                    maior_diff = max( maior_diff, mais_pesada.first - menor_esquerda.first );
                }
                cout << maior_diff << endl;
            }
        }
    }
    
    return 0;
}
