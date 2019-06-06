#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()

using namespace std;

using vi = vector<int>;

int main()
{
    ios::sync_with_stdio( false ); cin.tie(NULL);
    int t;
    cin >> t;
    while( t-- ) {
        string s;
        cin >> s;
        int len = (int) s.size();
        vector<int> freq(26, 0);
        for(const char& c : s) freq[ c - 'A' ]++;
        sort( freq.rbegin(), freq.rend() );
        for(int diff = 1; diff <= 26; ++diff) {
            if( len % diff ) continue;
            int each = len / diff;
            vector<int> good;
            for(const int& x : freq) good.push_back( each - x);
            sort( good.begin(), good.end(), [] (const int& a, const int& b) {
                return abs(a) < abs(b);        
            });
            int cost = 0;
        }
    }
    return 0;
}
