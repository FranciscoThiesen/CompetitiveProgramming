#include <bits/stdc++.h>
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define all(v) (v).begin(), (v).end()
#define xablau ios::sync_with_stdio(0);cin.tie(0);


using namespace std;

using vi = vector<int>;
using ll = long long;
using vll = vector<long long>;


struct seg {
    int N;
    
    vi Tree, lazy;
    
    int id = 0, h;

    int combine(int a, int b) { return max( a, b ); }

    void modify(int& elem, int delta) { elem -= delta; }
    
    seg(int n) {
        N = n;
        Tree.assign(2 * N, 0);
        lazy.assign(2 * N, 0);
        h = sizeof(int) * 8 - __builtin_clz(N);
    }

    void apply(int p, int delta) {
        modify(Tree[p], delta);
        if(p < N) lazy[p] += delta;
    }

    void buildIt() {
        for(int i = N - 1; i > 0; --i) Tree[i] = combine(Tree[i << 1], Tree[i << 1 | 1] );
    }

    void build(int p) {
        int v = 0;
        while(p > 1) {
            p >>= 1;
            v = combine( Tree[p << 1], Tree[p << 1 | 1] );
            modify(v, lazy[p]);
            Tree[p] = v;
        }
    }
    
    void push(int p) {
        for(int s = h; s > 0; --s) {
            int i = p >> s;
            if(lazy[i] != 0) {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                lazy[i] = 0;
            }
        }
    }

    void update(int l, int r, int delta) {
        //printf("Update (%d, %d) -> delta = %d\n", l, r, delta);
        l += N, r += N;
        int l0 = l, r0 = r;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) apply(l++, delta);
            if(r & 1) apply(--r, delta);
        }
        build(l0); build(r0 - 1); 
    }

    int query(int l, int r) {
        l += N, r += N;
        push(l); push(l + 1); push(r - 1); push(r);
        int res = 0;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res = combine(res, Tree[l++]);
            if(r & 1) res = combine(res, Tree[--r]);
        }
        return res;
    }

    void printAllCandles() {
        for(int i = 0; i < N; ++i) printf("h[%d] = %d\n", i, Tree[N + i] );
        printf("\n\n");
    }
    
    bool doit(const int candleHeight) {
        //printf("Chamei doit, vamos imprimir o tamanho das velas\n"); 
        //printAllCandles();
        if(candleHeight > N) return false;
        // [0, candleHeight)
        int res = query(0, candleHeight ); // semi-open intervals
        
        //printf("Tamanho da maior vela viva no intervalo [%d, %d) = %d \n", 0, candleHeight, res);
        if( res == 0) return false; 
        
        push(candleHeight - 1);
    
        int pointVal = Tree[N + candleHeight - 1];
        if(pointVal == 0) return false;

        //printf("Valor do extremo do intervalo = %d\n", pointVal);

        int firstLeft = findLeftmost(pointVal, candleHeight - 1);
        int firstRight = findRightmost(pointVal, candleHeight - 1); 
        
        int takenCareOf = firstLeft;
        if(takenCareOf > 0) update(0, firstLeft, 1);
        //printf("firstLeft = %d, firstRight = %d\n", firstLeft, firstRight);
        int rem = candleHeight - takenCareOf;
     
        int rightEnd = firstRight + 1; // semiopen
        int leftEnd  = rightEnd - rem + 1;
        
        if(rem > 0) update(leftEnd - 1, rightEnd , 1);

        
        // vou retornar true, preciso imprimir todas as velas
        //printAllCandles();

        return true;
    }

    int findLeftmost(int wantedValue, int upperBound) {
        int lo = 0, hi = upperBound;
        while(lo < hi) {
            int mid = lo + (hi - lo) / 2;
            push(mid);
            if( Tree[mid + N] == wantedValue) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    int findRightmost(int wantedValue, int lowerBound) {
        
        int lo = lowerBound, hi = N - 1;
        
        while(lo < hi) {
            int mid = lo + (hi - lo + 1) / 2;
            push(mid);
            if( Tree[mid + N] == wantedValue) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
};



int main()
{
    xablau;
    int n, m;
    cin >> n >> m;
    seg arv(n);
    vi v(n);
    for(int& x : v) cin >> x;
    sort( v.rbegin(), v.rend() );
    for(int i = 0; i < n; ++i) arv.Tree[n + i] = v[i];
    arv.buildIt();
    int ans = 0;
    for(int i = 0; i < m; ++i) {
        int h;
        cin >> h;
        if( arv.doit(h) ) ++ans;
        else break;
    }
    cout << ans << endl;
    return 0;
}

