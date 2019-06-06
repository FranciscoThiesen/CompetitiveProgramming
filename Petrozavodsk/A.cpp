#include <bits/stdc++.h>
#define TRACE(x) x
using namespace std;

int main()
{
	ifstream in("tests.in");
	ofstream out("tests.out");
    int n, m;
	in >> n >> m;
	vector<int> grades(m);
	for(int& x : grades) in >> x;
	vector<string> ans;
	
	string lixo;
	for(int i = 0; i < n; ++i) {
		getline(in, lixo); // quase certo que eh necessario
		string U;
        getline(in, U);
        int K;
		in >> K;
        vector<int> subject(K);
        for(int& x : subject) in >> x;
		vector< tuple<int, int, int> > exams;
        
        for(int _ = 0; _ < K; ++_) {
            int a, b, c;
            in >> a >> b >> c;
            exams.emplace_back(a, b, c);
        }
        int total = 0;
        for(int x = 0; x < K; ++x) {
            int nota = grades[ subject[x] - 1];
            int a, b, c;
            tie(a, b, c) = exams[x];
            if( nota < a) total += 2;
            else if( nota >= a && nota < b) total += 3;
            else if( nota >= b && nota < c) total += 4;
            else total += 5;
        }
        int F;
        in >> F;
        for(int _ = 0; _ < F; ++_) {
            getline(in, lixo);
            string faculty;
            getline(in, faculty);
            int needed;
            in >> needed;
            if( total >= needed ) {
                string name = U + " " + faculty;
                ans.push_back( name );
            }
        }
    }
    if( ans.empty() ) {
        out << "Army" << endl;
    }
    else {
        for(const auto& s : ans) out << s << endl;
    }
    return 0;
}
