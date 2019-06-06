#include <bits/stdc++.h>

using namespace std; 

#define TRACE(x...) x
#define PRINT(x...)
#define WATCH(x) TRACE(cout << #x << " = " << x << endl )

#define all(x) (x).begin(), (x).end()

long long solve(long long n, long long m) 
{
    long long mx = max(n, m);
    long long mn = min(n, m);
    vector<long long> phi(mx + 1);
    iota(all(phi), 0);
    for(long long i = mn + 1; i <= mx; ++i) phi[i] = mn; 

    for (long long p = 2; p <= mx; p++) { 
        if (phi[p] == p) { 
            phi[p] = p-1; 
            if(p <= mn) {
                for (long long i = 1LL * p * p; i <= mx; i += p) { 
                    // quantos caras vao deixar de ser coprimos porque sao multiplos de P
                    long long tira = min(i, mn) / p;
                    if( i % p == 0) ++tira;
                    phi[i] -= tira;
                    //phi[i] = (phi[i]/p) * (p-1); 
                } 
            }
        } 
    } 
    
    long long ans = 3;
    for(long long i = 2; i <= mx; ++i) {
        if( i <= mn ) ans += 2ll * phi[i];
        else ans += phi[i];
    }
    return ans;
} 
  
// Driver program to test above function 
int main() 
{ 
    ifstream in("rifleman.in");
    int n, m;
    in >> n >> m;
    ofstream out("rifleman.out");
    if(n == 1 && m == 1) out << 0 << endl;
    else if(n == 1 || m == 1) out << 1 << endl;
    else {
        --n;--m;  
        out << solve(n, m) << endl;
    }
    return 0; 
} 
