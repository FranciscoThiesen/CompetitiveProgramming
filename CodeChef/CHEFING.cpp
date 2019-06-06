#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> t;
    while( t-- ) {
        int n; cin >> n;
        vector<int> globalFreq(26, 0);
        for(int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            sort( s.begin(), s.end() );
            s.erase( unique( s.begin(), s.end() ), s.end() );
            for(const char c : s) globalFreq[ c - 'a' ]++;
        }
        int c = 0;
        for(int& x : globalFreq ) if( x == n) ++c;
        cout << c << endl;
    }
    return 0;
}
