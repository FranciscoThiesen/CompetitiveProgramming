#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define all(v) (v).begin(), (v).end()

using ll = long long;
using vi = vector<int>;
using ordered_set = 
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

using xablau = ordered_set;

struct st 
{
    int n;
    vector< xablau > T;
    st(int _n) : n(_n) { T.resize(4 * n);} 
    
    void upd(int idx, int lo, int hi, int pos, int val, int chg) 
    {
        if(pos < lo || pos > hi) return;
        else
        {
            if( chg == 1) T[idx].insert( val );
            else T[idx].erase(val);
            if(lo != hi) {
                int mid = (lo + hi) >> 1;
                upd(2 * idx, lo, mid, pos, val, chg);
                upd(2 * idx + 1, mid + 1, hi, pos, val, chg);
            }
        }
    }
    
    int query(int idx, int lo, int hi, int left, int right, int val) 
    {
        if( right < lo || left > hi) return 0;
        if( lo >= left && hi <= right) return T[idx].order_of_key( val );
        int mid = (lo + hi) >> 1;
        return query(2 * idx, lo, mid, left, right, val) + 
               query(2 * idx + 1, mid + 1, hi, left, right, val);
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    st seg(n);
    vector<int> v(n); 
    iota(all(v), 0);
    
    for(int i = 0; i < n; ++i) seg.upd(1, 0, n - 1, i, i, 1);
    
    long long ans = 0; // pode ter overflow... resp max -> ~2* 10^10
    
    for(int i = 0; i < m; ++i) 
    {
        int x, y;
        cin >> x >> y;
        --x;--y;
        if(x != y) {
            if(x > y) swap(x, y);  
            seg.upd(1, 0, n - 1, x, v[x], -1);
            seg.upd(1, 0, n - 1, y, v[y], -1);
            if(y - x > 1) {
                int addX = seg.query(1, 0, n - 1, x + 1, y - 1, v[x]);
                int removeX = (y - 1) - ( x + 1) + 1;
                int removeY = seg.query(1, 0, n - 1, x + 1, y - 1, v[y]);
                int addY = (y - 1) - (x + 1 ) + 1;
                removeX -= addX;
                addY -= removeY;
                ans += ( - addX - addY + removeX + removeY);
            }
            ans += ( v[y] > v[x] ? 1 : -1);
            swap(v[x], v[y]);
            seg.upd(1, 0, n - 1, x, v[x], 1);
            seg.upd(1, 0, n - 1, y, v[y], 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
