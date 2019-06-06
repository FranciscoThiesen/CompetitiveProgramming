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
using pii = pair<int, int>;
constexpr int INF = 0x3f3f3f3f;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); 
    int n, m;
    cin >> n >> m;
    vi v(n);
    for(int& x : v) cin >> x;
    vector< pii > rg(m);
    for(auto& x : rg) cin >> x.first >> x.second;
    for(auto& x : rg) { x.first--; x.second--; } 
    int best = -1;
    vi xablau;
    
    rep(i, 0, n) {
        rep(j, 0, n) {
            int diff = v[i] - v[j];
            vi used;
            rep(x, 0, m) {
                if( i >= rg[x].first && i <= rg[x].second ) continue;
                else {
                    if( j >= rg[x].first && j <= rg[x].second ) {
                        used.emplace_back(x);
                        diff++;
                    }
                }
            }
            if( diff > best ) {
                best = diff;
                xablau = used;
            }
        }
    }
    cout << best << endl;
    cout << sz(xablau) << endl;
    for(int x : xablau) cout << x + 1 << " ";
    return 0;
}

