#include <bits/stdc++.h>

using namespace std;

constexpr int ms = 5050;
constexpr int inf = 0x3f3f3f3f;

int dp[ms][ms][2];
vector< int > cc;
int len;

int main()
{
    ios::sync_with_stdio( false ); cin.tie(NULL);
    int n;
    cin >> n;
    
    vector<int> c(n);
    string s;
    cin >> s;
    for(int i = 0; i < n; ++i) c[i] = (s[i] - 'a');

    int cur = c[0];
    for(int i = 1; i < n; ++i) 
    {
        if( c[i] != c[i - 1] ) 
        {
            cc.emplace_back(cur);
            cur = c[i];
        }
    }
    
    cc.emplace_back( cur );

    len = (int) cc.size();
    
    for(int l = 1; l <= len; ++l) {
        for(int st = 0; st + l - 1 < len; ++st) {
            int nd = (st + l - 1);
            if( st == nd ) dp[st][nd][0] = dp[st][nd][1] = 0;
            else if( st == nd - 1) dp[st][nd][0] = dp[st][nd][1] = 1;
            else {
                // se o inicio e fim tem a mesma cor
                dp[st][nd][0] = dp[st][nd][1] = inf;
                if( cc[st] == cc[nd] ) {
                    dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd][0] + 1);
                    dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd][1] );
                    dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd - 1][0] + 1);
                    dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd - 1][1] + 1);
                    dp[st][nd][0] = min( dp[st][nd][0], dp[st][nd - 1][0] );
                    dp[st][nd][0] = min( dp[st][nd][0], dp[st][nd - 1][1] + 1);

                    dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd][0] + 1);
                    dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd][1] );
                    dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd - 1][0] + 1);
                    dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd - 1][1] + 1);
                    dp[st][nd][1] = min( dp[st][nd][1], dp[st][nd - 1][0] );
                    dp[st][nd][1] = min( dp[st][nd][1], dp[st][nd - 1][1] + 1);
                }
                else {
                	// se st e nd forem de cores diferentes
                	dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd][0] + 1);
                	dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd][1] + 1);
                	dp[st][nd][0] = min( dp[st][nd][0], dp[st][nd - 1][0] + 1);
                	dp[st][nd][0] = min( dp[st][nd][0], dp[st][nd - 1][1] + 1);

                	dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd][0] + 1);
                	dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd][1] + 1);
                	dp[st][nd][1] = min( dp[st][nd][1], dp[st][nd - 1][0] + 1);
                	dp[st][nd][1] = min( dp[st][nd][1], dp[st][nd - 1][1] + 1);

                }
            }
        }
    }

    cout << min( dp[0][len - 1][0], dp[0][len - 1][1] ) + 1 << endl;
    return 0;

}
