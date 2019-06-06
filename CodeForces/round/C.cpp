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

#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))

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

constexpr int INF = 0x3f3f3f3f;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int mat[3][3];

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); 
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    unordered_map<char, int> memo;
    memo['R'] = 0;
    memo['G'] = 1;
    memo['B'] = 2;
    
    for(int i = 0; i < n; ++i) {
        mat[ memo[ s[i] ] ][ i % 3 ]++;
    }
    
    int ans = INF;
    string best;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            for(int k = 0; k < 3; ++k) {
                if( i == j || i == k || j == k) continue;
                int cost = n;
                cost -= mat[0][i];
                cost -= mat[1][j];
                cost -= mat[2][k];

                if( cost < ans ) {
                    string go;
                    for(int x = 0; x < n; ++x) {
                        if(( x % 3 ) == i ) go += "R";
                        else if( ( x % 3 ) == j) go += "G";
                        else go += "B";
                    }
                    ans = cost;
                    best = go;
                }
            }
        }
    }
    cout << ans << endl << best << endl;
    
}

