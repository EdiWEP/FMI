// Tema 2 de la laboratorul de Limbaje Formale si Automate (exercitiul 4, generare de cuvinte de o anumita lungime generate de o gramatica regulata)
// Realizata de Podaru Eduard-Cristian, grupa 131
// Programul ruleaza in conditiile in care lambda este '#' in fisierul de intrare si n este dat pe prima linie, in rest, structura fisierului de intrare este cea din pdf-ul care descrie proiectul 2
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

ifstream inputFile("input.txt"); 
ofstream outputFile("output.txt");

struct productie {
    char neterminal;
    string tranzitie;

};

int nrNeterminale, nrProductii, maxim;

char neterminale[1000];
productie productii[1000];


void citireNeterminale() {
    
    string str;
    bool dupaEgal = false;
    inputFile.ignore();
    getline(inputFile, str);
    
    for(int i = 0; i < str.length(); ++i) {

        if (dupaEgal) {
            if(str[i] >= 'A' && str[i] <= 'Z') {
                neterminale[nrNeterminale] = str[i];
                ++nrNeterminale;
            }
        }
        if(str[i] == '=') {
            dupaEgal = true;
        }

    }
  
}

void skipTerminale() {
    string str;         // Nu este nevoie sa retinem terminalele pentru a rezolva cerinta
    getline(inputFile,str);

}

void citireProductii() {

    string str;
    bool gasit;

    while(getline(inputFile,str)) {
        

        productii[nrProductii].tranzitie = "";
        
        gasit = false;;

        for (int i = 0 ; i < str.length(); ++i) {
            if(!gasit) {
                for(int j = 0 ; j < nrNeterminale; ++j) {
                    if(str[i] == neterminale[j]) {
                        productii[nrProductii].neterminal = neterminale[j];
                        gasit = true;
                        break;
                    } 
                }
            }
            else {
                
                if( (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '#' ) {
                    productii[nrProductii].tranzitie += str[i];
                }
            
            }
        }
        ++nrProductii;
    }
}

void generare(string cuvantCurent, int lungime, char neterminalCurent) {

    for(int i = 0 ; i < nrProductii; ++i) {
        if(productii[i].neterminal == neterminalCurent) {

            if(productii[i].tranzitie.length() == 1) {
                if(lungime == 0 && productii[i].tranzitie == "#") {
                    outputFile << cuvantCurent << '\n';
                }
                else {
                    if(lungime == 1 && productii[i].tranzitie != "#") {
                        outputFile << cuvantCurent + productii[i].tranzitie << '\n'; 
                    }
                }

            }
            else {
                if(productii[i].tranzitie[0] >= 'a' && productii[i].tranzitie[0] <= 'z') {              // Distingem intre regulate la stanga si la dreapta
                    if(lungime > 0) generare(cuvantCurent + productii[i].tranzitie[0], lungime - 1, productii[i].tranzitie[1]);
                }
                else {
                    if(lungime > 0) generare(cuvantCurent + productii[i].tranzitie[1], lungime - 1, productii[i].tranzitie[0]);
                }
            }
        }
    }
}

int main() {

    inputFile >> maxim; // Lungimea ceruta a cuvintelor
 
    citireNeterminale();

    skipTerminale();

    citireProductii();

    outputFile << "Cuvinte generate de lungime " << maxim <<'\n';

    generare( "", maxim, 'S');

    return 0;
}