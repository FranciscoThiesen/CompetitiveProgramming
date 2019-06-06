#include <bits/stdc++.h>
using namespace std;
 
#define all(x) (x).begin(), (x).end()
 
#define TRACE(x) x
#define WATCH(x) TRACE(cout << #x" = " << x << endl)
#define PRINT(x...) TRACE(printf(x))
#define WATCHR(a, b) TRACE(for (auto c=a; c!=b;) cout << *(c++) << " "; cout << endl)
#define WATCHC(V) TRACE({cout << #V" = "; WATCHR(V.begin(), V.end());})
 
#define FU(i, a, b) for (auto i = a; i < b; ++i)
#define fu(i, b) FU(i, 0, b)
#define FD(i, a, b) for (auto i = (b) - 1; i >= a; --i)
#define fd(i, b) FD(i, 0, b)
 
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vd = vector<double>;
using vb = vector<bool>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
ll mod(ll a, ll b) {
  return ((a%b)+b)%b;
}
 
int cmp(double x, double y = 0, double tol = 1.e-7) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
template<typename T> struct seg_tree {
  int S;
 
  T identity;
  vector<T> value;
 
  seg_tree<T>(int _S, T _identity = T()) {
    S = _S, identity = _identity;
    value.resize(2*S+1, identity);
  }
 
  void set_leaves(vector<T> &leaves) {
    copy(leaves.begin(), leaves.end(), value.begin() + S);
 
    for (int i = S - 1; i > 0; i--)
      value[i] = value[2 * i] * value[2 * i + 1];
  }
 
  void upd(int i, T v) {
    i += S;
    value[i] = v;
    while (i > 1) {
      i /= 2;
      value[i] = value[2 * i] * value[2 * i + 1];
    }
  }
 
  T query(int i, int j) {
    T res_left = identity, res_right = identity;
    for(i += S, j += S; i <= j; i /= 2, j /= 2){
      if((i&1) == 1) res_left = res_left * value[i++];
      if((j&1) == 0) res_right = value[j--] * res_right;
    }
    return res_left * res_right;
  }
};
struct lca {
  int L, N;
  vector<int> depth, size, link;
 
  lca(){}
  lca(const vvi &graph, int root = 0) {
    N = graph.size();
    for (L = 0; (1 << L) <= N; L++);
    depth.resize(N), size.resize(N);
    link.resize(L*N);
    init(root, root, graph);
  }
  void init(int loc, int par, const vvi &graph) {
    link[loc] = par;
    for (int l = 1; l < L; l++)
      link[l*N + loc] = link[(l-1)*N + link[(l-1)*N + loc]];
    for (int nbr : graph[loc]) {
      if (nbr == par) continue;
      depth[nbr] = depth[loc] + 1;
      init(nbr, loc, graph);
      size[loc] += size[nbr];
    }
    size[loc]++;
  }
  int above(int loc, int dist) {
    for (int l = 0; l < L; l++)
      if ((dist >> l)&1)
        loc = link[l*N + loc];
    return loc;
  }
 
  int find(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    v = above(v, depth[v] - depth[u]);
    if (u == v) return u;
 
    for (int l = L - 1; l >= 0; l--) {
      if (link[l*N + u] != link[l*N + v])
        u = link[l*N + u], v = link[l*N + v];
    }
 
    return link[u];
  }
};
template<typename T> struct heavy_light {
  lca links;
  seg_tree<T> st;
  seg_tree<T> strev;
  vector<int> preorder, index, jump;
 
  heavy_light(const vvi &graph, int root) : st(graph.size()), strev(graph.size()) {
    links = lca(graph, 0);
 
    index.resize(graph.size()), jump.resize(graph.size());
    dfs(root, root, root, graph);
  }
  void dfs(int loc, int par, int lhv, const vvi &graph) {
    jump[loc] = lhv;
    index[loc] = preorder.size();
    preorder.push_back(loc);
 
    vector<int> ch = graph[loc];
    sort(ch.begin(), ch.end(), [&](int i, int j) {
      return links.size[i] > links.size[j]; });
    if (loc != par) ch.erase(ch.begin());
 
    for (int c = 0; c < ch.size(); c++)
      dfs(ch[c], loc, c ? ch[c] : lhv, graph);
  }
  void upd(int loc, T value) {
    st.upd(index[loc], value);
    strev.upd(index.size() - index[loc] - 1, value);
  }
 
  T __query(int u, int r, bool upwards) {
    T res = st.identity;
    while (u != r) {
      int go = max(index[r] + 1, index[jump[u]]);
      if (upwards) res = res * strev.query(index.size() - index[u] - 1, index.size() - go - 1);
      else res = st.query(go, index[u]) * res;
      u = links.link[preorder[go]];
    }
    return res;
  }
 
  T query(int u, int v) {
    int r = links.find(u, v);
    return __query(u, r, true) * st.query(index[r], index[r]) * __query(v, r, false);
  }
};
 
// Beginning of actual code, above you have the concatenation of template.cpp, data_structures/segtree.cpp, heavy_light/lca.cpp, and heavy_light/heavy_light.cpp
 
struct T {
    ll x;
    T(ll x = LLONG_MIN) : x(x) {}
 
    T operator*(T rhs) const {
        return max(x, rhs.x);
    }
};
 
void doit() {
    int N;
    scanf("%d", &N);
    vvi graph(N + (N - 1)); // first N represent nodes, last N-1 represent arcs
    vi costs(N - 1);
    fu(i, N - 1) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c); a--; b--;
        graph[a].push_back(N + i);
        graph[b].push_back(N + i);
        graph[N+i].push_back(a);
        graph[N+i].push_back(b);
        costs[i] = c;
    }
    heavy_light<T> hld(graph, 0);
    // insert the cost of edges
    fu(i, N-1) hld.upd(N + i, T(costs[i]));
    // process queries
    while (true) {
        char command[50];
        scanf(" %s", command);
        if (command[0] == 'D') break;
        else if (command[0] == 'Q') {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%lld\n", hld.query(a - 1, b - 1).x);
        } else {
            int i;
            ll ti;
            scanf("%d %lld", &i, &ti);
            hld.upd(N + i - 1, ti);
        }
    }
}
 
int main() {
    int t;
    scanf("%d", &t);
    while (t--) doit();
    return 0;
}
