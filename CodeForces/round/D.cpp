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

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); 
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    auto getC = [&] (char c1, char c2 ) {
        string s = "RGB";
        for(const char& c : s) {
            if( c != c1 && c != c2 ) {
                return c;
            }
        }
        return 'X';
    };
    
    int ans = INF;
    string xablau;
    auto calcCost = [&] ( char start ) {
        string x;
        x += start;
        int custo = ( start != s[0] ) ? 1 : 0;
        for(int i = 1; i < n; ++i ) {
            if( x.back() == s[i] ) {
                if( i + 1 < n ) {
                    x += getC( s[i + 1], x.back() );
                }
                else {
                    x += getC( x.back(), x.back() );
                }
                ++custo;
            }
            else x += s[i];
        }
        if( custo < ans ) {
            ans = custo;
            xablau = x;
        }
    };
    calcCost('R'); calcCost('G'); calcCost('B');

    cout << ans << endl << xablau << endl;
}
