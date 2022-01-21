#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

#define FIRST 1
#define LESS 2
#define MORE 3 

ifstream inputFile("transport2.in"); ofstream outputFile("transport2.out");


int numberOfNodes, numberOfEdges;
int destination;

int MPW = 0; // maximum possible weight
int lastWeight;
bool betterWeight;
int heaviest = 0;

int low, high;

int visited[100005]; // declarat global => initial toate = 0 
int currentStep; // folosesc variabila asta ca sa nu trebuiasca sa resetez tot vectorul visited de fiecare data 

vector<vector<pair<int, int>>> adjacencyList;
// first -> vecin       second -> weight

void initialize() {

    int x, y, weight;
    inputFile >> numberOfNodes >> numberOfEdges;

    destination = numberOfNodes - 1;

    adjacencyList = vector<vector<pair<int, int>>>(numberOfNodes, vector<pair<int, int>>()); 

    for(int i = 0; i < numberOfEdges; ++i) {

        inputFile >> x >> y >> weight;
        --x; --y; // ca sa indexez de la 0
        MPW = max(MPW, weight);
        adjacencyList[x].push_back(make_pair(y, weight));
        adjacencyList[y].push_back(make_pair(x, weight));
    }
}

void dfsTest(int node) {

    visited[node] = currentStep;
    for(int i = 0; i < adjacencyList[node].size() && !betterWeight; ++i) {
        pair<int, int> otherNode = adjacencyList[node][i];

        if(visited[otherNode.first] != currentStep && lastWeight <= otherNode.second) {
            if(otherNode.first == destination) {
                betterWeight = true;
            }
            else {
                dfsTest(otherNode.first);
            }
        }
    }
}

int nextBinarySearch(int code) {
    // functie care returneaza urmatorul weight posibil pe care il testam 
     
    switch(code) {

        case FIRST:
            low = 1; high = MPW;
        break;

        case LESS:
            high = lastWeight - 1;
        break;

        case MORE:
            low = lastWeight + 1;
        break;

        default: 
        break;
    }
 
    return (low + high) / 2;
}

void findMax() {

    // idee: fa binary search la o greutate de masina care poate sa ajunga la nodul n

    low = 1; high = MPW;
    lastWeight = nextBinarySearch(FIRST);

    currentStep = 1;

    while(low <= high) {

        betterWeight = false;
        dfsTest(0);

        if (betterWeight) {
            heaviest = lastWeight; 
            lastWeight = nextBinarySearch(MORE);
            
        }
        else {
            lastWeight = nextBinarySearch(LESS);
            
        }

        ++currentStep;
        
    }
}

int main() {

    initialize();

    findMax();
    outputFile << heaviest;
    // aveam TLE de la niste cout-uri lasate in program si ma face trist
    return 0;
}