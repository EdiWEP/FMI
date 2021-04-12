// Proiect realizat de Eduard-Cristian Podaru, grupa 131, pentru tema 2 de la laboratorul de POO
// Tema pe care am ales sa o implementez este tema 11
// Programul a fost testat si ruleaza corect pe Microsoft Visual Studio Community 2019, 
// cu compilatorul care vine default cu instalarea workload-ului "Desktop Development for C++", si anume MSVC/Visual C++ Compiler
// Programul permite inserarea si afisarea datelor despre abonatii unei biblioteci, prin intermediul claselor implementate
#pragma once

#include<iostream>
#include<fstream>
#include<cstring>
#include<string>


using namespace std;

class Persoana {

protected:
	string nume;
	string cnp;


public:

#pragma region Methods

	virtual int varsta() {
		int age;
		int totalDays = 0;
		int year = 0;
		int month = 0;
		int day = 0;
		int currentYear;
		int currentMonth;
		int currentDay;
		int currentTotalDays;

		string aux;

		cout << "\nTrebuie sa introduci data curenta";
		cout << "\nIntrodu anul curent: ";
		cin >> currentYear;
		cout << "\nIntrodu luna curenta(numeric): ";
		cin >> aux;
		currentMonth = (aux[0] - '0') * 10 + (aux[0] - '0');
		cout << "\nIntrodu ziua din luna curenta: ";
		cin >> aux;
		currentDay = (aux[0] - '0') * 10 + (aux[0] - '0');

		currentTotalDays = currentYear * 365 + currentMonth * 30 + currentDay;

		if (cnp[0] == '1' || cnp[0] == '2') {
			year = 1900;
		}
		else {
			year = 2000;
		}
		year += (cnp[1] - '0') * 10 + (cnp[2] - '0');
		month = (cnp[3] - '0') * 10 + (cnp[4] - '0');
		day = (cnp[5] - '0') * 10 + (cnp[6] - '0');

		totalDays = year * 365 + month * 30 + day;

		age = (currentTotalDays - totalDays) / 365 ;

		return age;
	}

#pragma endregion

#pragma region Setters

	void setNume(string name) {
		nume = name;
	}

	void setCnp(string id) {
		cnp = id;
	}

#pragma endregion 

#pragma region Getters

	string getNume() {
		return nume;
	}

	string getCnp() {
		return cnp;
	}

#pragma endregion 

#pragma region Operators 

	Persoana operator=(Persoana person) {
		if (this != &person) {

			this->nume = person.nume;
			this->cnp = person.cnp;
		}

		return *this;
	}

	friend istream& operator>>(istream& in, Persoana& person);
	friend ostream& operator<<(ostream& out, Persoana& person);

#pragma endregion 


#pragma region Constructors

	Persoana() {
		nume = "";
		cnp = "";
	}

	Persoana(string name, string id) {
		nume = name;
		cnp = id;
	}

	Persoana(const Persoana& person) {

		nume = person.nume;
		cnp = person.cnp;

	}

#pragma endregion Constructors

#pragma region Destructor

	~Persoana() {
		//cout << "Obiect persoana distrus";
	}
#pragma endregion Destructor

};


#pragma region Persoana Operators

istream& operator>>(istream& in, Persoana& person) {
	string aux;

	cout << "\nIntrodu numele persoanei: ";
	in.ignore();
	getline(in, aux);
	person.nume = aux;

	cout << "\nIntrodu CNP-ul persoanei: ";
	in >> aux;
	person.cnp = aux;

	return in;

}

ostream& operator<<(ostream& out, Persoana& person) {

	out << "\nNume: " << person.nume;
	out << "\nCNP: " << person.cnp;

	return out;
}

#pragma endregion

class Abonat : public Persoana {

private:

	int nrMaxCarti;
	int nrCartiImprumutate;
	int pretAbonament ;

	static int pretTotalAbonamente;

public: 

#pragma region Methods

	static void initializeazaPretTotal() {
		pretTotalAbonamente = 0;
	} 

	static void adaugaLaPretTotal(int pret) {
		pretTotalAbonamente += pret;
	}
	static void afiseazaPretTotal() {
		cout << "\nPretul total al abonamentelor: " << pretTotalAbonamente;
	}

	static int verificaNrMaxim(int pret, int nrMax) {

		bool ok = false;

		while (!ok) {
			try {
				if (pret < nrMax) {
					throw 101;
				}
				else {
					ok = true;
				}
			}

			catch (int errorCode) {

				cout << "\nNumarul maxim trebuie sa fie mai mic decat pretul, incearca din nou";
				cout << "\nIntrodu numarul maxim de carti: ";
				cin >> nrMax;
			}
		}
		
		return nrMax;
	}

	static int verificaNrImprumutate(int nrMax, int nrImpr) {
		
		bool ok = false;

		while (!ok) {

			try {
				if (nrMax < nrImpr) {
					throw 202;
				}
				else {
					ok = true;
				}
			}
			catch (int errorCode) {
				cout << "\nNumarul de carti imprumutate trebuie sa fie mai mic decat numarul maxim, incearca din nou";
				cout << "\nIntrodu numarul de carti imprumutate: ";
				cin >> nrImpr;
			}
		}

		return nrImpr;
	}

#pragma endregion

#pragma region Setters

	void setNrMaxCarti(int nr) {
		nrMaxCarti = nr;
	}

	void setNrCartiImprumutate(int nr) {
		nrCartiImprumutate = nr;
	}

	void setPretAbonament(int pret) {
		pretTotalAbonamente -= pretAbonament;
		pretTotalAbonamente += pret;
		pretAbonament = pret;
	}



#pragma endregion

#pragma region Getters
	
	int getNrMaxCarti() {
		return nrMaxCarti;
	}

	int getNrCartiImprumutate() {
		return nrCartiImprumutate;
	}

	int getPretAbonament() {
		return pretAbonament;
	}

	static int getPretTotalAbonamente() {
		return pretTotalAbonamente;
	}

#pragma endregion

#pragma region Constructors 

	Abonat() {

		nrMaxCarti = 0;
		nrCartiImprumutate = 0;
		pretAbonament = 0;
	}

	Abonat(string name, string id) : Persoana(name, id) {
		
		nrMaxCarti = 0;
		nrCartiImprumutate = 0;
		pretAbonament = 0;

	}

	Abonat(string name, string id, int nrMax, int nrImprumutate, int pret): Persoana(name, id) {
		
		nrMaxCarti = nrMax;
		nrCartiImprumutate = nrImprumutate;
		pretAbonament = pret;
		pretTotalAbonamente += pret;
	}

	Abonat(const Abonat& abonat) {

		this->nume = abonat.nume;
		this->cnp = abonat.cnp;
		this->nrMaxCarti = abonat.nrMaxCarti;
		this->nrCartiImprumutate = abonat.nrCartiImprumutate;
		pretTotalAbonamente -= this->pretAbonament;
		pretTotalAbonamente += abonat.pretAbonament;
		this->pretAbonament = abonat.pretAbonament;

	}

#pragma endregion


#pragma region Operators

	Abonat operator=(Abonat abon) {
		
		this->nume = abon.nume;
		this->cnp = abon.cnp;
		this->nrMaxCarti = abon.nrMaxCarti;
		this->nrCartiImprumutate = abon.nrCartiImprumutate;
		Abonat::pretTotalAbonamente -= this->pretAbonament;
		Abonat::pretTotalAbonamente += abon.pretAbonament;
		this->pretAbonament = abon.pretAbonament;

		return *this;
	}
	
	friend istream& operator>>(istream& in, Abonat& abonat);
	friend ostream& operator<<(ostream& out, Abonat& abonat);

#pragma endregion

#pragma region Destructor 

	~Abonat() {
		// cout << "Obiect Abonat distrus";
		
	}
#pragma endregion

};

int Abonat::pretTotalAbonamente = 0;

#pragma region Abonat Operators


istream& operator>>(istream& in, Abonat& abonat) {
	string aux;
	int aux2;

	cout << "\nIntrodu numele abonatului: ";
	in.ignore();
	getline(in, aux);
	abonat.nume = aux;

	cout << "\nIntrodu CNP-ul abonatului: ";
	in >> aux;
	abonat.cnp = aux;

	cout << "\nIntrodu pretul abonamentului: ";
	in >> aux2;
	abonat.pretAbonament = aux2;
	Abonat::pretTotalAbonamente += aux2;

	cout << "\nIntrodu numarul maxim de carti: ";
	in >> aux2;
	aux2 = Abonat::verificaNrMaxim(abonat.pretAbonament, aux2);
	abonat.nrMaxCarti = aux2;

	cout << "\nIntrodu numarul de carti imprumutate: ";
	in >> aux2;
	aux2 = Abonat::verificaNrImprumutate(abonat.nrMaxCarti, aux2);
	abonat.nrCartiImprumutate = aux2;

	

	
	return in;

}

ostream& operator<<(ostream& out, Abonat& abonat) {

	out << "\nNume: " << abonat.nume;
	out << "\nCNP: " << abonat.cnp;
	out << "\nNumarul maxim de carti: " << abonat.nrMaxCarti;
	out << "\nNumarul de carti imprumutate: " << abonat.nrCartiImprumutate;
	out << "\nPretul abonamentului: " << abonat.pretAbonament;

	return out;
}

#pragma endregion


class Dosar {

private:

	int nrAbonati;
	Abonat* abonati;


public:

#pragma region Methods

	void adaugareAbonat(Abonat& abonat) {
		
		Dosar dosarTemp(*this);

		++nrAbonati;

		abonati = new Abonat[nrAbonati];

		abonati[nrAbonati - 1] = abonat;

		for (int i = 0; i < nrAbonati - 1; ++i) {
			abonati[i] = dosarTemp.abonati[i];
		}
	}

#pragma endregion
#pragma region Setters

	void setNrAbonati(int nr) {
		nrAbonati = nr;
	}

#pragma endregion 

#pragma region Getters

	int getNrAbonati() {
		return nrAbonati;
	}

#pragma endregion

#pragma region Constructors 

	Dosar() {

		nrAbonati = 0;
		abonati = NULL;
	}

	Dosar(int nr) {

		nrAbonati = nr;
		abonati = NULL;
	}

	Dosar(const Dosar& dosar) {

		this->nrAbonati = dosar.nrAbonati;

		delete[] abonati;

		abonati = new Abonat[nrAbonati];

		for (int i = 0; i < nrAbonati; ++i) {
			abonati[i] = dosar.abonati[i];
		}

	}

#pragma endregion

#pragma region Operators

	Dosar operator=(Dosar dosar) {
		
		this->nrAbonati = dosar.nrAbonati;

		delete[] abonati;

		abonati = new Abonat[nrAbonati];

		for (int i = 0; i < nrAbonati; ++i) {
			abonati[i] = dosar.abonati[i];
		}

	}

	friend istream& operator>>(istream& in, Dosar& dosar);
	friend ostream& operator<<(ostream& out, Dosar& dosar);
	
#pragma endregion

#pragma region Destructor

	~Dosar() {
		delete[] abonati;
	}

#pragma endregion

};

#pragma region Dosar Operators

istream& operator>>(istream& in, Dosar& dosar) {

	int aux;

	cout << "\nIntrodu numarul de abonati: ";
	in >> aux;
	dosar.nrAbonati = aux;

	delete[] dosar.abonati;

	dosar.abonati = new Abonat[dosar.nrAbonati];

	for (int i = 0; i < aux; ++i) {
		cout << "\nInformatii abonat " << i + 1 << '\n';
		in >> dosar.abonati[i];
	}

	return in;
}

ostream& operator<<(ostream& out, Dosar& dosar) {

	out << "\nNumarul de abonati: " << dosar.nrAbonati;

	for (int i = 0; i < dosar.nrAbonati; ++i) {
		out << "\nInformatii abonat " << i + 1;

		out << dosar.abonati[i];
	}

	return out;
}

#pragma endregion