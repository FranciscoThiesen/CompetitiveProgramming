#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define mset(x, v) memset((x), (v), sizeof (x) )
#define buff() ios::sync_with_stdio(0);cin.tie(0)
#define sz(x) ( (int) (x).size() )

using vi  = vector<int>;
using ll  = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vvi = vector<vi>;

constexpr int mod = 1000000007;
constexpr int inf = 0x3f3f3f3f;

inline ll powmod(ll a, ll b) {
    ll res = 1;
    a %= mod;
    assert(b >= 0);
    for(;b;b>>=1) {
        if(b&1) res = (res * a) % mod;
        a = (a*a) % mod;
    }
    return res;
}

constexpr int ms = 1010;

int mat[ms][ms][4];
int mrkCol[ms][ms + 1];
int mrkLin[ms][ms + 1];

char casa[ms][ms];
char gabarito[ms][ms];
int n, m;

int main() {
    buff();
    cin >> n >> m;
    rep(i, 0, n) rep(j, 0, m) cin >> casa[i][j];
    // Vamos percorrer 4 matrizes pra calcular os valores acumulados

    // 0 -> Cima para baixo
    // 1 -> Baixo p cima
    // 2 -> Esq p dir
    // 3 -> dir p esq
    
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(casa[i][j] == '*') {
                if(casa[i - 1][j] == '*') {
                    mat[i][j][0] = mat[i - 1][j][0] + 1;
                }
            }
        }
    }
    for(int i = n - 2; i >= 0; --i) {
        for(int j = 0; j < m; ++j) {
            if(casa[i][j] == '*') {
                if(casa[i + 1][j] == '*') {
                    mat[i][j][1] = mat[i + 1][j][1] + 1; 
                }
            }
        }
    }
    for(int j = 1; j < m; ++j) {
        for(int i = 0; i < n; ++i) {
            if(casa[i][j] == '*' && casa[i][j - 1] == '*') {
                mat[i][j][2] = mat[i][j - 1][2] + 1;
            }
        }
    }
    for(int j = m - 2; j >= 0; --j) {
        for(int i = 0; i < n; ++i) {
            if(casa[i][j] == '*' && casa[i][j + 1] == '*') {
                mat[i][j][3] = mat[i][j + 1][3] + 1;
            }
        }
    }
    vector< tuple<int, int, int> > stars;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            int mn = 10012301;
            rep(x, 0, 4) mn = min( mat[i][j][x], mn);
            if(mn > 0) {
                stars.emplace_back(i + 1, j + 1, mn);
                mrkLin[i][j - mn]++;
                mrkLin[i][j + mn + 1]--;
                mrkCol[j][i - mn]++;
                mrkCol[j][i + mn + 1]--;
            }
        }
    }
    // agora tem que checar se eh possivel
    bool good = true;
    
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(j > 0) mrkLin[i][j] += mrkLin[i][j - 1];
            if(mrkLin[i][j]) gabarito[i][j] = '*';
            else gabarito[i][j] = '.';
        }
    }
    
    for(int j = 0; j < m; ++j)
    {
        for(int i = 0; i < n; ++i)
        {
            if(i > 0) mrkCol[j][i] += mrkCol[j][i - 1];
            if(mrkCol[j][i]) gabarito[i][j] = '*';
        }
    }
    rep(i, 0, n) {
        rep(j, 0,m) {
            if(casa[i][j] != gabarito[i][j]) good = false;
        }
    }
    if(good) {
        cout << sz(stars) << endl;
        for(const auto&[x, y, z] : stars) cout << x << " " << y << " " << z << endl;
    }
    else cout << -1 << endl;
}