#include <bits/stdc++.h>

using namespace std;

constexpr long long mod = 7 + (1000ll * 1000ll * 1000ll );
constexpr int ms = 26;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    long long soma = 0;
    vector<long long> res(k, 0), seen(k, -1);
    for(int i = 0; i < (int) s.size(); ++i)  
    {
        char c = s[i];
        res[c - 'a'] = (1ll + soma) % mod;
        soma = 0;
        for(int j = 0; j < k; ++j) soma = ( soma + res[j]) % mod;
        seen[c - 'a'] = i;
    }
    for(int i = 0; i < n; ++i) 
    {
        int best = 0x3f3f3f3f;
        int idx = -1;
        for(int j = 0; j < k; ++j) 
        {
            if(seen[j] < best) 
            {
                best = seen[j];
                idx = j;
            } 
        }
        res[ idx ] = ( 1ll + soma ) % mod;
        soma = 0;
        for(int j = 0; j < k; ++j) soma = (soma + res[j] ) % mod;
        seen[idx] = i + (int) s.size();
    }
    cout << (soma + 1) % mod << endl;
    return 0;
}
