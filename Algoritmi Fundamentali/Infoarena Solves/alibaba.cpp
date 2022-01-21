// Podaru Eduard-Cristian

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


ifstream inputFile("alibaba.in");
ofstream outputFile("alibaba.out");

int n, k;

vector<int> v;

int main() {

    int contor = 0;
    int digit;
    int i;

    inputFile>> n >> k;
    inputFile.get();

    for(i = 0; i < n; ++i) {

        digit = inputFile.get() - '0';

        while(!v.empty() && v.back() < digit && contor < k) {      
            v.pop_back();
            ++contor;
        }

        v.push_back(digit); 
    }

    while(contor < k) {
        ++contor;
        v.pop_back();
    }

    for( i = 0 ; i < v.size(); ++i) {
        outputFile<<v[i];
    }
    return 0;

}