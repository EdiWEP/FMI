// Podaru Eduard-Cristian

#include <iostream>
#include <fstream>

using namespace std;

ifstream inputFile("deque.in");
ofstream outputFile("deque.out");

long long suma;
int n, k, st, dr;
int a[5000001];
int d[5000001];


int main() {

    int i;

    inputFile>>n>>k;
    st = 1;
    dr = 0;
    suma = 0;

    for( i = 1; i <= n ; ++i) {
        inputFile>>a[i];
    }
    
    for(i = 1; i <= n; ++i) {

        while( st <= dr && a[i] <= a[d[dr]] ) {
            --dr;
        }

        ++dr;
        d[dr] = i;
        if( i >= k) {
            if (d[st] <= i - k) {
                ++st;
            }
            suma += a[d[st]];
        }
    }

    outputFile << suma;
    return 0;

}