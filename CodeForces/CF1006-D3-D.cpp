#include <bits/stdc++.h>
#define sz(x) (int) (x).size()
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    int ans = 0;
    for(int i = 0; i < n / 2; ++i)
    {
        map<char, int> f;
        f[a[i]]++;
        f[a[n - i - 1] ]++;
        f[b[i]]++;
        f[b[n - i - 1] ]++;

        if( sz(f) == 4) ans += 2;
        else if(sz(f) == 3) ans += (a[i] == a[n - i - 1]) + 1;
        else if(sz(f) == 2) ans += (f[a[i]] != 2);
    }
    if(n & 1) ans += (a[n / 2] != b[n / 2]);
    cout << ans << endl;
    return 0;
}
