// Proiect realizat de Eduard-Cristian Podaru, grupa 131, pentru tema 2 de la laboratorul de POO
// Tema pe care am ales sa o implementez este tema 11
// Programul a fost testat si ruleaza corect pe Microsoft Visual Studio Community 2019, 
// cu compilatorul care vine default cu instalarea workload-ului "Desktop Development for C++", si anume MSVC/Visual C++ Compiler
// Programul permite inserarea si afisarea datelor despre abonatii unei biblioteci, prin intermediul claselor implementate
#include <iostream>
#include<string>
#include<cstdlib>
#include "Biblioteca.h"

using namespace std;

Dosar dosar;

void separator();
void meniuPrincipal();
void meniuRevenire();
void iesire();

void afisareNume(Persoana& pers) {
											// Functie implementata pentru a exemplifica upcasting
	cout << pers.getNume();
}

void inregistrareAbonat(Persoana* pers) {
											// Functie implementata pentru a exemplifica downcasting
	int aux, pret, nrMax, nrImpr;
	

	cout << "\nIntrodu pretul abonamentului: ";
	cin >> pret;
	
	cout << "\nIntrodu numarul maxim de carti: ";
	cin >> aux;
	nrMax = Abonat::verificaNrMaxim(pret, aux);

	cout << "\nIntrodu numarul de carti imprumutate: ";
	cin >> aux;
	nrImpr = Abonat::verificaNrImprumutate(nrMax, aux);

	pers = new Abonat(pers->getNume(), pers->getCnp(), nrMax, nrImpr, pret);
	Abonat* abonatNou = dynamic_cast<Abonat*>(pers);
	
	Abonat::adaugaLaPretTotal(pret);

	dosar.adaugareAbonat(*abonatNou);

}



string readString() {
	string aux;																	// Functie implementata pentru a exemplifica try catch
	bool ok = false;
	while (!ok)
	{
		try {
			cin >> aux;
			ok = true;
		}
		catch (...) {
			cout<<"\nNu ai introdus un string, incearca din nou\n";
		}
	}

	return aux;
}

int readInt() {
	int aux;																	// Functie implementata pentru a exemplifica try catch
	bool ok = false;
	while (!ok) {
		try {
			cin >> aux;
			ok = true;
		}
		catch (...) {
			cout << "\nNu ai introdus un numar, incearca din nou\n";
		}
	}
	return aux;
}

void separator() {
	cout << "\n=======================================================================\n";
}

void meniuPrincipal() {
	string command;

	separator();

	cout << "Alege o comanda dintre urmatoarele: \n\n";

	cout << "READ - Citeste o lista de abonati\n";
	cout << "SHOW - Afiseaza lista de abonati\n";
	cout << "ADD - Adauga o persoana la lista de abonati\n";
	cout << "EXIT - Opreste programul\n";

	cout << "\nIntrodu comanda: ";

	cin >> command;

	for (unsigned int i = 0; i < command.size(); ++i) {
		command[i] = toupper(command[i]);
	}

	if (command == "READ") {
		separator();
		cin >> dosar;

		cout << "\nDosarul a fost citit si memorat\n";

		separator();
		meniuRevenire();
	}

	if (command == "SHOW") {
		separator();
		cout << dosar;
		separator();
		meniuRevenire();
	}

	if (command == "ADD") {
		separator();
		cout << "\nCitirea unei persoane: \n";
		Persoana* pers;
		pers = new Persoana();
		cin >> *pers;
		cout << "\nUrmeaza datele abonamentului:\n";
		inregistrareAbonat(pers);

		separator();
		meniuRevenire();

	}
	if (command == "EXIT") {
		cout << "\nMultumesc pentru rulare!\n";
		iesire();
	}

}

void meniuRevenire() {
	string command;
	cout << "Alege o comanda dintre urmatoarele: \n\n";

	cout << "BACK- Revenire la meniul principal\n";
	cout << "EXIT - Opreste programul\n";

	cout << "\nIntrodu comanda: ";

	cin >> command;

	for (unsigned int i = 0; i < command.size(); ++i) {
		command[i] = toupper(command[i]);
	}

	if (command == "BACK") {
		meniuPrincipal();
	}
	if (command == "EXIT") {
		iesire();
	}
}

void iesire() {
	exit(0);
}

int main() {

	cout << "Acest program permite afisarea si citirea unui dosar de abonati la biblioteca\n";

	meniuPrincipal();

	return 0;
}

