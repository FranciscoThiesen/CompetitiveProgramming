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
constexpr ll MOD = 1000000007LL;

template <typename T>
using ordered_set = 
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

ostream &operator<<(ostream& os, const pair<auto, auto>& p) {
    return os << "(" << p.first << "," << p.second << ")";
}

inline ll modPow( ll a, ll b, ll mod = MOD) {
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

void pri(const int a, const int b, const int c) { cout << "1 " << a << " " << b << " " << c << endl; }

void solve(vector<int>& ans, int st, int nd)
{
    if( nd - st + 1 == 4)
    {
        array<int, 4> res;
        pri(st, st + 1, st + 2);
        cin >> res[0];
        pri(st, st + 1, st + 3);
        cin >> res[1];
        pri(st + 1, st + 2, st + 3);
        cin >> res[2];
        pri(st, st + 2, st + 3);
        cin >> res[3];
        int threeXorFor = res[0] ^ res[1];
        ans[st] = res[3] ^ threeXorFor;
        ans[st + 1] = res[2] ^ threeXorFor;
        ans[st + 2] = res[0] ^ ans[st] ^ ans[st + 1];
        ans[st + 3] = res[3] ^ ans[st] ^ ans[st + 2];
    }
    else if( nd - st + 1 == 5)
    {
        array<int, 5> res;
        pri(st, st + 1, st + 2);
        cin >> res[0];
        pri(st, st + 3, st + 4);
        cin >> res[1];
        pri(st + 1 , st + 3, st + 4);
        cin >> res[2];
        pri(st, st + 2, st + 4);
        cin >> res[3];
        pri(st + 1, st + 2, st + 3);
        cin >> res[4];
        int oneXorTwo = res[1] ^ res[2];
        ans[st + 2] = res[0] ^ oneXorTwo;
        int oneXorFive = res[3] ^ ans[st + 2];
        ans[st + 3] = res[1] ^ oneXorFive;
        ans[st + 1] = res[4] ^ ( ans[st + 2] ^ ans[st + 3]);
        ans[st] = res[0] ^ ( ans[st + 2] ^ ans[st + 1]);
        ans[st + 4] = res[1] ^ ( ans[st] ^ ans[st + 3]);
    }
    else
    {
        array<int, 6> res; 
        pri(st, st + 1, st + 2);
        cin >> res[0];
        pri(st, st + 1, st + 3);
        cin >> res[1];
        pri(st + 1, st + 4, st + 5);
        cin >> res[2];
        pri(st, st + 4, st + 5);
        cin >> res[3];
        int oneXorTwo = res[2] ^ res[3];
        ans[st + 2] = res[0] ^ oneXorTwo;
        ans[st + 3] = res[1] ^ oneXorTwo;
        pri(st + 2, st + 3, st + 4);
        cin >> res[4];
        ans[st + 4] = res[4] ^ res[0] ^ res[1];
        pri(st + 2, st + 3, st + 5);
        cin >> res[5];
        ans[st + 5] = res[5] ^ ans[st + 2] ^ ans[st + 3];
        ans[st] = res[3] ^ ans[st + 4] ^ ans[st + 5];
        ans[st + 1] = res[2] ^ ans[st + 4] ^ ans[st + 5];
    }
}

int main()
{
    int t;
    cin >> t;
    rep(i, 0, t)
    {
        int n;
        cin >> n;
        vector<int> val(n + 1);
        int globalSt = 1;
        int rem = n;
        while( globalSt < n )
        {
            if( rem % 2)
            {
                solve(val, globalSt, globalSt + 4);
                globalSt += 5;
                rem -= 5;
            }
            else
            {
                if( rem % 4 == 2) 
                {
                    solve(val, globalSt, globalSt + 5);
                    globalSt += 6;
                    rem -= 6;
                }
                else
                {
                    solve(val, globalSt, globalSt + 3);
                    globalSt += 4;
                    rem -= 4;
                }
            }
        }
        cout << "2 ";
        rep(i, 1, n + 1) cout << val[i] << " ";
        cout << endl;
        int res;
        cin >> res;
    }
    return 0;
}

