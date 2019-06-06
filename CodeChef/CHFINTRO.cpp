#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, r;
    cin >> n >> r;
    for(int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        cout << ( x < r ? "Bad boi" : "Good boi") << endl;
    }
    return 0;
}
