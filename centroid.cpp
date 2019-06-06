#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <utility>

using namespace std;

#define rep(i, a, b) for(int (i) = (a); (i) < (b); ++(i))
#define mp make_pair
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define sz(x) (x).size()

using vi = vector<int>;
using ll = long long;
using vll = vector<ll>
using pii = pair<int, int>;

struct centroid_decomposition {
    int N;
    vector< vi > centroid_graph;
    deque<bool> visited;
    deque<bool> dirty;
    vi subtree_size;

    centroid_decomposition( const vector< vi >& graph ) {
        N = sz(graph);
        G.resize(N);
        visited.assign( N, false );
        dirty.assign(N, false );
        subtree_size.assign(N, 0);
    };
    
    int centroid(int loc, vector<vi>& graph ) {
        for(const int& nei : graph[loc] ) {
            if( subtree_size[nei] > ( N / 2 ) ) {
                return centroid(nei);
            }
        }
        return loc;
    }
    



};

int main()
{

}
