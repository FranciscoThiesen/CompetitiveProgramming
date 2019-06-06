#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i) )
#define all(v) (v).begin(), (v).end()
#define fast ios::sync_with_stdio(0);cin.tie(0);

using vi = vector<int>;
using ll = long long;
using vll = vector<ll>;

struct node {
    int value;
    node(int v = 0) : value(v) {}
};

// Intervals are [l, r)

struct seg {
    int N;
    vector<node> Tree;
    vector<int> lazy;
    node identity = node(0);
    int height;
    
    node combine(const node& a, const node& b) { return node( min(a.value, b.value) ); }
    
    void modify(node& a, int delta) { a.value -= delta; }
    
    seg(int n) : N(n) {
        Tree.assign(2 * N, identity);
        lazy.assign(2 * N, 0);
        h = sizeof(int) * 8 - __builtin_clz(N);
    }
    
    void apply(int p, int delta) {
        modify(Tree[position], delta);
        // if is not a leaf
        if(p < N) lazy[p] += value;
    }
    
    void buildIt() {
        for(int i = N - 1; i > 0; --i) Tree[i] = combine(Tree[ i << 1], Tree[ i << 1 | 1] ); 
    }
    
    void build(int p) {
        node tmp;
        while(p > 1) {
            p >>= 1;
            tmp = combine(Tree[ p << 1], Tree[p << 1 | 1] );
            modify(tmp, lazy[p]);
            Tree[p] = tmp;
        }
    }
    void push(int p) {
        for(int s = h; s > 0; --s) {
            int i = p >> s;
            if(lazy[i] != 0) {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                lazy[i] = 0;
            }
        }
    }

    void update(int l, int r, int value) {
        l += N, r += N;
        int l0 = l, r0 = r;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) apply(l++, value);
            if(r & 1) apply(--r, value);
        }
        build(l0);
        build(r0);
    }
    
    int query(int l, int r) {
        l += N, r += N;
        push(l);
        push(r);
        node res = id;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res = combine(res, Tree[++l]);
            if(r & 1) res = combine(res, Tree[--r]);
        }
        return res.value;
    }
    
    bool canDoit(int numberOfCandles) {
        if(numberOfCandles > N) return false;
        
    }
}


int main()
{
    fast;
    int n, m;
    cin >> n >> m;
    seg arv( n );
    vector<int> c(m);
    rep(i, 0, n) cin >> arv.Tree[i + n];
    for(int& x : c) cin >> x;
     


}
