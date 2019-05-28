#include <bits/stdc++.h>


using namespace std;

#define TRACE(x) x
#define WATCH(x) TRACE( cout << #x" = " << x << endl)
#define PRINT(x) TRACE(printf(x))
#define WATCHR(a, b) TRACE( for(auto c = a; c != b;) cout << *(c++) << " "; cout << endl)
#define WATCHC(V) TRACE({cout << #V" = "; WATCHR(V.begin(), V.end()); } )

#define all(v) (v).begin(), (v).end()
#define sz(v) (int) (v).size()

#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define shandom_ruffle random_shuffle

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr long long MOD = 10000000007;

inline ll modPow( ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1) {
        if(b&1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); 
    int n, d;
    cin >> n >> d;
    vector< pair<int, double> > vec(n);
    for(int i = 0; i < n; ++i) cin >> vec[i].first;
    for(int i = 0; i < n; ++i) cin >> vec[i].second;
    sort( all(vec) );
    
    double melhor_poder = vec[0].second;
    int total_grupos = 0;
    vector<double> acc(n, 0.0);
    acc[0] = vec[0].second;
    for(int i = 1; i < n; ++i) acc[i] = (acc[i - 1] + vec[i].second );
    
    double soma_poder = 0.0;
    deque< pair<int, double> > publico_ativo;
    int qtd_publico = 1, maior_publico = 1, qtd_publicos = 1;

    publico_ativo.push_back( vec[0] );
    soma_poder += vec[0].second;

    for(int i = 1; i < n; ++i)
    {
        if( publico_ativo.front().first + d < vec[i].first ) qtd_publicos++;
        publico_ativo.push_back( vec[i] );
        soma_poder += vec[i].second;
        qtd_publico++;

        while( !publico_ativo.empty() && publico_ativo.front().first + d < vec[i].first )
        {
            soma_poder -= publico_ativo.front().second;
            publico_ativo.pop_front();
            qtd_publico--;
        }
        
        melhor_poder = max( soma_poder, melhor_poder );
        maior_publico = max( maior_publico, qtd_publico );

    }

    cout << qtd_publicos << " " << maior_publico << " ";
    cout << fixed << setprecision(2) << melhor_poder << endl;
    return 0;
}