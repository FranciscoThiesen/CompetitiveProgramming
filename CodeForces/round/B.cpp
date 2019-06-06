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


inline ll lcm( ll a, ll b) {
    return ( (a / __gcd(a, b) ) * b );
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); 
    unordered_map<int, int> f;
    int n;
    cin >> n;
    vector<int> div(n);
    vector<bool> used(n, false);
    for(int& x : div) cin >> x;
    sort( div.rbegin(), div.rend() );
    
    int first = div[0];
    for(int i = 1; i < n; ++i) {
        if( div[i] == div[i - 1] ) {
            cout << first << " " << div[i] << endl;
            return 0;
        }
        else {
            if( first % div[i] != 0) {
                cout << first << " " << div[i] << endl;
                return 0;
            }
        }
    }

}

