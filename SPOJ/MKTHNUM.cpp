#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(), (v).end()
#define sz(v) (int) (v).size()
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

struct MergeST 
{
    int n;
    vector< vi > tree;
        MergeST( int _n) : n(_n) { tree.resize(4 * n ); }
    
    void combine( vi& pai, vi& filhoA, vi& filhoB) 
    {
        merge( all(filhoA), all(filhoB), back_inserter(pai) );
    }
    
    void build(vector< pii >& v, int idx, int lo, int hi) 
    {
        if(lo == hi) tree[idx].push_back(v[lo].second);
        else 
        {
            int mid = (lo + hi) / 2;
            build(v, 2*idx, lo, mid); 
            build(v, 2*idx + 1, mid + 1, hi);
            combine( tree[idx], tree[2 * idx], tree[2 * idx + 1] );
        }
    }

    int query(int idx, int lo, int hi, int qLo, int qHi, int kth) 
    {
        if(lo == hi) return tree[idx][0];
        int mid = (lo + hi) / 2;
        int qtd = upper_bound(all(tree[2 * idx]), qHi) - lower_bound(all(tree[2 * idx]), qLo);
        if( qtd < kth) return query( 2 * idx + 1, mid + 1, hi, qLo, qHi, kth - qtd);
        else return query(2 * idx, lo, mid, qLo, qHi, kth); 
    }

};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q; 
    
    vector<pii> v(n);
    vi orig(n);
    
    for(int i = 0; i < n; ++i) 
    {
        cin >> v[i].first;
        v[i].second = i;
        orig[i] = v[i].first;
    }

    MergeST arv( n );
    
    sort(all(v) );
    
    arv.build(v, 1, 0, n - 1);

    for(int i = 0; i < q; ++i) 
    {
        int x, y, z;
        cin >> x >> y >> z;
        --x;--y;
        auto idx = arv.query(1, 0, n - 1, x, y, z);
        cout << orig[idx] << endl;
    }

    return 0;
}

