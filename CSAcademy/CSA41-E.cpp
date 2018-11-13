#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()

using namespace std;

int n, m;
vector<int> candleHeights, dailyDemand;


/* The following function will try to find the maximumFlow of a graph that has
 * a superSource, connected to all the n candleHeights with capacity = 
 * candleHeight[i] in every edge. Each node on the left side of the graph 
 * represent one of the candleHeight. And each node on the left side has edges
 * of capacity 1 going to every node on the right. This happens because each
 * candle can contribute only once to a daily candle demmand.
 * On the right we will have nodes representing all the days in the range 
 * [0, v). Each node x on the right side of the graph has an outgoing edge
 * going to the superSink of the graph, with capacity equal dailyDemand[x].
 *
 * We want to make sure that the maximum flow of the graph is equal to the sum
 * of all the dailyDemands from [0, v). If this happens, then there is a way
 * of satisfying all daily demands in that range. Since there is not a fast 
 * way of calculating the maximum flow for this graph, we will use the
 * Maximum-Flow x MinCut equivalence, and find the MinCut.
 */
bool f(int v)
{
    vector< int > demands(v);
    long long maxFlow = 0;
    
    for(int i = 0; i < v; ++i)
    {
        demands[i] = dailyDemand[i];
        maxFlow += dailyDemand[i];
    }
    
    // We will be sorting the demands to try to improve the cut in a greedy way
    sort( all( demands ) );
    
    /* 
     * Left Index value will be useful to check which edges connecting the 
     * left side of the graph to the superSource have been disconnected
     */

    int leftIdx = 0; 
    
    /*
     * s[0] = Cost of the edges of the left side that have been added to the cut
     * s[1] = Cost of the edges of the right side that have been added to the cut 
     * Initially, all edges of the right-side of the graph have been added to the
     * minCut. We will try to improve it!
     */

    array<long long, 2> s = { 0, maxFlow };
    
    long long minC = maxFlow;

    for(int i = v - 1; i >= 0; --i)
    {
        /* Right here, I am removing the most expensive edge on the right
         * side of the cut. This is basically connecting the i-th dailyDemand
         * to the superSink of the graph. So all candles that candles that are
         * being used to supply this demand, will have to be disconnected from
         * the superSource and the cost of this will be added later to the minCut.
         */
        
        s[1] -= demands[i]; // removing expensive edge of the rightSide of the graph from the cut 
        
        /* Now that we have connected dailyDemand[i] to the superSink. We will have to add all
         * the edges of capacity one that goes from the left side candles to the right side 
         * daily demands. But there is a catch! For some candle x, with candleHeight[x] = K, we have
         * two different possibilities. 
         * We can disconnect it from the superSource, and we will not have to pay for the (v - i) 
         * edges with capacity 1 that goes to the right side of the graph. Or we can pay (v - i) * 1 if
         * we keep it connected to the superSource. Since (v - i) only increases, we can guarantee that
         * if we disconnect some candle from the superSource at some moment, it will never be profitable
         * to connect it back to the superSource.
         *
         * I hope my explanation with sufficient for understanding the solution. If it was not, you can send
         * me a message and I will make some drawings in order to make illustrate the process.
         */
        while( leftIdx < n && candleHeights[leftIdx] < v - i)
        {
            /* Here, as pointed above, we will disconnect all candles from the superSource
             * That fit the criteria (candleHeight[x] < v - i )
             */
            s[0] += candleHeights[leftIdx++];
        }
        
        /* Now we know the total cost of the minCut. It is S[0] + S[1] +
         * ( |candles still connected to the superSource| * (|dailyDemands still connected to the superSink|)
         */
        minC = min( minC, 0LL + s[0] + s[1] + 1LL * ( v - i ) * ( n - leftIdx) ); 
    }
    
    // Here we are making sure that the minCut is equal to the sum of all the dailyDemands on the right side 
    // of the graph
    return (minC == maxFlow);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    candleHeights.resize(n); 
    dailyDemand.resize(m);
    
    for(int& x : candleHeights) cin >> x;
    for(int& x : dailyDemand) cin >> x;
    
    sort(all( candleHeights ) );
    
    /* It is not hard to prove that the problem is monotonic and we can binary
     * search it for finding the largest x, where f(x) is true.
     */
    int lo = 0, hi = m;
    while(lo < hi)
    {
        int mid = lo + (hi - lo + 1) / 2;
        if( f(mid) ) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << endl;
    
    return 0;

}
