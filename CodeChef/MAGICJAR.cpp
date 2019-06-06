#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()

using namespace std;

int main()
{
    ios::sync_with_stdio( false );
    cin.tie(NULL);
    int t;
    cin >> t;
    while( t-- ) {
        int n;
        cin >> n;
        vector<long long> v(n);
        long long ans = 0;
        for(auto& x : v) {
            cin >> x;
            ans += ( x - 1);
        }
        long long acc = 0;
        sort( all(v) );
        for(auto& x : v) {
            if( acc == 0) {
                ++ans;
                acc = 1;
            }
        }
        cout << ans << endl; 
    }
    return 0;
}
