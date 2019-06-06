#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define rep(i,a,b) for(int (i) = (a); (i) < (b); ++(i))
#define pb push_back

typedef pair<int, int> pii;
typedef vector<int> vi;

const int ms = 112345;

int n, q, idx = 0, freq[ms], arr[ms];
map<int, int> newValue;
map<int, int> rev;

set<int> compress;

struct node
{
    int val;
    node *l, *r;
    node() {}
    node(int val = 0, node* l = nullptr, node* r = nullptr) : val(val), l(l), r(r){}
};

node* roots[ms];

node* build(int left, int right)
{
    if(left == right - 1) return new node(0, nullptr, nullptr);
    int mid = (left + right) / 2;
    node* l = build(left, mid);
    node* r = build(mid, right);
    return new node(l->val + r->val, l, r);
}

node* buildCopy(node* current, int left, int right, int upd)
{
	if(left == right - 1) return new node(freq[upd], nullptr, nullptr);
	int mid = (left + right) / 2;
	node *l, *r;
	// Only create nodes when necessary -> This it what makes it beautiful
    if( upd < mid )
	{
		l = buildCopy(current->l, left, mid, upd);
		r = current->r;
	}
	else
	{
		l = current->l;
		r = buildCopy(current->r, mid, right, upd);
	}
	return new node(l->val + r->val, l, r);
}

// Should be different for every problem
int query(int left, int right, int kth)
{
	node *leftEnd = roots[left - 1], *rightEnd = roots[right];
	int seen = 0;
	int lo = 0, hi = ms, mid;
	while(lo != hi - 1)
	{
		mid = (lo + hi) / 2;

		if(seen + (rightEnd->l->val - leftEnd->l->val) >= kth)
		{
			rightEnd = rightEnd->l;
			leftEnd  = leftEnd->l;
			hi = mid;
		}
		else
		{
			seen += ( (rightEnd->l->val - leftEnd->l->val) );
			rightEnd = rightEnd->r;
			leftEnd  = leftEnd->r;
			lo = mid;
		}
	}
	return rev[lo];
}

int main()
{
    scanf("%d %d", &n, &q);
    rep(i,0,n)
	{
        scanf("%d", &arr[i]);
        compress.insert(arr[i]);
    }

    for(const int& val : compress)
    {
    	newValue[val] = idx++;
    	rev[idx - 1] = val;
    }

   	roots[0] = build(0, ms);

	rep(i,1,n+1)
	{	
		freq[newValue[ arr[i - 1] ] ]  += 1;
		roots[i] = buildCopy(roots[i-1], 0, ms, newValue[arr[i - 1]] );
	}
	rep(x,0,q)
	{
		int i, j, k;
		scanf("%d %d %d", &i, &j, &k);
		printf("%d\n", query(i, j, k) );
	}
	return 0;
}
