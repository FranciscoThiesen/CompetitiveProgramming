#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    ios::sync_with_stdio( false ); cin.tie(NULL);
    cin >> t;
    while( t-- ) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for(int& x : a) cin >> x;
        for(int& x : b) cin >> x;
        int best = -1;
        for(int i = 0; i < n; ++i) {
            int nxt = (i + 1) % n;
            int ant = (i - 1 + n ) % n;
            if( b[i] > a[nxt] + a[ant] ) {
                best = max( best, b[i] );
            }
        }
        cout << best << endl;
    }
    return 0;
}
