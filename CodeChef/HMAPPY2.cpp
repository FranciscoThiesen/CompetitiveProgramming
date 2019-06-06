#include <bits/stdc++.h>
#define TRACE(x) x
using namespace std;

int main()
{
    int t;
    cin >> t;
    while( t-- ) {
        long long n, a, b, k;
        cin >> n >> a >> b >> k;
        long long LCM = ( a / __gcd( a, b ) ) * b;
        long long ans = (n / a) + (n / b) - 2 * (n / LCM );
        if( ans >= k) cout << "Win" << endl;
        else cout << "Lose" << endl;
    }
    return 0;
}
