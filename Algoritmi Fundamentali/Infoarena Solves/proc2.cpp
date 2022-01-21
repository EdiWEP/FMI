// Podaru Eduard-Cristian
// Putem folosi 2 min-heapuri, unul in care sa pastram indicele procesoarelor libere, 
// si unul in care sa pastram operatii care sunt executate momentan

#include<iostream>
#include<fstream>
#include<queue>

using namespace std;


ifstream inputFile("proc2.in"); ofstream outputFile("proc2.out");

int n, m, start, length;

priority_queue< pair<int, int> > tasks;
priority_queue<int> procs;


int main() {


    inputFile >> n >> m;

    for(int i = 1; i <= n; ++i) {
        procs.push(-i);
    }

    for(int i = 0; i < m; ++i) {

        inputFile >> start >> length;

        int eta = start + length;

        while(!tasks.empty() && start >= (-1 * tasks.top().first) ) {           // Eliminam taskurile care s-au terminat 
            procs.push(-tasks.top().second);                                    // Eliberam procesorul
            tasks.pop();
        }

        
        outputFile << -procs.top() << '\n';

        tasks.push(make_pair(-eta, -procs.top()));                  // Asociam procesorului cu indice minim liber taskul curent
        procs.pop();

    }
 
    return 0;

}