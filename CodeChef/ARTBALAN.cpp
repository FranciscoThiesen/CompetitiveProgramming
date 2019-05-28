#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define sz(x) (int) (x).size()
#define all(v) (v).begin(), (v).end()

int main()
{
    ios::sync_with_stdio( false ); cin.tie(NULL);
    int t;
    cin >> t;
    while( t-- ) 
    {
        string s;
        cin >> s;
        int len = sz(s);
        
        vector<int> freq(26, 0);
        for(const char& c : s) freq[c - 'A'] += 1;
        sort( all(freq) );

        int ans = 0x3f3f3f3f;
        for(int distinct_chars = 1; distinct_chars <= 26; ++distinct_chars ) {
            if( len % distinct_chars ) continue;
            
            int single_freq = len / distinct_chars;
            
            vector<int> non_negative, negative;
            
            for( const int& f : freq ) {
                if( f >= single_freq ) non_negative.push_back( f - single_freq );
                else negative.push_back( single_freq - f );
            }
            
            sort( all(non_negative) ); sort( all( negative ) );
            
            int tamPos = sz(non_negative), tamNeg = sz(negative);
            for(int qntPos = 0; qntPos <= distinct_chars; ++qntPos) {
                if( qntPos > tamPos ) continue;
                if( distinct_chars - qntPos > tamNeg) continue;
                int cost = 0;
                int praDoar = 0;
                for(int i = 0; i < qntPos; ++i) cost += non_negative[i];
                
                praDoar = cost;
                for(int i = 0; i < distinct_chars - qntPos; ++i) {
                    int ker = negative[i];
                    if( praDoar >= ker ) {
                        praDoar -= ker;
                    }
                    else {
                        int inc = ker - praDoar;
                        praDoar = 0;
                        cost += inc;
                    }
                }
                ans = min( ans, cost );
            }
        }
        cout << ans << endl; 
    }
    return 0;
}
