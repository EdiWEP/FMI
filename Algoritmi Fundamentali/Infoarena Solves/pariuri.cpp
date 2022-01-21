// Podaru Eduard-Cristian
// Problema se rezolva folosind un tabel hash in care tot adaugam banii obtinuti/pierduti la timpurile diferite
#include<iostream>
#include<fstream>
#include<unordered_map>

using namespace std;

ifstream inputFile("pariuri.in"); ofstream outputFile("pariuri.out");

int n, m;

unordered_map<int,int> Hash;

int main() {

    int time, gain;

    inputFile>>n;

    for(int i = 0; i < n; ++i) {
        
        inputFile >> m;

        for(int j = 0; j < m; ++j) {
            
            inputFile >> time >> gain;

            Hash[time] += gain;
        }
    }

    outputFile << Hash.size() << '\n';
    for(auto i = Hash.begin(); i != Hash.end(); ++i) {
        outputFile << i->first << ' '; 
        outputFile << i->second << ' ';
    }
    return 0;
}