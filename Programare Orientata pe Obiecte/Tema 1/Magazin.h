// Proiect realizat de Eduard-Cristian Podaru, grupa 131, pentru tema 1 de la laboratorul de POO
// Programul a fost testat si ruleaza corect pe Microsoft Visual Studio Community 2019, 
// cu compilatorul care vine default cu instalarea workload-ului "Desktop Development for C++", si anume MSVC/Visual C++ Compiler
// Programul simuleaza un magazin, folosind POO
#pragma once								// In acest fisier am implementat clasele folosite
					

#include <string>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

class Produs {								// Clasa care modeleaza produsele magazinului

	private:								// Membrele tara, anCulegere, tip, denumire servesc pentru a substitui momentan mostenirea
											
		int pret;							// Pretul per unitatea corespunzatoare
		int numar;							// Numarul de produse in stoc/lista clientului
		
		string nume;						// Denumirea produsului
		string unitate;						// Retine daca produsul se vinde la KG, la L sau la bucata(BUC)
		string tip = "nu";					// Tipul produsului, unde este cazul(faina, bere, vin etc)
		string tara = "nu";					// Tara de culegere in cazul vinului
		string denumire = "nu";				// Numele jucariei/brandul vinului/berii
		string anCulegere = "nu";			// Anul in care a fost cules in cazul vinului de soi

		char apartenenta = 'm';				// Are valaorea 'm' sau 'c' care determina daca apartine stocului magazinului sau listei unui client
											// Folosit pentru a ajuta la formatarea afisarii cu operatorii << si >>, pentru a afisa stocul magazinului/lista unui client
											// Am ales sa implementez astfel pentru a substitui mostenirea clasei Produs
											// In viitor, as mosteni clasa Produs pentru crea o clasa ProdusListaClient care supraincarca operatorii suparincarcati in Produs
											// Iar clasa Magazin ar avea ca membra o lista de tip Produs*, 
											// In timp ce clasa Client ar avea ca membra o lista de tip ProdusListaClient*
	public:

#pragma region Getters
		int getPret() {
			return pret;
		}

		int getNumar() {
			return numar;
		}

		string getAnCulegere() {
			return anCulegere;
		}

		string getNume() {
			return nume;
		}

		string getUnitate() {
			return unitate;
		}

		string getTip() {
			return tip;
		}

		string getDenumire() {
			return denumire;
		}

		string getTara() {
			return tara;
		}

		char getApartenenta() {
			return apartenenta;
		}

#pragma endregion

#pragma region Setters
		void setPret(int price) {
			pret = price;
		}

		void setNumar(int nr) {
			numar = nr;
		}

		void setAnCulegere(string an) {
			anCulegere = an;
		}

		void setNume(string name) {
			nume = name;
		}

		void setUnitate(string unit) {
			unitate = unit;
		}

		void setTip(string type) {
			tip = type;
		}

		void setDenumire(string name) {
			denumire = name;
		}
		
		void setTara(string country) {
			tara = country;
		}

		void setApartenenta(char owner) {
			apartenenta = owner;
		}


#pragma endregion

#pragma region Methods

		int pretTotal() {
			return numar * pret;
		}

#pragma endregion

#pragma region Operators

		
		Produs operator=(Produs produs) {
			if (this != &produs) {

				this->nume = produs.nume;
				this->pret = produs.pret;
				this->tip = produs.tip;
				this->numar = produs.numar;

				this->unitate = produs.unitate;
				this->denumire = produs.denumire;
				this->anCulegere = produs.anCulegere;
				this->tara = produs.tara;

			}
			return *this;
		}

		Produs operator-=(int nrVandut) {

			this->numar -= nrVandut;
			if (numar < 0) {
				numar = 0;
			}
			return *this;
		}

		friend bool operator==(const Produs& produs1, const Produs& produs2);
		friend bool operator<=(const Produs& produs1, const Produs& produs2);
		friend istream& operator>>(istream& in, Produs& produs);
		friend ostream& operator<<(ostream& out, Produs& produs);

#pragma endregion

#pragma region Constructors

		Produs() {							// Pentru un produs gol, trebuie modificate datele dupa construire pentru a avea folos

			numar = 0;
			pret = 0;
			anCulegere = "nu";

			nume = "";
			unitate = "BUC";

		}

		Produs(string name, int price, string unit, int stock, string type = "nu", string brand = "nu", string year = "nu", string country = "nu") {
			// Constructor pentru un produs cu toate datele necesare, se pot omite ultimele pentru produse care nu necesita acele membre
			// (deoarece ele substituie momentan mostenirea clasei produs)
			nume = name;
			pret = price;
			unitate = unit;
			numar = stock;

			tip = type;
			tara = country;
			denumire = brand;
			anCulegere = year;
		}

		Produs(char owner) {				// Pentru a creea un produs care urmeaza sa fie introdus in lista clientului
			apartenenta = owner;
			numar = 0;
			pret = 0;
			anCulegere = "nu";

			nume = "";
			unitate = "BUC";
		}

		Produs(const Produs &prod) {

			nume = prod.nume;
			pret = prod.pret;
			unitate = prod.unitate;
			numar = prod.numar;

			tip = prod.tip;
			tara = prod.tara;
			denumire = prod.denumire;
			anCulegere = prod.anCulegere;
			apartenenta = prod.apartenenta;
		}

#pragma endregion

#pragma region Destructor
		~Produs() {
			// cout<<"Produs Distrus\n";
		}
#pragma endregion

};

#pragma region Produs Operators

bool operator==(const Produs& produs1, const Produs& produs2) {
	// Verifica daca 2 obiecte produs contin aceleasi valori, inafara de apartenenta 
	bool egal;

	if (produs1.nume == produs2.nume && produs1.pret == produs2.pret && produs1.tip == produs2.tip && produs1.numar == produs2.numar && produs1.unitate == produs2.unitate && produs1.denumire == produs2.denumire && produs1.tara == produs2.tara && produs1.anCulegere == produs2.anCulegere)
	{
		egal = true;
	}
	else {
		egal = false;
	}
	return egal;
}

bool operator<=(const Produs& produs1, const Produs& produs2) {
	// produs1 trebuie sa aiba apartenenta 'c', iar produs2 trebuie sa aiba apartenenta 'm' ca sa aiba folos operatorul acesta.
	// Folosit pentru a verifica daca produsul cerut de un client se afla in magazin, prin comparatia produselor din magazin cu cel apelant, in felul urmator:
	// Pentru produs1:
	// Membrele tip,denumire, tara care au valoarea "nu" nu se iau in considerare,
	// Membrul anCulegere nu se ia in considerare daca e = 0,
	// Membrele unitate si pret nu se iau in considerare, acestea trebuind sa fie setate dupa folosirea operatorului <=

	bool maiMic = true;

	if (produs1.nume == produs2.nume) {

		if (produs1.tip != "") {
			if (produs1.tip != produs2.tip) {
				maiMic = false;
			}
		}
		
		if (produs1.denumire != "") {
			if (produs1.denumire != produs2.denumire) {
				maiMic = false;
			}
		}

		if (produs1.nume == "vin") {

			if (produs1.tara != "") {
				if (produs1.tara != produs2.tara) {
					maiMic = false;
				}
			}

			if (produs1.anCulegere != "") {
				if (produs1.anCulegere != produs2.anCulegere) {
					maiMic = false;
				}
			}
		}
	}
	else {
		maiMic = false;
	}

	return maiMic;
}

istream& operator>>(istream& in, Produs& produs) {
	string aux;

	if (produs.apartenenta == 'm') {
		cout << "Produs: ";
		in >> aux;											// In caz ca utilizatorul nu introduce litere mici, folosim tolower pe ce a introdus
		produs.nume = "";
		for (unsigned int i = 0; i < aux.size(); ++i) {
			produs.nume += tolower(aux[i]);
		}

		cout << "Pret: ";
		in >> produs.pret;
		
		cout << "Unitatea de masura(BUC/KG/L): ";
		in >> aux;											// In caz ca utilizatorul nu introduce litere mari, folosim toupper pe ce a introdus
		produs.unitate = "";
		for (unsigned int i = 0; i < aux.size(); ++i) {
			produs.unitate += toupper(aux[i]);
		}

		cout << "Numar: ";
		in >> produs.numar;

		cout << "Tip produs(sau \"nu\"): ";
		in.ignore();
		getline(in, aux);											// In caz ca utilizatorul nu introduce litere mici, folosim tolower pe ce a introdus
		produs.tip = "";
		for (unsigned int i = 0; i < aux.size(); ++i) {
			produs.tip += tolower(aux[i]);
		}

		cout << "Denumire/brand(sau \"nu\"): ";
		getline(in, produs.denumire);

		if (produs.nume == "vin" && produs.denumire != "nu") {
			cout << "Anul culegerii: ";
			in >> produs.anCulegere;

			cout << "Tara de origine: ";
			in >> produs.tara;
		}
		else {
			produs.anCulegere = "nu";
			produs.tara = "nu";
		}
	}

	else {
		cout << "Produs: ";
		in >> aux;											// In caz ca utilizatorul nu introduce litere mici, folosim tolower pe ce a introdus
		produs.nume = "";
		for (unsigned int i = 0; i < aux.size(); ++i) {
			produs.nume += tolower(aux[i]);
		}

		cout << "Tip produs(sau \"nu\" pentru a nu specifica): ";
		in.ignore();
		getline(in, aux);											// In caz ca utilizatorul nu introduce litere mici, folosim tolower pe ce a introdus
		produs.tip = "";
		for (unsigned int i = 0; i < aux.size(); ++i) {
			produs.tip += tolower(aux[i]);
		}

		cout << "Denumire/brand(sau \"nu\" pentru a nu specifica): ";
		getline(in, produs.denumire);
	
		if (produs.nume == "vin" && produs.denumire != "nu") {
			cout << "Anul culegerii(sau \"nu\" pentru a nu specifica): ";
			in >> produs.anCulegere;

			cout << "Tara de origine(sau \"nu\" pentru a nu specifica): ";
			in >> produs.tara;
		}
		else {
			if (produs.nume == "vin") {
				produs.unitate = "L";
			}
			produs.anCulegere = "nu";
			produs.tara = "nu";
		}

		cout << "Numar: ";
		in >> produs.numar;
		
		if (produs.tip == "nu") {
			produs.tip = "";
		}
		if (produs.denumire == "nu") {
			produs.denumire = "";
		}
		if (produs.anCulegere == "nu") {
			produs.anCulegere = "";
		}
		if (produs.tara == "nu") {
			produs.tara = "";
		}
	}

	return in;
}

ostream& operator<<(ostream& out, Produs& produs) {
	// Aceasta implementare hard-coded substituie momentan supraincarcarea operatorilor unor clase mostenite
	string numeAux;

	numeAux = produs.nume;
	numeAux[0] = toupper(numeAux[0]);

	if (produs.apartenenta == 'm') {
		
		if (produs.nume == "varza") {
			//fara tip sau denumire
			out << '\n' << numeAux << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numar << " ramase in stoc";

		}

		if (produs.nume == "cartofi" || produs.nume == "faina") {
			//Au aceeasi structura, au tip
			if (produs.nume == "faina") {
				out << '\n' << numeAux << " de calitate " << produs.tip << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numar << " ramase in stoc";
			}
			else {
				out << '\n' << numeAux << ' ' << produs.tip << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numar << " ramase in stoc";
			}
		}


		if (produs.nume == "bere") {
			//are tip blonda/bruna si denumire
			out << '\n' << numeAux << ' ' << produs.tip << ' ' << produs.denumire << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numar << " ramase in stoc";
		}

		if (produs.nume == "jucarie") {
			//are denumire
			out << '\n' << numeAux << ' ' << produs.denumire << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numar << " ramase in stoc";

		}

		if (produs.nume == "vin") {
			//are tip rosu/alb
			if (produs.unitate == "BUC") {
				//Vin de soi, are denumire, anculegere si tara
				out << '\n' << numeAux << ' ' << produs.tip << ' ' << produs.denumire << " din " << produs.tara << " cules in " << produs.anCulegere << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numar << " ramase in stoc";

			}

			if (produs.unitate == "L") {
				//Vin varsat
				out << '\n' << numeAux << " varsat " << produs.tip << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numar << " ramase in stoc";

			}
		}
	}
	else {
		if (produs.nume == "varza") {
			//fara tip sau denumire
			out << '\n' << produs.numar << ' ' << produs.unitate << ' ' << numeAux << " - "<<produs.pretTotal()<<" lei";
		
		}

		if (produs.nume == "cartofi" || produs.nume == "faina") {
			//Au aceeasi structura, au tip
			if (produs.nume == "faina") {
				out << '\n' << produs.numar << ' ' << produs.unitate << ' ' << numeAux << ' ' << produs.tip << " - " << produs.pretTotal() << " lei";
			
			}
			else {
				out << '\n' << produs.numar << ' ' << produs.unitate << ' ' << numeAux << ' ' << produs.tip << " - " << produs.pretTotal() << " lei";
			
			}
		}


		if (produs.nume == "bere") {
			//are tip blonda/bruna si denumire
			out << '\n' << produs.numar << ' ' << produs.unitate << ' ' << numeAux << ' ' << produs.tip << ' ' << produs.denumire << " - " << produs.pretTotal() << " lei";
		
		}

		if (produs.nume == "jucarie") {
			//are denumire
			out << '\n' << produs.numar << ' ' << produs.unitate << ' ' << numeAux << ' ' << produs.denumire << " - " << produs.pretTotal() << " lei";
		
		}

		if (produs.nume == "vin") {
			//are tip rosu/alb
			if (produs.unitate == "BUC") {
				//Vin de soi, are denumire, anculegere si tara
				out << '\n' << produs.numar << ' ' << produs.unitate << ' ' << numeAux << ' ' << produs.tip << ' ' << produs.denumire<< " din " << produs.tara << " cules in " << produs.anCulegere << " - " << produs.pretTotal() << " lei";

			}

			if (produs.unitate == "L") {
				//Vin varsat
				out << '\n' << produs.numar <<' '<< produs.unitate << ' ' << numeAux << " varsat " << produs.tip << " - " << produs.pretTotal() << " lei";

			}
		}
	}
	return out;
}



#pragma endregion



class Client {


private:

	int suma;							// Suma de bani pe care o detine clientul
	int numarCumparaturi;				// Numarul de iteme din lista de cumparaturi

	Produs* lista = NULL;					// Lista de cumparaturi a clientului

public:


#pragma region Getters 
	int getSuma() {
		return suma;
	}

	int getNumarCumparaturi() {
		return numarCumparaturi;
	}

	Produs* getLista() {
		return lista;
	}
#pragma endregion

#pragma region Setters
	void setSuma(int sum) {
		suma = sum;
	}

	void setNumarCumparaturi(int nr) {
		numarCumparaturi = nr;
	}
#pragma endregion


#pragma region Constructors

	Client() {
		suma = 100;
		numarCumparaturi = 0;
		lista = NULL;
	}


	Client(int sum, int nr) {
		suma = sum;
		numarCumparaturi = nr;

		delete[] lista;
		lista = new Produs[numarCumparaturi];

	}


	Client(const Client& client) {
		suma = client.suma;
		numarCumparaturi = client.numarCumparaturi;

		delete[] lista;
		lista = new Produs[client.numarCumparaturi];

		for (int i = 0; i < client.numarCumparaturi; ++i) {
			lista[i] = client.lista[i];
		}

	}

#pragma endregion

#pragma region Destructor
	~Client() {
		delete[] lista;
		//cout<<"Client distrus\n";
	}
#pragma endregion

#pragma region Methods

	void afiseazaLista() {
		cout << "Lista de cumparaturi:\n";

		for (int i = 0; i < numarCumparaturi; ++i) {
			cout << lista[i];
		}
		
	}
	void initializareClient(int index) {					// Metoda pentru a initializa arrayul de clienti din main cu niste clienti predefiniti


		Produs produse[20] = {

			Produs("varza",5,"BUC",2),
			Produs("cartofi",2,"KG",1,"rosii"),
			Produs("cartofi",3,"KG",3,"albi"),
			Produs("faina",2,"KG",2,"I"),
			Produs("faina",3,"KG",1,"II"),
			Produs("faina",5,"KG",1,"III"),
			Produs("vin",8,"L",5,"rosu sec"),
			Produs("vin",8,"L",7,"rosu dulce"),
			Produs("bere",5,"BUC",3,"bruna","Silva"),
			Produs("bere", 6,"BUC",6,"blonda","Ciuc Radler"),
			Produs("vin",12,"BUC",2,"alb sec","Cotnari","2020","Romania"),
			Produs("vin",15,"BUC",1,"rosu dulce","Merlot","2015","Franta"),
			Produs("jucarie",15,"BUC",1,"nu","Teddy Bear"),
			Produs("jucarie",20,"BUC",2,"nu","Figurina Transformer"),
			Produs("bere",7,"BUC",6,"bruna","Stejar"),
			Produs("vin",16,"BUC",1,"rosu sec","Cabernet Savignon","2016","Franta"),
			Produs("jucarie",25,"BUC",1,"nu","Papusa Barbie"),
			Produs("jucarie",50,"BUC",3,"nu","Masina Teleghidata"),
			Produs("vin",8,"L",10,"alb dulce"),
			Produs("jucarie",70,"BUC",1,"nu","Set Lego"),
		};

		Client clienti[5] = {
			Client(300,3),
			Client(250,4),
			Client(100,2),
			Client(500,5),
			Client(175,3)
		};

		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < clienti[i].numarCumparaturi; ++j) {
				clienti[i].lista[j].setApartenenta('c');
			}
		}

		clienti[0].lista[0] = produse[3]; clienti[0].lista[1] = produse[6]; clienti[0].lista[2] = produse[8];
		clienti[1].lista[0] = produse[1]; clienti[1].lista[1] = produse[0]; clienti[1].lista[2] = produse[5]; clienti[1].lista[3] = produse[1];
		clienti[2].lista[0] = produse[2]; clienti[2].lista[1] = produse[3];
		clienti[3].lista[0] = produse[10]; clienti[3].lista[1] = produse[12]; clienti[3].lista[2] = produse[9]; clienti[3].lista[3] = produse[11]; clienti[3].lista[4] = produse[17];
		clienti[4].lista[0] = produse[4]; clienti[4].lista[1] = produse[7]; clienti[4].lista[2] = produse[13];

		this->suma = clienti[index].suma;
		this->numarCumparaturi = clienti[index].numarCumparaturi;

		delete[] this->lista;
		this->lista = new Produs[this->numarCumparaturi];

		for (int i = 0; i < this->numarCumparaturi; ++i) {
			this->lista[i] = clienti[index].lista[i];
			this->lista[i].setApartenenta('c');
		}
	}


#pragma endregion

#pragma region Operators

	friend istream& operator>>(istream& in, Client& client);
	friend ostream& operator<<(ostream& out, Client& client);

#pragma endregion

};

#pragma region Client Operators

istream& operator>>(istream& in, Client& client) {

	cout << "\nIntrodu suma de bani detinuta: ";
	in >> client.suma;

	cout << "\nIntrodu numarul de produse din lista de cumparaturi: ";
	in >> client.numarCumparaturi;

	delete[] client.lista;

	client.lista = new Produs[client.numarCumparaturi];
	for (int i = 0; i < client.numarCumparaturi; ++i) {
		client.lista[i].setApartenenta('c');

	}

	for (int i = 0; i < client.numarCumparaturi; ++i) {
		cout << "\nInformatii produs " << i + 1 << " din " << client.numarCumparaturi << ":\n";
		in >> client.lista[i];
	}

	return in;
}

ostream& operator<<(ostream& out, Client& client) {

	out << "Suma de bani detinuta: " << client.suma << '\n';
	out << "Numarul de produse din lista de cumparaturi: " << client.numarCumparaturi << "\n\n";

	out << "Lista de cumparaturi:\n";

	for (int i = 0; i < client.numarCumparaturi; ++i) {
		out << client.lista[i];
	}
	return out;
}
#pragma endregion

class Magazin {								// Clasa care modeleaza magazinul

	private:

		Produs* stoc;						// Lista de produse valabile in stoc

		int profitZi;						// Profitul total de la finalul zilei
		int numarProduse;

		
	public:

#pragma region Getters

	int getProfitZi() {
		return profitZi;
	}

	int getNumarProduse() {
		return numarProduse;
	}

#pragma endregion

#pragma region Setters

	void setProfitZi(int profit) {
		profitZi = profit;
	}

	void setNumarProduse(int number) {
		numarProduse = number;
	}

#pragma endregion

#pragma region Methods

	void initializeazaMagazin(int nrProduse) {
		// Metoda care initializeaza magazinul cu un numar dat de produse diferite in stoc
		Produs produse[20] = {

			Produs("varza",5,"BUC",60),
			Produs("cartofi",2,"KG",75,"rosii"),
			Produs("cartofi",3,"KG",45,"albi"),
			Produs("faina",2,"KG",75,"I"),
			Produs("faina",3,"KG",75,"II"),
			Produs("faina",5,"KG",75,"III"),			
			Produs("vin",8,"L",120,"rosu sec"),
			Produs("vin",8,"L",110,"rosu dulce"),
			Produs("bere",5,"BUC",85,"bruna","Silva"),
			Produs("bere", 6,"BUC",90,"blonda","Ciuc Radler"),
			Produs("vin",12,"BUC",50,"alb sec","Cotnari","2020","Romania"),
			Produs("vin",15,"BUC",40,"rosu dulce","Merlot","2015","Franta"),
			Produs("jucarie",15,"BUC",30,"nu","Teddy Bear"),
			Produs("jucarie",20,"BUC",25,"nu","Figurina Transformer"),
			Produs("bere",7,"BUC",60,"bruna","Stejar"),
			Produs("vin",16,"BUC",35,"rosu sec","Cabernet Savignon","2016","Franta"),
			Produs("jucarie",25,"BUC",40,"nu","Papusa Barbie"),
			Produs("jucarie",50,"BUC",20,"nu","Masina Teleghidata"),
			Produs("vin",8,"L",120,"alb dulce"),
			Produs("jucarie",70,"BUC",25,"nu","Set Lego"),

		};

		profitZi = 0;

		numarProduse = nrProduse;

		delete[] stoc;
		stoc = new Produs[nrProduse];

		for (int i = 0; i < nrProduse; ++i) {
			stoc[i] = produse[i];
		}


	}

	void afiseazaStoc() {								// Metoda care afiseaza stocul magazinului
		for (int i = 0; i < numarProduse; ++i) {
			cout << stoc[i];
		}
		cout << '\n';
	}

	int verificaLista(Produs* lista, int nrProduse) {	// Metoda care verifica daca magazinul detine toate produsele din lista clientului
		int sum = 0;									// Si returneaza suma totala a produselor din lista pe care le poate cumpara
														//(in limita stocului)
		for (int i = 0; i < nrProduse; ++i) {
			
			bool gasit = false;
			int j;
			for(j = 0; j < numarProduse; ++j){
				if (lista[i] <= stoc[j]) {
					gasit = true;
					break;
				}
			}

			if (gasit) {
				lista[i].setPret(stoc[j].getPret());
				lista[i].setUnitate(stoc[j].getUnitate());
				if (lista[i].getNume() == "vin" && lista[i].getUnitate() == "BUC"){
					lista[i].setDenumire(stoc[j].getDenumire());
					lista[i].setTip(stoc[j].getTip());
					lista[i].setAnCulegere(stoc[j].getAnCulegere());
					lista[i].setTara(stoc[j].getTara());
				}
				if (lista[i].getNumar() <= stoc[j].getNumar()) {
					sum += lista[i].pretTotal();
				}
				else {
					sum += stoc[j].pretTotal();
				}
			}

		}

		return sum;
	}

	void vindeProduse(Client& client) {			// Functie care vinde produse din stoc clientului si sterge din lista sa de cumparaturi produsele care nu sunt in stoc 

		int sum = 0;
		int nrLista = client.getNumarCumparaturi();
		Produs* listaClient = client.getLista();
		queue<int> deEliminat;

		for (int i = 0; i < nrLista; ++i) {

			bool gasit = false;
			int j;
			
			for (j = 0; j < numarProduse; ++j) {
				if (listaClient[i] <= stoc[j]) {
					gasit = true;
					break;
				}
			}

			if (gasit) {
				listaClient[i].setPret(stoc[j].getPret());
				listaClient[i].setUnitate(stoc[j].getUnitate());
				if (listaClient[i].getNumar() <= stoc[j].getNumar()) {
					sum += listaClient[i].pretTotal();
					stoc[j] -= listaClient[i].getNumar();
				}
				else {
					sum += stoc[j].pretTotal();
					listaClient[i].setNumar(stoc[j].getNumar());
					stoc[j].setNumar(0);
				}
			}
			else {
				deEliminat.push(i);
			}	
		}

	
		for (int i = 0; i < nrLista; ++i) {
			if (deEliminat.empty()) {
				break;
			}
			if(i == deEliminat.front()) {
				for (int j = i; j < nrLista - 1; ++j) {
					listaClient[j] = listaClient[j + 1];
				}
				--nrLista;
				deEliminat.pop();
			}
		}
		client.setNumarCumparaturi(nrLista);
		client.setSuma(client.getSuma() - sum);
		this->profitZi += sum;
	}

#pragma endregion

#pragma region Operators 

	Magazin& operator=(Magazin& magazin) {					// Supraincarcam si operatorul de atribuire pentru a avea fiecare un stoc propriu
		if (this != &magazin) {

			this->profitZi = magazin.profitZi;
			this->numarProduse = magazin.numarProduse;

			delete[] stoc;
			stoc = new Produs[magazin.numarProduse];

			for (int i = 0; i < magazin.numarProduse; ++i) {
				stoc[i] = magazin.stoc[i];
			}
		}
		return *this;
	}

	Magazin& operator+=(int suma) {							// Supraincarcare a lui += pentru a adauga la profit
		
		profitZi += suma;
		return *this;
	}

	friend istream& operator>>(istream& in, Magazin& magazin);
	friend ostream& operator<<(ostream& out, Magazin& magazin);

#pragma endregion

#pragma region Constructors

	Magazin() {
		
		profitZi = 0;
		numarProduse = 0;

		stoc = NULL;
	}

	Magazin(int number, int profit = 0) {
		// Constructor pentru magazin cu lista goala de number produse

		profitZi = profit;
		numarProduse = number;
		
		delete[] stoc;
		stoc = new Produs[number];

	}

	Magazin(int number, Produs produse[], int profit = 0) {
		// Constructor pentru magazin cu number produse, care primeste un array de produse cu care sa initializeze stocul

		profitZi = profit;
		numarProduse = number;

		delete[] stoc;
		stoc = new Produs[number];

		for (int i = 0; i < number; ++i) {
			stoc[i] = produse[i];
		}
		
	}

	Magazin(const Magazin &mag) {						// Constructor de copiere
														// Redefinit pentru a nu avea 2 obicte magazin care acceseaza acelasi array in memorie
		profitZi = mag.profitZi;
		numarProduse = mag.numarProduse;

		delete[] stoc;
		stoc = new Produs[mag.numarProduse];

		for (int i = 0; i < numarProduse; ++i) {
			stoc[i] = mag.stoc[i];
		}
	}

#pragma endregion

#pragma region Destructor 

	~Magazin() {
		delete[] stoc;
		//cout << "Magazin distrus\n";
	}

#pragma endregion

};

#pragma region Magazin Operators

istream& operator>>(istream& in, Magazin& magazin) {
	
	cout << "Seteaza profitul: ";
	in >> magazin.profitZi;

	cout << "Numarul de produse diferite: ";
	in >> magazin.numarProduse;

	delete[] magazin.stoc;

	magazin.stoc = new Produs[magazin.numarProduse];

	for (int i = 0; i < magazin.numarProduse; ++i) {
		cout << "Informatii produs "<<i+1<<" din " << magazin.numarProduse << ":\n";
		in >> magazin.stoc[i];
		cout << '\n';
	}

	return in;
}

ostream& operator<<(ostream& out, Magazin& magazin) {
	
	out << "Profitul zilei: " << magazin.profitZi << '\n';
	out << "Numarul de produse diferite: " << magazin.numarProduse << '\n';
	out << "Lista de produse oferite:\n";

	for (int i = 0; i < magazin.numarProduse; ++i) {
		out << magazin.stoc[i];
	}
	
	
	return out;
}

#pragma endregion