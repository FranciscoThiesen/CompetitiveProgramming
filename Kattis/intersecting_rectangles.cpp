#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <tuple>
#include <set>
#include <map>
#include <iterator>

using namespace std;

#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair

typedef vector<int> vi;

int lsb(int i){ return i & -i;}

struct BIT
{
	int size;
	vi table;
	
	BIT(int sz) {
		table.resize(sz+1, 0);
		size = sz+1;
	}

	void update(int pos, int delta) {
		++pos;
		while(pos <= size)
		{
			table[pos] += delta;
			pos += lsb(pos);
		}
	}
	//the i parameter is 0 indexed
	int sum(int i) const {
		++i;
		int sum = 0;
		while(i > 0)
		{
			sum += table[i];
			i -= lsb(i);
		}
		return sum;
	}
	// range sum, l and r are 0-indexed
	int rangeSum(int l, int r) const {
		return sum(r) - sum(l-1);
	}
};

// x, kind, y1, y2
using ev = tuple<int, int, int, int>;

int main()
{
	int n;
	ios::sync_with_stdio( false ); cin.tie( nullptr );
	cin >> n;
	vi all_x, all_y;
	vector< ev > events;
	

	for(int i = 0; i < n; ++i)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		// type 0 -> queries
		events.emplace_back(x1, 0, y1, y2);
		events.emplace_back(x2, 0, y1, y2);

		// horizontal adds are add and decrement at Y
		events.emplace_back(x1, 1, y1, y1);
		events.emplace_back(x1, 1, y2, y2);
		events.emplace_back(x2, -1, y1, y1);
		events.emplace_back(x2, -1, y2, y2);

		all_x.push_back(x1); all_x.push_back(x2);
		all_y.push_back(y1); all_y.push_back(y1);
	}
	sort( all( all_x ) );
	sort( all( all_y ) );
	all_x.erase( unique(all( all_x) ), all_x.end() );
	all_y.erase( unique(all( all_y) ), all_y.end() );

	sort( all(events) );

	bool has_intersection = false;

	BIT bit( (int) events.size() );

	for(const auto& e : events )
	{
		int x, op, y1, y2;
		tie(x, op, y1, y2) = e;
		int idx_y = lower_bound( all( all_y ), y1) - begin(all_y);
		
		if( op == 0 )
		{
			int idx_y2 = lower_bound( all( all_y ), y2) - begin(all_y);
			if( bit.rangeSum(idx_y + 1, idx_y2 - 1) ) {
				has_intersection = true;
				break;
			}
		}
		else bit.update(idx_y, op);
	}

	if ( has_intersection == false ) cout << 0 << endl;
	else cout << 1 << endl;
	return 0;

}
