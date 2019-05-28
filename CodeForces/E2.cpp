#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define rall(v) (v).rbegin(), (v).rend()
#define rep(i, a, b) for(int (i) = (a); (i) < (b); ++(i))

using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

// Foi testado para o seguinte problema ( https://codeforces.com/contest/52/problem/C )
template <typename T>
struct SegmentTree {
    vector<T> tree, lazy;
    T id;
    T neutral;
    int n;
    SegmentTree(int _n, T _id, T _neutral) : n(_n), id(_id), neutral(_neutral) {
        tree.assign(4*n, id);
        lazy.assign(4*n, neutral); // it is not necessary for the leaves.. should decrease this array size
    }

    // This must change accodingly to the problem
    T combine( const T& a, const T& b) { return min(a, b); }
    
    inline void buildTree( vector<T>& src, int idx, int l, int r) {
        if(l == r) tree[idx] = src[l];
        else {
            int mid = (l + r)/2;
            buildTree( src, 2 * idx, l, mid);
            buildTree( src, 2 * idx + 1, mid + 1, r);
            tree[idx] = combine( tree[2*idx], tree[2*idx + 1] ); 
        }
    }
    
    void push(int idx) {
        tree[2 * idx] -= lazy[idx];
        tree[2* idx + 1] -= lazy[idx];
        lazy[2 * idx] += lazy[idx];
        lazy[2 * idx + 1] += lazy[idx];
        lazy[idx] = 0;
    }
    
    void update(int idx, int tl, int tr, int l, int r, T delta) {
        if(l > r) return;
        if(tl == l && tr == r) {
            tree[idx] += delta;
            lazy[idx] += delta;
        }
        else {
            push(idx);
            int tm = (tl + tr) / 2;
            update( idx * 2, tl, tm, l, min(r, tm), delta);
            update( idx * 2 + 1, tm + 1, tr, max(l, tm + 1), r, delta);
            tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1] );
        }
    }

    T query(int idx, int tl, int tr, int l, int r) {
        if(l > r) return id;
        if(l <= tl && tr <= r) return tree[idx];
        push(idx);
        int tm = (tl + tr) / 2;
        return combine( query( idx * 2, tl, tm, l, min(r, tm) ),
                        query( idx*2 + 1, tm + 1, tr, max(l, tm + 1), r) );
    }
};

constexpr int ms = 1e5 + 13;
constexpr int lg = 18;

int sparse_table[ms][lg];
int pre[ms];

void fill_table(const vector<int>& v) {
    pre[1] = 0;
    for(int i = 2; i < ms; ++i) pre[i] = pre[i / 2] + 1;
    int len = (int) v.size();
    for(int i = 0; i < ms; ++i) for(int L = 0; L < lg; ++L) sparse_table[i][L] = 0x3f3f3f3f;
    for(int i = 0; i < len; ++i) sparse_table[i][0] = v[i];
    for(int L = 1; L < lg; ++L) {
        for(int i = 0; i + (1<<L) <= len; ++i) {
            sparse_table[i][L] = max( sparse_table[i][L - 1], sparse_table[i + (1 << (L - 1) )][L - 1] );
        }
    }
}

int max_in_range(int L, int R) {
    int j = pre[R - L + 1];
    return max( sparse_table[L][j], sparse_table[R - (1 << j) + 1][j] ); 
}

int main()
{
    ios::sync_with_stdio( false ); cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<int> vec(n);
    for(int& x : vec) cin >> x;

    fill_table( vec );

    SegmentTree< int > seg(n, 0x3f3f3f3f, 0);
    
    seg.buildTree(vec, 1, 0, n - 1);

    vector< pii > upd(q);
    for(auto& u : upd) cin >> u.first >> u.second;
    for(auto& u : upd) { u.first--; u.second--; }
    
    sort( upd.begin(), upd.end(), [&] ( const pii& a, const pii& b) {
            return a.second < b.second;
            });


    int best = -1;

    for(const auto& u : upd) {
        seg.update(1, 0, n - 1, u.first, u.second, 1);
        int sm = seg.query(1, 0, n - 1, 0, )
    }

}
