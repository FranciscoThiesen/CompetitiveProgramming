#include <bits/stdc++.h>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define rep(i, a, b) for(int (i) = (a); (i) < (b); ++(i))
#define rp(i,n) rep(i,0,n)

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;

struct flight {
    int arrive_date, source, destination, price;
    bool operator<( const flight& o) const {
        return arrive_date < o.arrive_date;
    };
    flight(int a, int b, int c, int d) : arrive_date(a), source(b), destination(c), price(d) {}
};

constexpr ll linf = 0x3f3f3f3f3f3f3fLL;
constexpr int max_date = 1e6 + 13;

int main() 
{
    ios::sync_with_stdio( false ); cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector< flight > F;
    
    rp(i, m) 
    {
        int d, f, t, c;
        cin >> d >> f >> t >> c;
        F.push_back( flight(d, f, t, c) );
    }
    
    sort( all(F) );
    
    vll best_forward_cost_per_jury(n + 1, linf);
    vll best_backward_cost_per_jury(n + 1, linf);
    
    ll current_cost = 0LL;
    set< int > present_jury;
    // Vamos calcular o custo de ter todos os jurados em uma cidade antes de determinado dia
    vll best_forward_cost(max_date, linf );
    ll total_cost = 0;
    rp(i, m) {
        if( F[i].destination != 0) continue;
        else {
            if( present_jury.find(F[i].source) != present_jury.end() ) {
                if( best_forward_cost_per_jury[ F[i].source ] > F[i].price ) {
                    total_cost -= ( best_forward_cost_per_jury[ F[i].source] - F[i].price );
                    best_forward_cost_per_jury[ F[i].source] = F[i].price;
                }
            }
            else
            {
                present_jury.insert( F[i].source );
                best_forward_cost_per_jury[ F[i].source ] = F[i].price;
                total_cost += F[i].price;
            }
            if( (int) present_jury.size() == n ) best_forward_cost[ F[i].arrive_date + 1] = total_cost;
        }
    }
    rep(i, 1, max_date) best_forward_cost[i] = min( best_forward_cost[i], best_forward_cost[i - 1] );
    present_jury.clear();
    total_cost = 0LL;
    // lidando com os voos de volta
    vll best_backward_cost( max_date, linf );
    for(int i = m - 1; i >= 0; --i)
    {
        if( F[i].destination == 0) continue;
        else {
            if( present_jury.find( F[i].destination ) != present_jury.end() ) {
                if( best_backward_cost_per_jury[ F[i].destination ] > F[i].price ) {
                    total_cost -= ( best_backward_cost_per_jury[ F[i].destination ] - F[i].price );
                    best_backward_cost_per_jury[ F[i].destination ] = F[i].price;
                }
            }
            else {
                present_jury.insert( F[i].destination );
                best_backward_cost_per_jury[ F[i].destination ] = F[i].price;
                total_cost += F[i].price;
            }
            if( (int) present_jury.size() == n ) best_backward_cost[ F[i].arrive_date ] = total_cost;
        }
    }
    for(int i = max_date - 10; i >= 0; --i) best_backward_cost[i] = min( best_backward_cost[i], best_backward_cost[i + 1] );
    
    bool found_ans = false;
    long long best = linf;
    
    for(int i = 1; i + k < max_date; ++i)
    {
        long long cost = best_forward_cost[i] + best_backward_cost[i + k];
        if( best_forward_cost[i] != linf && best_backward_cost[i + k] != linf ) {
            best = min( best, cost );
            found_ans = true;
        }
    }
    if( found_ans ) cout << best << endl;
    else cout << -1 << endl;
}
