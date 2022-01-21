#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

ifstream inputFile("srevni.in"); ofstream outputFile("srevni.out");


int nCities, nEdges;
int citiesLeft; 

vector<pair <int, int>> price;
int cheapest[100005];
bool visited[100005];


vector< vector<int> > adjacencyList;

void initialize() {

    int x, y;

    inputFile >> nCities >> nEdges;

    citiesLeft = nCities;

    price = vector<pair<int,int>>(nCities, pair<int,int>());
    adjacencyList = vector< vector<int> >(nCities, vector<int>());
    for(int i = 0; i < nCities; ++i) {
        
        inputFile >> x;
        price[i].first = x;
        price[i].second = i;
        
        cheapest[i] = x;
        visited[i] = false;
    }

    for(int i = 0; i < nEdges; ++i) {
        inputFile >> x >> y;     
        --x; --y;   // ca sa indexez de la 0           
        adjacencyList[y].push_back(x);      // Adaugam muchiile invers
                                            // Motivatie: Daca am face dfs din fiecare oras pt a gasi un minim => O(n^2)
                                            // Daca in schimb intai sortam orasele, apoi plecam din cele cu pret minim si actualizam minimul celor reachable => O(nlogn)
    }
    
}


void dfs(int node, int newPrice) {
    --citiesLeft;
    visited[node] = true;

    for(int i = 0; i < adjacencyList[node].size(); ++i) {
        int otherNode = adjacencyList[node][i];
        if(!visited[otherNode]) {
            cheapest[otherNode] = newPrice; // nu este nevoie de a verifica, sigur este mai bun pretul din cauza sortarii
            dfs(otherNode, newPrice);
        }
    }
}

void print() {
    for(int i = 0; i < nCities; ++i) {
        outputFile << cheapest[i] << ' ';
    }
}

bool comp(pair<int,int> x, pair<int,int> y) {

    return (x.first <= y.first);
}

int main() {

    initialize();

    sort(price.begin(), price.end(), comp);

    for(int i = 0; i < nCities; ++i) {
        if(citiesLeft) {
            if(!visited[price[i].second]) {
                dfs(price[i].second, price[i].first);
            }
        }
        else {
            break;
        }
    }

    print();
    return 0;
}