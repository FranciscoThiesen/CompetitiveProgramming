#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream in("elevator.in");
    long long N, C, P, T;
    in >> N >> C >> P >> T;
    vector<long long> V(N);
    for(auto& x : V) in >> x; 

    long long ans = 0LL;
    for(int i = 0; i < N; ++i) {
        if(2LL * (i + 1LL) <= T) ans += V[i];
    }

    ofstream out("elevator.out");
    out << ans << endl;
}
