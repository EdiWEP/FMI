// Podaru Eduard-Cristian

#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

ifstream inputFile("vila2.in");
ofstream outputFile("vila2.out");


int a[100001];
int n, k;
int maxim, minim, difference;

deque<int> maxDeque; 
deque<int> minDeque;


int main() {

    int i;
    
    difference = -10000000;

    inputFile>> n >> k;
   

    for(i = 1; i <= n; ++i) {
        inputFile>> a[i];

        while(!minDeque.empty() && a[minDeque.back()] >= a[i]) {
            minDeque.pop_back();

        }

        minDeque.push_back(i);

        if(minDeque.back() - minDeque.front() > k ) {
            minDeque.pop_front();
        }

        while(!maxDeque.empty() && a[maxDeque.back()] <= a[i]) {
            maxDeque.pop_back();
        }

        maxDeque.push_back(i);

        if(maxDeque.back() - maxDeque.front() > k ) { 
            maxDeque.pop_front();
        }

        difference = max(difference, a[maxDeque.front()] - a[minDeque.front()]);
    }

    outputFile << difference;
    
    return 0;
}
