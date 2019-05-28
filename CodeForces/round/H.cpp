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
    for(int& x : c) cin >> x;

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

    for(int l = 1; l <= len; ++l) 
    {
        for(int st = 0; st + l - 1 < len; ++st)
        {
            int nd = st + l - 1;
            dp[st][nd][0] = dp[st][nd][1] = inf;
            if( st == nd ) dp[st][nd][0] = dp[st][nd][1] = 0;
            else if( st == nd - 1) 
            {
                dp[st][nd][0] = dp[st][nd][1] = 1;
            }
            else
            {
                // b == 0
                if( cc[st] == cc[nd] ) 
                {
                    if( cc[st] == cc[st + 1] ) 
                    {
                        dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd - 1][0] ); 
                    }
                    if( cc[st] == cc[nd - 1] ) 
                    {
                        dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd - 1][1] );
                    }
                    dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd - 1][0] + 1);
                    dp[st][nd][0] = min( dp[st][nd][0], dp[st + 1][nd - 1][1] + 1);
                }
                else
                {
                    if( cc[st] == cc[st + 1] ) 
                    {
                        dp[st][nd][0] = min( dp[st + 1][nd][0], dp[st][nd][0] );
                    }
                    if( cc[st] == cc[nd - 1] )
                    {
                        dp[st][nd][0] = min( dp[st][nd - 1][1] + 1, dp[st][nd][0] );
                    }
                }
                
                dp[st][nd][0] = min( dp[st + 1][nd][1] + 1, dp[st][nd][0]);
                dp[st][nd][0] = min( dp[st + 1][nd][0] + 1, dp[st][nd][0]);
                dp[st][nd][0] = min( dp[st][nd][0], dp[st][nd - 1][0] + 1);
                dp[st][nd][0] = min( dp[st][nd][0], dp[st][nd - 1][1] + 1); // thats all folks for b == 0
            
                // b == 1
                if( cc[st] == cc[nd] )
                {
                    if( cc[nd] == cc[st + 1] )
                    {
                        dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd - 1][0] );
                    }
                    if( cc[nd] == cc[nd - 1] ) 
                    {
                        dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd - 1][1] );
                    }
                    dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd - 1][0] + 1 );
                    dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd - 1][1] + 1 );
                }
                else
                {
                    if( cc[nd] == cc[st + 1] )
                    {
                        dp[st][nd][1] = min( dp[st][nd][1], dp[st + 1][nd][0] + 1);
                    }
                    if( cc[nd] == cc[nd - 1] )
                    {
                        dp[st][nd][1] = min( dp[st][nd][1], dp[st][nd - 1][1] );
                    }
                }
                
                dp[st][nd][1] = min( dp[st + 1][nd][1] + 1, dp[st][nd][1]);
                dp[st][nd][1] = min( dp[st + 1][nd][0] + 1, dp[st][nd][1]);
                dp[st][nd][1] = min( dp[st][nd][1], dp[st][nd - 1][0] + 1);
                dp[st][nd][1] = min( dp[st][nd][1], dp[st][nd - 1][1] + 1); // thats all folks for b == 0
            
            }
        }
    }
    
    /*for(int i = 0; i < len; ++i) {
        for(int j = i; j < len; ++j) {
            for(int b = 0; b < 2; ++b) {
                printf("dp[%d][%d][%d] = %d  ", i, j, b, dp[i][j][b] );
            }
            puts("");
        }
        puts("\n");
    }*/

    cout << min( dp[0][len - 1][0], dp[0][len - 1][1] ) << endl;
    return 0;

}
