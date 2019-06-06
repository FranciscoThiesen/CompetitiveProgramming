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
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) (int) (v).size()

#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define trav(a, x) for(auto& a : x)

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

#define funoredered_map __fast_unordered_map
template<class Key, class Value, class Hash = std::hash<Key>>
using funordered_map = __gnu_pbds::gp_hash_table<Key, Value, Hash>;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr int NINF = 0xc0c0c0c0;
constexpr double EPS = 1e-8;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ostream &operator<<(ostream& os, const pair<auto, auto>& p) {
    return os << "(" << p.first << "," << p.second << ")";
}

inline int cmp_double( double x, double y, double tol = EPS) {
    return (x <= y + tol) ? ( x + tol < y) ? -1 : 0 : 1;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const long long  base = 357;
const long long MAXN = 100100;
const array<ll, 2> MD = { 1000LL * 1000LL * 1000LL + 7, 1000LL * 1000LL * 1000LL + 23 };

ll hashVal[2][100100];
ll basePow[2][100100];

struct Hash {
    int len = 0;    
    array<ll, 2> hVal = {0LL, 0LL};
    Hash() {} 
    void addC( char c) {
        int val = ( c - ' ') + 1; 
        rep(i, 0, 2) {
            hVal[i] = (hVal[i] +  ( (val * basePow[i][len]) % MD[i] ) ) % MD[i];
        }
        ++len;
    }
    void addStr( string s)
    {
        for(char c : s) addC( c );
    }
};

int main()
{
	basePow[0][0] = basePow[1][0] = 1LL;
    rep(i, 0, 2) {
        rep(j, 1, MAXN) {
            basePow[i][j] = (basePow[i][j - 1] * base) % MD[i];
        }
    }
    ios::sync_with_stdio(0); cin.tie(NULL);
    map< pll , vector< pii > > mapa;
    int n;
    cin >> n;
    TRACE( cout << "N = " << n << endl; )
    vector<string> vec(n);
    int tamanhoTotal = 0;
    rep(i,0,n) cin >> vec[i];
    char space = ' ';
    vector<int> accuLen(n + 1);
    accuLen[0] = 0;
    TRACE( cout << "preLoop" << endl; )
    rep(i,0,n)
    {
        if( i == 0) accuLen[i] = sz(vec[i]);
        else accuLen[i + 1] = 1 + accuLen[i] + sz(vec[i]);
        Hash accu = Hash();
        accu.addStr(vec[i]);
        mapa[ make_pair( accu.hVal[0], accu.hVal[1] ) ].pb( make_pair(i, 1) );
        int wordCount = 1;
        rep(nxt, i + 1, n)
        {
            wordCount++;
            accu.addC( space );
            accu.addStr(vec[nxt]);
            mapa[ make_pair( accu.hVal[0], accu.hVal[1] ) ].pb( make_pair(i, wordCount) );
        }
    }
    TRACE( cout << "chegay 1 " << endl; )
    int res = tamanhoTotal;
    for(const auto& v : mapa) {
        int countGood = 0;
        int prevNd = -1;
        int len = 0;
        int wrd = 0;
        for(const auto& par : v.second) {
            if( par.first > prevNd) {
                countGood++;
                prevNd = par.first + par.second - 1;
                int fst = par.first;
                int lst = par.first + par.second - 1;
                len = accuLen[lst] - accuLen[fst];
                wrd = par.second;
            }
        }
        int novoLen = wrd;
        if( countGood > 1)
        {
            int save = (len - novoLen) * countGood;
            TRACE( cout << v.first << "/// save = " << save << endl; )
            res = min( res, tamanhoTotal - save);
        }
    }
    cout << res << endl;
    return 0;

}

