// Tema 1, optiunea 1 de la laboratorul de Structuri de Date, realizata de Eduard-Cristian Podaru, grupa 131
// Am implementat BubbleSort, CountSort, RadixSort varianta LSD cu baza variabila, MergeSort, QuickSort cu mediana de 3

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

ifstream inputFile("Teste.txt");
ofstream outputFile("Rezultate.txt");

int a[100000000];                    // Array in care citim datele
int v[100000000];                     // Array in care vom face sortarile
int k[100000000];                    // Array auxiliar pentru MergeSort

int n;                              // Lungimea arrayului a/v
int nrMax;                          // Numarul maxim posibil in arrayul dat
int nrTeste;
clock_t timpInitial, timpFinal;     // Variabile folosite pentru a determina timpul de executie al sortarilor, folosind functia clock()
float timpDecurs;


void citireTestGenerare() {
    inputFile >> n;                                                 // Am folosit o distributie uniforma de numere generate random
    inputFile >> nrMax;                            

    random_device randDevice;
    mt19937 randGenerator(randDevice());                             // Deoarece rand() nu imi genera numere peste 32000, am folosit aceasta alternativa
    uniform_int_distribution<int> distribution(0, nrMax);            // care foloseste un Mersenne Twister RNG si il seed-eaza cu un device ales random
                                                                     // dintre cele de pe masina care il ruleaza   
    for (int i = 0; i < n; ++i) {
        a[i] = distribution(randGenerator);
    }
}

void copiere() {                       // Functie care copiaza continutul arrayului a in arrayul v
    for (int i = 0; i < n; ++i) {
        v[i] = a[i];
    }
}

string isSorted() {         // Functie care verifica daca v este sortat corect

    int i;
    for (i = 0; i < n - 1; ++i) {
        if (v[i] > v[i + 1]) return "Incorect";
    }
    return "Corect";
}

float calculeazaTimp(clock_t t1, clock_t t2) {          // Functie care calculeaza timpul decurs al unui algoritm
    return (float)((t2 - t1) / (1.0 * CLOCKS_PER_SEC));
}

void outputTestResult(string sortFolosit, float timp) {      // Functie folosita pentru a formata liniile din output

    outputFile << "   " << sortFolosit << "-ul implementat a sortat " << isSorted() << ", timp de executie: " << timp << " secunde\n";
}

bool BubbleSort() {             // Am implementat sortarile cerute ca functii statice
    int i;
    int aux;                // Variabila auxiliara pentru swap-ul dintre elemente
    bool inversari;                        // Variabila folosita pentru a determina daca mai sunt elemente nesortate 

    if (n > 10000) {
        return false;
    }

    do {
        inversari = false;
        for (i = 0; i < n - 1; ++i) {
            if (v[i] > v[i + 1]) {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                inversari = true;
            }
        }
    } while (inversari);

    return true;
}

bool CountSort() {
    unsigned long long i, j;

    if (nrMax > 10000000) {
        return false;
    }

    vector<int> fr(nrMax+1, 0);           // Vector pentru frecventa
    
    int minim = nrMax + 1;
    int maxim = 0;                   // Numarul minim, respectiv maxim din sir, salvate pentru optimizarea cautarii
    int poz = 0;                            // Pozitia curenta in vectorul v

    for (i = 0; i < n; ++i) {
        ++fr[v[i]];
        
        
        if (minim > v[i]) {
            minim = v[i];    
        }

        
        if (maxim < v[i]) {
            maxim = v[i];
            
        }

    }
   
    for (i = minim; i <= maxim; ++i) {          // Reconstruim vectorul v sortat
        
        
        if (fr[i]) {
            for (j = 0; j < fr[i]; ++j) {
                v[poz] = i;
                ++poz;
                
            }
        }
    }

    fr.clear();
    return true;
}

void Radix(int mask, int baza) {

    vector<int> fr(baza);
    vector<unsigned long long> aux(n);
    
    for (int i = 0; i < baza; ++i) {              // Cream vectorul de frecventa
        fr[i] = 0;
    }
    
    for (int i = 0; i < n; ++i) {               // Actualizam vectorul de frecventa
        ++fr[(v[i] / mask) % baza];
    }
    
    for (int i = 1; i < baza; ++i) {                  // Facem aceste adunari pentru a ajunge mai rapid la indexii corecti in reconstruire
        fr[i] += fr[i - 1];
    }
    
    for (int i = n-1; i >= 0; --i) {                // Parcurgem in ordinea descrescatoare a indexilor din cauza adunarilor facute anterior
        int cifra = (v[i] / mask) % baza;             // Vrem intai sa punem in aux pe pozitiile mai mari numerele sortate deja dupa cifrele anterioare
        aux[fr[cifra]-1] = v[i];                    // In ordine descrescatoare a acestora, din cauza faptului ca decrementam fr[cifra]
        --fr[cifra];
    }
    
    for (int i = 0; i < n; ++i) {
        v[i] = aux[i];
    }
    
}

void RadixSortLSD(int baza) {
    
    unsigned long long maxim = 0;

    for (int i = 0; i < n; ++i) {               // Calculam maximul din vector
        if (v[i] > maxim) {
            maxim = a[i];
        }
    }

    for (unsigned long long i = 1; maxim/i > 0; i *= baza) {        // Pentru fiecare cifra
        Radix(i, baza);
    }
    
}

int MedianOf3(int st, int dr) {
    // Alege mediana din 3
    int mij = (st + dr) / 2;                    


    int aux;

    if (v[st] > v[mij]) {
        aux = v[st];
        v[st] = v[mij];
        v[mij] = aux;
    }

    if (v[st] > v[dr]) {
        aux = v[st];
        v[st] = v[dr];
        v[dr] = aux;
    }

    if (v[mij] > v[dr]) {
        aux = v[mij];
        v[mij] = v[dr];
        v[dr] = aux;
    }

    return mij;
}

int Partition(int st, int dr, int mij) {

    int pivot = v[mij];
    int aux = v[mij];

    v[mij] = v[dr];                             // Mutam pivotul la final
    v[dr] = aux;

    int i = st;
    for (int j = st; j < dr; ++j) {
        if (v[j] < pivot) {
            aux = v[j];                         // Mutam toate elementele mai mici decat pivotul la inceputul vectorului
            v[j] = v[i];
            v[i] = aux;
            ++i;
        }
    }

    aux = v[i];
    v[i] = v[dr];                               // Mutam pivotul pe pozitia corecta in vectorul final
    v[dr] = aux;

    return i;                                   // Returnam indexul pivotului
}

void QuickSort(int st, int dr, bool skip = 0) {         // Parametrul skip == 1 => Nu folosim mediana din 3, ci folosim ultimul element ca si pivot
    TailRecurse:
    if (st < dr) {                                      // Din cauza faptului ca am avut probleme de stack overflow la quicksort
        int mij;                                        // Pe care nu reuseam sa le rezolv, am cautat pe net si am gasit solutia aceasta care se bazeaza
                                                        // Pe reducerea adancimii de recursie.    
        if (skip) {
            mij = dr;
        }
        else {
            mij = MedianOf3(st, dr);
        }

        int index = Partition(st, dr, mij);

        if (index < (st + dr) / 2) {
            // Inseamna ca partitia din stanga este mai mica deci pe ea aplicam recursie, iar pe cealalta simulam recursia
            QuickSort(st, index - 1, skip);
            st = index + 1;
            goto TailRecurse;
        }
        else {
            // Inseamna ca partitia din dreapta este mai mica deci pe ea aplicam recursie, iar pe cealalta simulam recursia
            QuickSort(index + 1, dr, skip);
            dr = index - 1;
            goto TailRecurse;
        }

    }
}


void Interclasare(int st, int dr) {

    int mij = (st + dr) / 2;
    int i = st;
    int j = mij +1;
    int poz = 0;

    while (i <= mij && j <= dr) {
        if (v[i] <= v[j]) {
            k[poz] = v[i];
            ++i;
        }
        else {
            k[poz] = v[j];
            ++j; 
        }  
        ++poz;
    }

    while (i <= mij) {
        k[poz] = v[i];
        ++i;
        ++poz;
    }
    while (j <= dr) {
        k[poz] = v[j];
        ++j;
        ++poz;
    }

    poz = 0;
    for (i = st; i <= dr; ++i) {
        v[i] = k[poz];
        ++poz;
    }

}

void MergeSort(int st, int dr) {
                                            // Varianta standard de MergeSort
    int aux = 0;

    if (st <dr) {
        int mij = (st + dr) / 2;
        MergeSort(st, mij);
        MergeSort(mij + 1, dr);
        Interclasare(st, dr);
    }

}

int main() {

    inputFile >> nrTeste;
    for (int t = 0; t < nrTeste; ++t) {
        citireTestGenerare();
        outputFile << "Rezultate Test " << t + 1 << ", cu N = " << n << " si Max = " << nrMax << "\n\n";

        //Sort din STL

        copiere();
        timpInitial = clock();

        sort(v, v + n);

        timpFinal = clock();
        timpDecurs = calculeazaTimp(timpInitial, timpFinal);

        outputFile << "   " << "Sort din STL a sortat " << isSorted() << ", timp de executie: " << timpDecurs << " secunde\n";

        // BubbleSort
        copiere();
        timpInitial = clock();

        bool bubble = BubbleSort();

        timpFinal = clock();
        if (bubble) {
            timpDecurs = calculeazaTimp(timpInitial, timpFinal);

            outputTestResult("BubbleSort", timpDecurs);
        }
        else {
            outputFile << "   BubbleSort nu poate sorta, N este prea mare\n";
        }
       

        //CountSort
        copiere();
        timpInitial = clock();

        bool count = CountSort();

        timpFinal = clock();
        if(count) {
            timpDecurs = calculeazaTimp(timpInitial, timpFinal);

            outputTestResult("CountSort", timpDecurs);
        }
        else {
            outputFile<<"   CountSort nu poate sorta, Max este prea mare\n";
        }
        
        
        //RadixSort baza 10
        copiere();
        timpInitial = clock();

        RadixSortLSD(10);

        timpFinal = clock();
        timpDecurs = calculeazaTimp(timpInitial, timpFinal);

        outputTestResult("LSD(baza 10) RadixSort", timpDecurs);


        //RadixSort baza 8 
        copiere();
        timpInitial = clock();

        RadixSortLSD(8);

        timpFinal = clock();
        timpDecurs = calculeazaTimp(timpInitial, timpFinal);

        outputTestResult("LSD(baza 8) RadixSort", timpDecurs);


        //QuickSort Mediana din 3
        
        copiere();
        timpInitial = clock();

        QuickSort(0, n-1);

        timpFinal = clock();
        timpDecurs = calculeazaTimp(timpInitial, timpFinal);

        outputTestResult("Median of 3 Quicksort", timpDecurs);


        //QuickSort Ultimul element pivot
        
        copiere();
        timpInitial = clock();

        QuickSort(0, n - 1);

        timpFinal = clock();
        timpDecurs = calculeazaTimp(timpInitial, timpFinal);

        outputTestResult("Last Element Pivot Quicksort", timpDecurs);


        //MergeSort

        copiere();
        timpInitial = clock();

        MergeSort(0, n - 1);

        timpFinal = clock();
        timpDecurs = calculeazaTimp(timpInitial, timpFinal);

        outputTestResult("MergeSort", timpDecurs);


        outputFile << '\n';

    }

    inputFile.close();
    outputFile.close();

    return 0;
}
