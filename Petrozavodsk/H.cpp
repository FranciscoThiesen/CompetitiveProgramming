#include <bits/stdc++.h>

using namespace std;

int main()
{
	ifstream in("tests.in");
	int n, m;
	in >> n >> m;
	vector<int> grades(m);
	for(int& x : grades) in >> x;
	vector<string> ans;
	
	string lixo;
	for(int i = 0; i < n; ++i) {
		//getline(in, lixo); // quase certo que eh necessario
		string U;
		getline(in, U);
		int K;
		in >> K;
		vector< tuple<int, int, int> > exams;

	}

}