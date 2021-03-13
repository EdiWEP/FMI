// Proiect realizat de Eduard-Cristian Podaru, grupa 131, pentru tema 1 de la laboratorul de POO
// Programul a fost testat si ruleaza corect pe Microsoft Visual Studio Community 2019, 
// cu compilatorul care vine default cu instalarea workload-ului "Desktop Development for C++", si anume MSVC/Visual C++ Compiler
// Programul simuleaza un magazin, folosind POO

#include <iostream>
#include <fstream>
#include "Magazin.h"
#include <cstdlib>						// Pentru exit();

using namespace std;

Magazin m;
Client* clienti = NULL;
int numarClienti;

void meniuPrincipal();					// Am implementat meniul sub forma unor functii care se apeleaza reciproc 
void meniuInitializare();				// Pentru a ii da cursivitate
void meniuSimulare();
void meniuAfisare();					
void iesire();							// Termina programul prin exit
void separator();						// Afiseaza o linie continua
void initializare();					// Initializeaza magazinul si clientii cu un set de date predefinit

void meniuPrincipal() {

	string command;

	
	cout << "Alege o comanda dintre urmatoarele:\n\n";
	cout << "SHOW - Afiseaza datele magazinului sau ale clientilor\n";
	cout << "SIMULATE - Simuleaza o zi de cumparaturi cu datele curente\n";
	cout << "INITIALIZE - Seteaza datele pentru magazin sau pentru clienti\n";	
	cout << "EXIT - Terminarea programului\n\n";
	cout << "Introdu comanda aici: ";

	cin >> command;
	for (unsigned int i = 0; i < command.size(); ++i) {
		command[i] = toupper(command[i]);
	}

	if (command == "INITIALIZE") {

		separator();
		meniuInitializare();
	}
	else if (command == "SIMULATE") {
		separator();
		meniuSimulare();
	}
	else if (command == "SHOW") {
		separator();
		meniuAfisare();
	}
	else if (command == "EXIT") {
		iesire();
	}
	else {
		cout << "\nComanda introdusa nu exista, introdu una din comenzile SHOW,SIMULATE,INITIALIZE sau EXIT.\n";
		meniuPrincipal();
	}

}

void meniuInitializare() {
	string command;

	cout<< "Ce date vrei sa setezi?\n";
	cout << "Alege o comanda dintre urmatoarele:\n\n";
	cout << "STORE - Citeste de la tastatura datele magazinului(folosind listaProduseImplementate.txt pentru a introduce corect produsele implementate)\n";
	cout << "CLIENTS - Citeste de la tastatura datele clientilor\n";
	cout << "MAIN - Revenire la meniul principal\n\n";

	cout << "Introdu comanda aici: ";
	cin >> command;

	for (unsigned int i = 0; i < command.size(); ++i) {
		command[i] = toupper(command[i]);
	}

	while (command != "STORE" && command != "MAIN" && command != "CLIENTS") {
		cout << "Ai introdus o comanda incorecta\n";
		cout << "Alege o comanda dintre urmatoarele:\n\n";
		cout << "STORE - Citeste de la tastatura datele magazinului(folosind listaProduseImplementate.txt pentru a introduce corect produsele implementate)\n";
		cout << "CLIENTS - Citeste de la tastatura datele clientilor\n";
		cout << "MAIN - Revenire la meniul principal\n\n";
		cout << "Introdu comanda aici: ";

		cin >> command;
		for (unsigned int i = 0; i < command.size(); ++i) {
			command[i] = toupper(command[i]);
		}
	}


	if (command == "STORE") {
		separator();
		cin >> m;

		cout << "\n\nAi setat datele magazinului.\n";
		cout << "Alege o comanda dintre urmatoarele:\n\n";
		cout << "MAIN - Revenire la meniul principal\n";
		cout << "BACK - Revenire la meniul de initializare\n\n";
		cout << "Introdu comanda aici: ";
		cin >> command;
		for (unsigned int i = 0; i < command.size(); ++i) {
			command[i] = toupper(command[i]);
		}

		while (command != "MAIN" && command != "BACK" ) {
			cout << "Ai introdus o comanda incorecta\n";
			cout << "Alege o comanda dintre urmatoarele:\n\n";
			cout << "MAIN - Revenire la meniul principal\n";
			cout << "BACK - Revenire la meniul de initializare\n\n";
			cout << "Introdu comanda aici: ";

			cin >> command;
			for (unsigned int i = 0; i < command.size(); ++i) {
				command[i] = toupper(command[i]);
			}
		}

	}
	else if (command == "CLIENTS") {
		
		separator();
		cout << "Introdu numarul de clienti: ";
		cin >> numarClienti;
		cout << '\n';

		delete[] clienti;
		clienti = new Client[numarClienti];

		for (int i = 0; i < numarClienti; ++i) {
			cout << "\nInformatii client " << i + 1<<" din "<<numarClienti<<":\n";
			cin >> clienti[i];
		}

		cout << "\n\nAi setat datele clientilor.\n";
		cout << "In meniul de afisare, pretul fiecarui produs va fi afisat ca fiind 0\n";
		cout << "Acesta va fi actualizat in urma rularii unei simulari\n\n";
		cout << "Alege o comanda dintre urmatoarele:\n\n";
		cout << "MAIN - Revenire la meniul principal\n";
		cout << "BACK - Revenire la meniul de initializare\n\n";
		cout << "Introdu comanda aici: ";
		cin >> command;
		for (unsigned int i = 0; i < command.size(); ++i) {
			command[i] = toupper(command[i]);
		}

		while (command != "MAIN" && command != "BACK") {
			cout << "Ai introdus o comanda incorecta\n";
			cout << "Alege o comanda dintre urmatoarele:\n\n";
			cout << "MAIN - Revenire la meniul principal\n";
			cout << "BACK - Revenire la meniul de initializare\n\n";
			cout << "Introdu comanda aici: ";

			cin >> command;
			for (unsigned int i = 0; i < command.size(); ++i) {
				command[i] = toupper(command[i]);
			}
		}
	}
	if (command == "MAIN") {
		separator();
		meniuPrincipal();
	}
	if (command == "BACK") {
		separator();
		meniuInitializare();
	}
	
}

void meniuSimulare() {
	
	m.setProfitZi(0);
	string command;

	cout << "\nSe va simula o zi de cumparaturi cu datele curente ale magazinului si clientilor\n";
	cout << "Daca deja s-a rulat o simulare, este indicat sa se reinitializeze datele clientilor\n";
	cout << "prin setarea manuala a unei noi liste de clienti sau prin repornirea programului\n";
	separator();
	cout << "Se va afisa stocul magazinului\n\n";
	cout << "Introdu \".\" pentru a continua \n";
	cin >> command;
	cout << '\n';
	m.afiseazaStoc();
	separator();
	cout << "Vor veni clientii pe rand\n\n";
	cout << "Introdu \".\" pentru a continua \n";
	cin >> command;

	for (int i = 0; i < numarClienti; ++i) {
	
		separator();
		int sumaNecesara;
		int sumaTotala=0;
		int sumaClient = clienti[i].getSuma();

		cout << "\nClientul " << i + 1<<'\n';

		sumaNecesara = m.verificaLista(clienti[i].getLista(), clienti[i].getNumarCumparaturi());
		for (int j = 0; j < clienti[i].getNumarCumparaturi(); ++j) {
			sumaTotala += clienti[i].getLista()[j].pretTotal();
		}

		cout << "\n";
		clienti[i].afiseazaLista();
		cout<< "\n";
		
		cout << "\nProdusele cu pret 0 nu sunt disponibile in stocul magazinului\n\n";
		cout << "Suma necesara pentru toate produsele, in limita stocului: " << sumaNecesara<<" lei\n";
		cout << "Clientul are " << clienti[i].getSuma() << " lei\n\n";

		cout << "Introdu \".\" pentru a continua \n";
		cin >> command;

		if (sumaTotala > sumaNecesara) {
			cout << "Unele dintre produsele cerute nu sunt vandute de acest magazin sau nu sunt destule in stoc\n";
			cout << "Daca clientul decide sa cumpere, vor fi cumparate toate produsele cerute in limita stocului\n";
			cout << "Iar cele care nu sunt disponibile in magazin vor fi sterse din lista clientului\n\n";
		}

		
		separator();
		
		if (sumaNecesara > sumaClient) {
			cout << "Clientul realizeaza ca nu detine destui bani pentru a cumpara toate produsele\n";
			cout << "Dezamagit, acesta alege sa nu cumpere nimic\n\n";
			cout << "Introdu \".\" pentru a continua \n";

			cin >> command;
			command = "SKIP";
		}
		else {
			cout << "Alege o comanda dintre urmatoarele:\n\n";
			cout << "BUY - Clientul va cumpara produsele in limita stocului\n";
			cout << "SKIP - Clientul nu va cumpara nimic\n\n";
			cout << "Introdu comanda aici: ";


			cin >> command;
			for (unsigned int i = 0; i < command.size(); ++i) {
				command[i] = toupper(command[i]);
			}

			while (command != "BUY" && command != "SKIP") {
				cout << "Ai introdus o comanda incorecta\n";
				cout << "Alege o comanda dintre urmatoarele:\n\n";
				cout << "BUY - Clientul va cumpara produsele in limita stocului\n";
				cout << "SKIP - Clientul nu va cumpara nimic\n\n";
				cout << "Introdu comanda aici: ";


				cin >> command;
				for (unsigned int i = 0; i < command.size(); ++i) {
					command[i] = toupper(command[i]);
				}
			}
		}
		if (command == "BUY") {

			separator();
			m.vindeProduse(clienti[i]);
			
			cout << "Clientul " << i + 1 << " a cumparat produsele disponibile din lista sa\n";
			cout << "Magazinul a incasat " << sumaNecesara << " lei\n";
			cout << "Clientul mai are " << clienti[i].getSuma() << " lei\n\n";
		
			if (i < numarClienti - 1) {
				cout << "Va urma urmatorul client\n\n";
			}

			cout << "Introdu \".\" pentru a continua \n";

			cin >> command;
		}
		else if (command == "SKIP") {
			separator();
			cout << "Clientul " << i + 1 << " a ales sa nu cumpere nimic\n\n";

			if (i < numarClienti - 1) {
				cout << "Va urma urmatorul client\n\n";
			}

			cout << "Introdu \".\" pentru a continua \n";

			cin >> command;
		}
		
		cout << '\n';
	}
	separator();
	cout << "S-a terminat simularea\n";
	cout << "Magazinul a incasat " << m.getProfitZi() << " lei in total in aceasta zi\n\n";
	cout << "Introdu \".\" pentru a continua \n";
	cin >> command;

	separator();

	cout << "Alege o comanda dintre urmatoarele:\n\n";
	cout << "MAIN - Revenire la meniul principal\n";
	cout << "EXIT - Terminarea programului\n\n";
	cout << "Introdu comanda aici: ";
	cin >> command;
	for (unsigned int i = 0; i < command.size(); ++i) {
		command[i] = toupper(command[i]);
	}

	while (command != "MAIN" && command != "EXIT") {
		cout << "Ai introdus o comanda incorecta\n";
		cout << "Alege o comanda dintre urmatoarele:\n\n";
		cout << "MAIN - Revenire la meniul principal\n";
		cout << "EXIT - Terminarea programului\n\n";
		cout << "Introdu comanda aici: ";


		cin >> command;
		for (unsigned int i = 0; i < command.size(); ++i) {
			command[i] = toupper(command[i]);
		}
	}

	if (command == "MAIN") {
		separator();
		meniuPrincipal();
	}
	else if (command == "EXIT") {
		separator();
		iesire();
	}
}

void meniuAfisare() {
	string command;

	cout << "Ce date vrei sa afisezi?\n";
	cout << "Alege o comanda dintre urmatoarele:\n\n";
	cout << "STORE - Afiseaza datele magazinului\n";
	cout << "CLIENTS - Afiseaza datele clientilor\n";
	cout << "MAIN - Revenire la meniul principal\n\n";

	cout << "Introdu comanda aici: ";
	cin >> command;
	for (unsigned int i = 0; i < command.size(); ++i) {
		command[i] = toupper(command[i]);
	}

	while (command != "STORE" && command != "MAIN" && command != "CLIENTS") {
		cout << "Ai introdus o comanda incorecta\n";
		cout << "Alege o comanda dintre urmatoarele:\n\n";
		cout << "STORE - Afiseaza datele magazinului\n";
		cout << "CLIENTS - Afiseaza datele clientilor\n";
		cout << "MAIN - Revenire la meniul principal\n\n";
		cout << "Introdu comanda aici: ";

		cin >> command;
		for (unsigned int i = 0; i < command.size(); ++i) {
			command[i] = toupper(command[i]);
		}
	}

	if (command == "STORE") {
		separator();
		cout << "Acestea sunt datele magazinului: \n\n";
		cout << m;
		separator();
		cout << "Alege o comanda dintre urmatoarele:\n\n";
		cout << "MAIN - Revenire la meniul principal\n";
		cout << "BACK - Revenire la meniul de afisare\n\n";
		cout << "Introdu comanda aici: ";
		cin >> command;
		for (unsigned int i = 0; i < command.size(); ++i) {
			command[i] = toupper(command[i]);
		}

		while (command != "BACK" && command != "MAIN") {
			cout << "Ai introdus o comanda incorecta\n";
			cout << "Alege o comanda dintre urmatoarele:\n\n";
			cout << "MAIN - Revenire la meniul principal\n";
			cout << "BACK - Revenire la meniul de afisare\n\n";
			cout << "Introdu comanda aici: ";

			cin >> command;
			for (unsigned int i = 0; i < command.size(); ++i) {
				command[i] = toupper(command[i]);
			}
		}
	}
	else if (command == "CLIENTS") {
		separator();
		cout << "Acestea sunt datele clientilor: \n\n";
		for (int i = 0; i < numarClienti; ++i) {
			cout << "Informatii client " << i + 1 << " din " << numarClienti << ":\n\n";
			cout << clienti[i];
			cout << "\n";
			separator();
		}
		separator();

		cout << "Alege o comanda dintre urmatoarele:\n\n";
		cout << "MAIN - Revenire la meniul principal\n";
		cout << "BACK - Revenire la meniul de afisare\n\n";
		cout << "Introdu comanda aici: ";
		cin >> command;
		for (unsigned int i = 0; i < command.size(); ++i) {
			command[i] = toupper(command[i]);
		}

		while (command != "BACK" && command != "MAIN") {
			cout << "Ai introdus o comanda incorecta\n";
			cout << "Alege o comanda dintre urmatoarele:\n\n";
			cout << "MAIN - Revenire la meniul principal\n";
			cout << "BACK - Revenire la meniul de afisare\n\n";
			cout << "Introdu comanda aici: ";

			cin >> command;
			for (unsigned int i = 0; i < command.size(); ++i) {
				command[i] = toupper(command[i]);
			}
		}
	}
	if (command == "MAIN") {
		separator();
		meniuPrincipal();
	}
	if (command == "BACK") {
		separator();
		meniuAfisare();
	}

}

void iesire() {
	delete[] clienti;
	cout << "Multumesc ca ai utilizat acest program!\n\n";
	exit(0);
}

void separator() {
	cout << "\n_________________________________________________\n\n";
}

void initializare() {
	m.initializeazaMagazin(20);
	numarClienti = 5;

	delete[] clienti;
	clienti = new Client[numarClienti];

	for (int i = 0; i < numarClienti; ++i) {
		clienti[i].initializareClient(i);

	}
}

int main() {

	initializare();
	cout << "||------------------------- MAGAZIN -------------------------||\n";
	cout << "Acest program simuleaza un magazin care vinde diverse produse la un numar de clienti in decursul unei zile.\n";
	cout << "Magazinul si clientii au fost initializate cu date default, dar pot fi modificate.\n\n";

	meniuPrincipal();

	
	delete[] clienti;
	return 0;
}
