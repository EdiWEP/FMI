// Podaru Eduard-Cristian
// Putem parcurge sirul de intervale pentru a gasi costul minim de fiecare data, insa prioritizam intai marginile superioare mari,
// Practic completand invers intervalul 1..n
// Actualizam dupa fiecare minim lungimea de interval pe care am cumparat-o pana acum

#include<iostream>
#include<fstream>

using namespace std;


ifstream inputFile("timbre.in"); ofstream outputFile("timbre.out");

int n, m, k;
int currentLen;
int minim, minimIndex;
int sol;

struct timbre {
    int cost;
    int range;
};

timbre a[10001];


int main() {

    inputFile >> n >> m >> k;

    for(int i = 0; i < m; ++i) {
        inputFile >> a[i].range;
        inputFile >> a[i].cost;
    }

    while(currentLen < n) {
        
        minim = 999999;
        
        for(int i = 0; i < m; ++i) {
            if( a[i].cost < minim && a[i].range >= n - currentLen ) {
                minim = a[i].cost;
                minimIndex = i;
            }
        }

        sol += minim;
        a[minimIndex].range = -1;        // Eliminam intervalul folosit
        currentLen += k;                // Mereu luam cate k elemente  
    }

    outputFile << sol;
    return 0;
}