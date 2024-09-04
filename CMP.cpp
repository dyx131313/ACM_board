//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

void cmp() {
    db a = clock();
    system("A.exe");
    db b = clock();
    system("B.exe");
    db c = clock();
    if (system("fc A.out B.out")) {
        printf("WA\n");
    } else {
        printf("AC %lf %lf\n", (b - a) / CLOCKS_PER_SEC, (c - b) / CLOCKS_PER_SEC);
    }
}