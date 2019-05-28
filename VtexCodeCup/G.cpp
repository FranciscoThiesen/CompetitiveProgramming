#include <bits/stdc++.h>

using namespace std;

// Debugging macros 
#define TRACE(x) x
#define WATCH(x) TRACE( cout << #x" = " << x << endl)
#define PRINT(x) TRACE(printf(x))
#define WATCHR(a, b) TRACE( for(auto c = a; c != b;) cout << *(c++) << " "; cout << endl)
#define WATCHC(V) TRACE({cout << #V" = "; WATCHR(V.begin(), V.end()); } )
// End of Debugging macros 

// Macros for faster typing
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) (int) (v).size()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define pb push_back

using ll = long long;
using vi = vector<int>;
using pii = pair<ll, ll>;
// End of macros for faster typing

constexpr int inf = 0x3f3f3f3f;
constexpr ll MOD = 1000000007LL;
constexpr double tol = 1e-8;

inline ll powmod( ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1) {
        if(b&1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(0);cin.tie(NULL);
    long long n, k;
    cin >> n >> k;
    vector<ll> A(n);
    vector< pii > clients;
    rep(i, 0, n) {
        ll a, b;
        cin >> a >> b;
        A[i] = b;
        clients.emplace_back(a, i);
    }
    vector< pair< char, long long > > resp(n);
    sort( all(clients) );
    ll alberto_free = 0;
    ll bernardo_free = 0;
    queue< pii > alberto_queue;
    queue< pii > bernardo_queue;
    int aq_len = 0, bq_len = 0;

    for(const auto& v : clients ) {
        ll idx = v.second;
        ll T = v.first;
        while(!alberto_queue.empty() ) {
            auto f = alberto_queue.front();
            if(f.second <= T) {
                alberto_queue.pop();
                aq_len--;
            }
            else break; 
        }
        while(!bernardo_queue.empty() ) {
            auto f = bernardo_queue.front();
            if( f.second <= T) {
                bernardo_queue.pop();
                bq_len--;
            }
            else break;
        }
        if( aq_len <= bq_len ) {
            // Goes to alberto
            alberto_free = max( alberto_free, T );
            alberto_queue.emplace( alberto_free, alberto_free + A[idx] );
            aq_len++;
            alberto_free += A[idx];
            resp[idx] = make_pair('A', alberto_free);
        }
        else {
            bernardo_free = max( bernardo_free, T);
            bernardo_queue.emplace( bernardo_free, bernardo_free + k * A[idx] );
            bq_len++;
            bernardo_free += (k * A[idx]);
            resp[idx] = make_pair('B', bernardo_free);
        }
    }
    for(const auto& v : resp) cout << v.first << " " << v.second << endl;

    return 0;
}

