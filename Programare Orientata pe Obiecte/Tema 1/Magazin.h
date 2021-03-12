#pragma once					// In acest fisier am implementat clasele folosite
					

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Produs {								// Clasa care modeleaza produsele magazinului

	private:								// Membrele tara, anCulegere, tip, denumire servesc pentru a substitui momentan mostenirea
											
		int pret;							// Pretul per unitatea corespunzatoare
		int numarStoc;						// Numarul de produse de acest tip in stoc
		int anCulegere = 0;					// Anul in care a fost cules in cazul vinului de soi

		string nume;						// Denumirea produsului
		string unitate;						// Retine daca produsul se vinde la KG, la L sau la bucata(BUC)
		string tip = "nu";					// Tipul produsului, unde este cazul(faina, bere, vin etc)
		string tara = "nu";					// Tara de culegere in cazul vinului
		string denumire = "nu";				// Numele jucariei/brandul vinului/berii

	public:

#pragma region Getters
		int getPret() {
			return pret;
		}

		int getNumarStoc() {
			return numarStoc;
		}

		int getAnCulegere() {
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
#pragma endregion

#pragma region Setters
		void setPret(int price) {
			pret = price;
		}

		void setNumarStoc(int nr) {
			numarStoc = nr;
		}

		void setAnCulegere(int an) {
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

#pragma endregion

#pragma region Operators

		Produs operator=(Produs produs) {
			if (this != &produs) {

				this->nume = produs.nume;
				this->pret = produs.pret;
				this->tip = produs.tip;
				this->numarStoc = produs.numarStoc;

				this->unitate = produs.unitate;
				this->denumire = produs.denumire;
				this->anCulegere = produs.anCulegere;
				this->tara = produs.tara;

			}
			return *this;
		}

		Produs operator-=(int nrVandut) {

			this->numarStoc -= nrVandut;
			if (numarStoc < 0) {
				numarStoc = 0;
			}
			return *this;
		}

		friend istream& operator>>(istream& in, Produs& produs);
		friend ostream& operator<<(ostream& out, Produs& produs);

#pragma endregion

#pragma region Constructors

		Produs() {							// Pentru un produs gol, trebuie modificate datele dupa construire pentru a avea folos

			numarStoc = 0;
			pret = 0;
			anCulegere = 0;

			nume = "";
			unitate = "BUC";

		}

		Produs(string name, int price, string unit, int stock, string type = "nu", string brand = "nu", int year = 0, string country = "nu") {
			// Constructor pentru un produs cu toate datele necesare, se pot omite ultimele pentru produse care nu necesita acele membre
			// (deoarece ele substituie momentan mostenirea clasei produs)
			nume = name;
			pret = price;
			unitate = unit;
			numarStoc = stock;

			tip = type;
			tara = country;
			denumire = brand;
			anCulegere = year;
		}

		Produs(const Produs &prod) {

			nume = prod.nume;
			pret = prod.pret;
			unitate = prod.unitate;
			numarStoc = prod.numarStoc;

			tip = prod.tip;
			tara = prod.tara;
			denumire = prod.denumire;
			anCulegere = prod.anCulegere;
		}

#pragma endregion

#pragma region Destructor
		~Produs() {
			// cout<<"Produs Distrus\n";
		}
#pragma endregion

};

#pragma region Produs Operators

istream& operator>>(istream& in, Produs& produs) {
	string aux;

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

	cout << "Numar in stoc: ";
	in >> produs.numarStoc;

	cout << "Tip produs(sau \"nu\" daca nu are):";
	in.ignore();
	getline(in, aux);											// In caz ca utilizatorul nu introduce litere mici, folosim tolower pe ce a introdus
	produs.tip = "";
	for (unsigned int i = 0; i < aux.size(); ++i) {
		produs.tip += tolower(aux[i]);
	}

	cout << "Denumire/brand(sau \"nu\" daca nu are): ";
	getline(in, produs.denumire);

	if (produs.nume == "vin" && produs.unitate == "BUC") {
		cout << "Anul culegerii: ";
		in >> produs.anCulegere;

		cout << "Tara de origine: ";
		in >> produs.tara;
	}
	else {
		produs.anCulegere = 0;
		produs.tara = "nu";
	}

	return in;
}

ostream& operator<<(ostream& out, Produs& produs) {
	// Aceasta implementare hard-coded substituie momentan supraincarcarea operatorilor unor clase mostenite
	string numeAux;

	numeAux = produs.nume;
	numeAux[0] = toupper(numeAux[0]);
														
	if (produs.nume == "varza") {
		//fara tip sau denumire
		out << '\n' << numeAux << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numarStoc << " ramase in stoc";

	}
	
	if (produs.nume == "cartofi" || produs.nume =="faina") {
		//Au aceeasi structura, au tip
		if (produs.nume == "faina") {
			out << '\n' << numeAux << " de calitate " << produs.tip << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numarStoc << " ramase in stoc";
		}
		else {
			out << '\n' << numeAux << ' ' << produs.tip << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numarStoc << " ramase in stoc";
		}
	}
	
	
	if (produs.nume == "bere") {
		//are tip blonda/bruna si denumire
		out << '\n' << numeAux << ' ' << produs.tip <<' '<< produs.denumire<< ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numarStoc << " ramase in stoc";
	}

	if (produs.nume == "jucarie") {
		//are denumire
		out << '\n' << numeAux << ' ' << produs.denumire << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numarStoc << " ramase in stoc";

	}

	if (produs.nume == "vin") {
		//are tip rosu/alb
		if (produs.unitate == "BUC") {
			//Vin de soi, are denumire, anculegere si tara
			out << '\n' << numeAux << ' ' << produs.tip << ' ' << produs.denumire << " din " << produs.tara << " cules in " << produs.anCulegere << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numarStoc << " ramase in stoc";

		}
		
		if (produs.unitate == "L") {
			//Vin varsat
			out << '\n' << numeAux << " varsat " << produs.tip << ": " << produs.pret << " lei pe " << produs.unitate << "; " << produs.numarStoc << " ramase in stoc";

		}
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
		Produs produse[16] = {

			Produs("varza",5,"BUC",60),
			Produs("cartofi",2,"KG",75,"rosii"),
			Produs("cartofi",3,"KG",45,"albi"),
			Produs("vin",8,"L",120,"rosu sec"),
			Produs("vin",8,"L",110,"rosu dulce"),
			Produs("bere", 6,"BUC",90,"blonda","Ciuc Radler"),
			Produs("bere",5,"BUC",85,"bruna","Silva"),
			Produs("vin",12,"BUC",50,"alb sec","Cotnari",2020,"Romania"),
			Produs("vin",15,"BUC",40,"rosu dulce","Merlot",2015,"Franta"),
			Produs("jucarie",50,"BUC",20,"nu","Masina Teleghidata"),
			Produs("jucarie",25,"BUC",40,"nu","Papusa Barbie"),
			Produs("bere",7,"BUC",60,"bruna","Stejar"),
			Produs("vin",16,"BUC",35,"rosu sec","Cabernet Savignon",2016,"Franta"),
			Produs("jucarie",15,"BUC",30,"nu","Teddy Bear"),
			Produs("jucarie",20,"BUC",25,"nu","Figurina Transformer"),
			Produs("vin",8,"L",120,"alb dulce"),

		};

		profitZi = 0;

		numarProduse = nrProduse;

		delete[] stoc;
		stoc = new Produs[nrProduse];

		for (int i = 0; i < nrProduse; ++i) {
			stoc[i] = produse[i];
		}


	}

	void afiseazaStoc() {
		for (int i = 0; i < numarProduse; ++i) {
			cout << stoc[i];
		}
		cout << '\n';
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

	out << "Numarul de produse diferite: " << magazin.numarProduse<<'\n';
	
	for (int i = 0; i < magazin.numarProduse; ++i) {
		out << magazin.stoc[i];
		out << '\n';
	}
	out << "Profitul zilei: " << magazin.profitZi<<'\n';
	
	return out;
}

#pragma endregion


class ItemLista {							// Clasa care modeleaza produsele din lista de cumparaturi a unui client
	
	private:

		int cantitate;						// Numarul de produse
		
		string nume;						// Denumirea produselor
		string unitate;						// KG/L/BUC

	public:

#pragma region Getters

		int getCantitate() {
			return cantitate;
		}

		string getNume() {
			return nume;
		}

		string getUnitate() {
			return unitate;
		}
#pragma endregion

#pragma region Setters

		void setCantitate(int quantity) {
			cantitate = quantity;
		}

		void setNume(string name) {
			nume = name;
		}

		void setUnitate(string unit) {
			unitate = unit;
		}
#pragma endregion

#pragma region Constructors

		ItemLista() {
			
			nume = "";
			cantitate = 0;
			unitate = "BUC";
		}

		ItemLista(string name, int quantity, string unit) {
			nume = name;
			cantitate = quantity;
			unitate = unit;
		}

		ItemLista(const ItemLista& item) {

			
			nume = item.nume;
			cantitate = item.cantitate;
			unitate = item.unitate;
		}

#pragma endregion 

#pragma region Destructor
		~ItemLista() {
			//cout << "Item din lista distrus\n";
		}
#pragma endregion

};


class Client {

	
	private:
		
		int suma;							// Suma de bani pe care o detine clientul
		int numarCumparaturi;				// Numarul de iteme din lista de cumparaturi

		ItemLista* lista;					// Lista de cumparaturi a clientului
		
	public:
		
		Client() {

			string x;
			int nrElemente = 0;
			do {
				cin >> x;
				++nrElemente;
			} while (x != "gata");

			lista = new ItemLista[nrElemente];
			for (int i = 0; i < nrElemente; ++i) {
				lista[i] = ItemLista();
			}
			numarCumparaturi = nrElemente;
		}

#pragma region Getters 
		int getSuma() {
			return suma;
		}

		int getNumarCumparaturi() {
			return numarCumparaturi;
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

#pragma region Destructor
		~Client() {
			delete[] lista;
			//cout<<"Client distrus\n";
		}
#pragma endregion
		
};
