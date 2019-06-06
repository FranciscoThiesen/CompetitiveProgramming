#include <bits/stdc++.h>

using namespace std;

struct node {
    int value;
    node* nxt;
    node() {}
    node( int v = -1, node* ptr = nullptr) : value(v), nxt(ptr) {}
};

node* arr[100000];

int currentVersion = 0;

void make_copy(int version, int value ) {
    node x = node( value, arr[version] );
    arr[ ++currentVersion ] = x; 
}

int pop( int version ) {
    if( arr[version] != nullptr) {
        int v = (arr[version])->value;
        arr[ version ] = (arr[ version ])->nxt;
        return v;
    }
    return -1;
}

int main()
{
    arr[0] = node();

}
