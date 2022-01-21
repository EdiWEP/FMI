#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

#define INCHIS -2
#define PAZNIC 0
#define BLOCAT -1

ifstream inputFile("muzeu.in"); ofstream outputFile("muzeu.out");

int dim; // dimensiune 

int out[255][255];

vector<pair<int, int>> guards;
queue<pair<int, int>> nodeQueue;

void initialize() {

    char c;

    inputFile >> dim;

    for(int i = 0; i <= dim + 1; ++i) {
        out[0][i] = INCHIS;
        out[i][0] = INCHIS;
        out[dim+1][i] = INCHIS;
        out[i][dim+1] = INCHIS;
    }

    for(int i = 1; i <= dim; ++i) {
        for(int j = 1; j <= dim; ++j) {
            inputFile >> c;

            switch(c) {

                case '.': 
                    out[i][j] = BLOCAT; // initializez aici
                break;
                case '#': 
                    out[i][j] = INCHIS;
                break;
                case 'P': 
                    out[i][j] = PAZNIC;
                    guards.push_back(make_pair(i, j)); // pastram paznicii ca sa nu parcurgem toata matricea incontinuu
                break;
            }
        }
    }


}



void bfs() {
    int nextStep;
    pair<int, int> currentNode;

    while(!nodeQueue.empty()) {
        currentNode = nodeQueue.front();
        nodeQueue.pop(); 
        int x = currentNode.first;
        int y = currentNode.second;
        
        nextStep = out[x][y] + 1;

        if(out[x-1][y] == BLOCAT || out[x-1][y] > nextStep) {
            out[x-1][y] = nextStep;
            nodeQueue.push(make_pair(x-1, y));
        }
        if(out[x+1][y] == BLOCAT || out[x+1][y] > nextStep) {
            out[x+1][y] = nextStep;
            nodeQueue.push(make_pair(x+1, y));
        }
        if(out[x][y-1] == BLOCAT || out[x][y-1] > nextStep) {
            out[x][y-1] = nextStep;
            nodeQueue.push(make_pair(x, y-1));
        }
        if(out[x][y+1] == BLOCAT || out[x][y+1] > nextStep) {
            out[x][y+1] = nextStep;
            nodeQueue.push(make_pair(x, y+1));
        }
    }   
}

void fill() {

    for(int i = 0; i < guards.size(); ++i) {
        nodeQueue.push(guards[i]);
    }

    bfs();
}

void print() {

    //char* buffer = (char*) malloc(dim*2+1);
    for(int i = 1; i <= dim; ++i, outputFile << '\n') {
        for(int j = 1; j <= dim; ++j) {
            outputFile << out[i][j] <<' ';
        }
    }
}

int main() {

    initialize();

    fill();

    print();
    return 0;
}