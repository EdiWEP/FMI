#include <iostream>
#include <fstream>
	
using namespace std;
	
ifstream inputFile("rf.in"); ofstream outputFile("rf.out");
	
int n, a[260][260], nr[260][260];
	
void RoyFloyd() {

    int i,j,k;
    for(k = 1; k <= n; ++k) {
        for(i = 1; i<= n; ++i) {
            for(j = i + 1; j <= n; ++j) {
                if(a[i][k] + a[k][j] < a[i][j] || (a[i][k]+a[k][j] == a[i][j] && nr[i][k]+nr[k][j] > nr[i][j])) {
                    a[i][j] = a[i][k] + a[k][j];
                    nr[i][j] = nr[i][k] + nr[k][j];
                    a[j][i] = a[i][j];
                    nr[j][i] = nr[i][j];
	
                }
            }
        }
    }
}
	
int main() {
	
    int i, j;
	
    inputFile >> n;
	
    for(i = 1; i <= n; ++i) {
        for(j = 1; j <= n; ++j) {
            inputFile >> a[i][j];
            if (i != j) {
                nr[i][j] = 1;
            }
            else {
                nr[i][j] = 0;
            }
        }
    }
    
    RoyFloyd();
    for(i = 1; i <= n; ++i, outputFile << '\n') {
        for(j = 1; j <= n; ++j) {
            outputFile<<a[i][j]<<' ';
	
        }
    }
	
    for(i = 1; i <= n; ++i, outputFile << '\n') {
        for(j = 1; j <= n; ++j) {
            outputFile<<nr[i][j]<<' ';
        }
    }
	
    return 0;
}