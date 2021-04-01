// Acest program implementeaza un automat Mealy
// Automatul implementat a fost testat pe inputul dat de catre laborant in fisierul cu exemple
// Proiect realizat de Podaru Eduard-Cristian, grupa 131, pentru tema 1 de la laborator de Limbaje Formale si Automate

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream inputFile("input.txt");
ofstream outputFile("output.txt");

struct Muchie {
	
	int catre;
	char simbol;
	char outputChar;
};

struct Nod {


		bool start = false;
		bool final = false;
		int index;
		int nrMuchii = 0;
		Muchie muchii[100];

		
};


Nod noduri[100];
int nrCuvinte, n, m;					// n - numarul de noduri; m - numarul de muchii
int stareInitiala;

string cuvinte[100];

void citire() {
	
	int i,stare,nrFinale;
	inputFile >> n >> m;
	

	for (i = 0; i < n; ++i) {
		noduri[i].index = i;
	}

	for (i = 0; i < m; ++i) {
		int x, y;
		char simbol, output;
		inputFile >> x >> y >> simbol >> output;
		++noduri[x].nrMuchii;
		noduri[x].muchii[noduri[x].nrMuchii-1].catre = y;
		noduri[x].muchii[noduri[x].nrMuchii-1].simbol = simbol;
		noduri[x].muchii[noduri[x].nrMuchii-1].outputChar = output;

	}

	
	inputFile >> stare;
	stareInitiala = stare;
	noduri[stare].start = true;

	inputFile >> nrFinale;

	for (i = 0; i < nrFinale; ++i) {
		inputFile>> stare;
		noduri[stare].final = true;
	
	}
	
	inputFile >> nrCuvinte;

	for (i = 0; i < nrCuvinte; ++i) {
		inputFile >> cuvinte[i];
	}


}
									
void testeaza(string cuvant) {

	int stareCurenta = stareInitiala;
	int traseu[100];
	int nrLitere = cuvant.size();
	string outputul = "";
	
	int poz = 0;
	char literaCurenta = cuvant[poz];

	traseu[0] = stareInitiala;
	bool acceptat = true;

	
	while(poz<nrLitere) {
		
		bool gasit = false;
		for (int i = 0; i < noduri[stareCurenta].nrMuchii; ++i) {
			
			if (noduri[stareCurenta].muchii[i].simbol == cuvant[poz]) {
				outputul += noduri[stareCurenta].muchii[i].outputChar;
				++poz;
				traseu[poz] = noduri[stareCurenta].muchii[i].catre;
				stareCurenta = noduri[stareCurenta].muchii[i].catre;
				gasit = true; 
				break;
			}
			
		}
		if (!gasit) {
			acceptat = false;
			break;
		}
		if (poz == nrLitere) {
			if (!noduri[stareCurenta].final) {
				acceptat = false;
				break;
			}
		}
	}

	if (acceptat) {
		outputFile << "DA\n";
		outputFile << outputul << '\n';
		outputFile << "Traseu: ";
		for (int i = 0; i <= nrLitere; ++i) {
			outputFile << traseu[i] << ' ';
		}
		outputFile << '\n';
	}
	else {
		outputFile << "NU\n";
	}
}


int main() {

	citire();
	for (int i = 0; i < nrCuvinte; ++i) {
		
		testeaza(cuvinte[i]);
	}

}
