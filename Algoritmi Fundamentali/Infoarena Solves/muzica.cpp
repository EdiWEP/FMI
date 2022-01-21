// Podaru Eduard-Cristian
// Putem folosi un tabel hash pentru a retine cele N melodii date
// Generam melodiile random si le cautam in tabel, daca le gasim, incrementam un contor

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<vector>

using namespace std;


ifstream inputFile("muzica.in"); ofstream outputFile("muzica.out");

const int Mod = 11587;
int n, m, contor;
long long a, b, c, d, e;
long long x, y, z;         // Variabile in care retinem ultimele doua melodii generate

//unordered_map<long long, bool> Hash;

vector<int> Hash[Mod];

bool sterge(int key) {
    int index = key % Mod;
    for(int i = 0; i < Hash[index].size(); ++i) {
        if(Hash[index][i] == key) {
            Hash[index][i] = -1;            // Practic stergem
            return 1;
        }
    }

    return 0;
}

int main() {

    inputFile >> n >> m;
    inputFile >> a >> b >> c >> d >> e;

    for(int i = 0; i < n; ++i) {
        inputFile >> x;
        Hash[x % Mod].push_back(x);
    }

    x = a;
    y = b;


    for(int i = 0; i < m; ++i) {
        if(sterge(x)) {
            ++contor;
            
        }
        
        z = (c * y + d * x) % e;

        x = y; y = z;

    }

    outputFile << contor;
    return 0;

}
