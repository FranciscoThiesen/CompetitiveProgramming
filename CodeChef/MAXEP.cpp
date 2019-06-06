#include <bits/stdc++.h>
using namespace std;
int main()
{
    int N, c;
    cin >> N >> c; 
    int cur = 1, result; 
    bool broken = false;
    int root = 388;
    int hi, lo;
    while( broken == false )
    {
        cout << "1 " << min(N, cur + root) << endl;
        cin >> result;
        if( result == 1 )
        {
            broken = true;
            cout << 2 << endl;
            hi = min(N, cur + root) - 1;
            lo = cur; 
        }
        else cur = min(N, cur + root);
    }
    if( lo == hi )
    {
        cout << "3 " << lo << endl;
        return 0;
    }
    for(int i = lo; i <= min(hi, N); ++i)
    {
        if( i == hi )
        {
            cout << "3 " << i << endl;
            return 0;
        }
        cout << "1 " << i << endl;
        cin >> result;
        if( result == 1 )
        {
            cout << 2 << endl;
            cout << "3 " << i << endl;
            return 0;
        }

    }
    return 0;
}
