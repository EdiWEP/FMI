// Podaru Eduard-Cristian
// La aceasta problema se foloseste un tabel hash, in care pastram toate sumele a cate 3 numere posibile, 
// incercam odata cu fiecare suma calculata sa cautam S2=S-(suma aceea) in tabel, 
// daca gasim, numerele din suma respectiva si S2 sunt solutie

#include<iostream>
#include<fstream>
#include <cstdlib>
#include <unordered_map>

using namespace std;

ifstream inputFile("loto.in"); ofstream outputFile("loto.out");


struct Vector3 {

    int x;
    int y;
    int z;
};

int getSum(Vector3 k) {
    return k.x+k.y+k.z;
}

unordered_map<int, Vector3> Hash;

int n, s;

int a[100];

int main() {

    inputFile >> n >> s;

    for(int i = 0; i < n; ++i) {
        inputFile >> a[i];
    }


    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            for(int l = j; l < n; ++l) {

                Vector3 suma;
                suma.x = a[i];
                suma.y = a[j];
                suma.z = a[l];

                Hash[getSum(suma)] = suma;

                if(Hash.find(s-getSum(suma)) != Hash.end()) {

                    // Am gasit solutie
                    outputFile << Hash[s-getSum(suma)].x << ' ' << Hash[s-getSum(suma)].y << ' ' << Hash[s-getSum(suma)].z << ' ' << a[i] << ' ' << a[j] << ' ' << a[l];
                    exit(0);
                }

            }        
        }
    }
    outputFile << -1; // Daca se ajunge aici nu am gasit solutie
    return 0;
}

