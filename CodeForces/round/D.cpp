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
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define funoredered_map __fast_unordered_map

template<class Key, class Value, class Hash = std::hash<Key>>
using funordered_map = __gnu_pbds::gp_hash_table<Key, Value, Hash>;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int inf = 0x3f3f3f3f;
constexpr double EPS = 1e-8;
constexpr ll  MOD = 998244353LL;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// online for debugging pairs with modern cpp ( >= 17 )
ostream &operator<<(ostream& os, const pair<auto, auto>& p) {
    return os << "(" << p.first << "," << p.second << ")";
}

inline ll powmod( ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1) {
        if(b&1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}

inline int cmp_double( double x, double y, double tol = EPS) {
    return (x <= y + tol) ? ( x + tol < y) ? -1 : 0 : 1;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll fat(ll n) {
    if(n <= 1) return 1LL;
    return n * fat(n - 1);
}

ll X( ll n )
{
    vector<int> v(n, 0);
    iota(all(v), 1);
    vector<int> tudo;
    map<deque<int>, int> f;
    do {
        copy( all(v), back_inserter(tudo) );
    } while( next_permutation(all(v) ) );

    // agora vou fazer sliding windonw
    long long target = (n * (n + 1) ) / 2LL;
    long long curSum = 0LL;
    ll c = 0;
    ll pos = 0;
    deque<int> cc;
    map<int, int> sick;
    for(int i = 0; i < sz(tudo); ++i) {
        curSum += tudo[i];
        cc.push_back(tudo[i]); 
        if(i >= n) {
            curSum -= tudo[i - n]; 
            cc.pop_front();
        }
        if(i >= n - 1 && curSum == target) ++c;
        //if(i >= n - 1) f[curSum]++, ++pos;
        if(i >= n - 1 && curSum == target) {
            f[cc] += 1;
        }
    }
    TRACE( 
            for(auto& v : f) {
                //for(auto& x : v.first) cout << x << " ";
                //cout << " = " << v.second << endl;
                sick[v.second]++;
            }
    )
    for(const auto& elem : sick) {
        cout << " temos um total de " << elem.second << " tuplas boas que aparecem " << elem.first << " vezes " << endl; 
    }
    //TRACE( cout << " possible = " << pos << endl; )
    return c;

}

long long count(ll n) {
    long long soma = n;
    long long multiplica = n - 2;
    long long curVal = 2;
    long long soma1 = n;
    while( curVal <= n - 1) {
        long long nxtQnd = (soma1 * multiplica) % MOD;
        soma = (soma + ( (curVal * nxtQnd) % MOD) ) % MOD; 
        soma1 = ( soma1 + nxtQnd) % MOD;
        multiplica--;
        curVal++;
    }
    return soma;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(NULL);
    //ll n;
    //cin >> n;
    for(int i = 1; i <= 8; ++i) {
        X(i);
    }
    //cout << count(n) << endl;
    
    return 0;
}

