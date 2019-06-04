#include <bits/stdc++.h>

#define rep(i, a, b) for(int (i) = (a); (i) < (b); ++(i))
#define all(x) (x).begin(), (x).end()

using namespace std;

struct segment {
    int x, y1, y2;
    bool operator<( const segment& o ) const {
        if( o.x != x ) return x < o.x;
        return y1 < o.y1;
    }
    segment(int a, int b, int c) : x(a), y1(b), y2(c) {}
};

int main()
{
    ios::sync_with_stdio( false ); cin.tie( nullptr );
    int n;
    cin >> n;
    
    vector< segment > S;

    rep(i, 0, n) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        S.push_back( segment(a, b, d) );
        S.push_back( segment(c, b, d) );
    }

    sort( all(S) );


}
