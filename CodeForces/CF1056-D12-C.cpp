#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define buff() ios::sync_with_stdio(0);cin.tie(0)
#define sz(x) ( (int) (x).size() )

using vi  = vector<int>;
using ll  = long long;
using pii = pair<int, int>;
using vll = vector<ll>;
using pll = pair<ll, ll>;

constexpr int inf = 0x3f3f3f3f;
constexpr ll  mod = 1000000007;

inline ll powmod(ll a, ll b) 
{
    ll res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1) 
    {
        if(b&1) res = (res * a) % mod;
        a = (a*a) % mod;
    }
    return res;
}

int main() 
{
    int n, m;
    cin >> n >> m;
    vector< pii > h( 2 * n);
    vector<int> power( 2 * n);
    vector<int> inimigo( 2 * n, - 1);
    for(int i = 0; i < 2 * n; ++i)
    {
        cin >> h[i].first;
        h[i].first = - ( h[i].first );
        h[i].second = i;
        power[i] = h[i].first;
    }
    vector< pii > rixa;
    for(int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        --a;--b;
        inimigo[a] = b;
        inimigo[b] = a;
        rixa.emplace_back( min(a, b), max(a, b) );
    }

    set< pair<int, int> > semRixa;
    set< pair<int, int> > comRixa;

    for(int i = 0; i < 2 * n; ++i)
    {
        if(inimigo[i] != -1) comRixa.insert( h[i] );
        else semRixa.insert( h[i] );
    }
    deque<bool> usado( 2 * n, false);
    int joga;
    cin >> joga;
    joga -= 1;
    int compulsorio = -1; 
    for(int i = 0; i < 2 * n; ++i)
    {
        if(joga)
        {
            int eleQuer;
            cin >> eleQuer;
            --eleQuer;
            if( inimigo[eleQuer] != -1)
            {
                compulsorio = inimigo[ eleQuer ];
                if( usado[compulsorio] == true) compulsorio = -1;
                comRixa.erase( h[eleQuer] );
            }
            else
            {
                compulsorio = -1;
                usado[ eleQuer ] = true;
                semRixa.erase( h[eleQuer] );
            }
        }
        else
        {
            if( compulsorio != -1 )
            {
                cout << compulsorio + 1 << endl;
                usado[ compulsorio ] = true;
                comRixa.erase( h[compulsorio ] ); 
            }
            else
            {
                if( !comRixa.empty() )
                {
                    auto prim = *(comRixa.begin());
                    comRixa.erase(comRixa.begin() );
                    usado[prim.second] = true;
                    cout << prim.second + 1 << endl;
                }
                else
                {
                    auto prim = *(semRixa.begin());
                    semRixa.erase(semRixa.begin());
                    usado[prim.second] = true;
                    cout << prim.second + 1 << endl;
                }
            }
        }
        joga ^= 1;
    }
    return 0;
}

