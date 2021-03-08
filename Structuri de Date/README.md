# Tema Sortari

Tema 1 de la laboratorul de Structuri de Date, anul 1, semestrul 2.

## Cerinta

Implementare a mai multi algoritmi de sortare pentru a compara timpii de rulare ai acestora intre ei si cu sort-ul standard integrat in limbajul de programare folosit(C++) 

Algoritmii implementati sunt urmatorii:
* BubbleSort
* CountSort
* RadixSort
* QuickSort
* MergeSort

## Detalii despre implementare

**Structura**
In Teste.txt se introduc pe prima linie numarul de teste(T), iar pe urmatoarele T linii pereci de numere de forma "N Max", unde N este numarul de elemente, iar Max este numarul maxim posibil aflat printre ele

Se ruleaza Sortari.cpp, care creaza un fisier Rezultate.txt(Exemplu inclus), care contine timpii de rulare ai algoritmilor pe fiecare test citit.

**Generare Numere Random**
Pentru a genera numere random, deoarece rand() din c++ nu imi genera numere mai mari decat ~32000, am folosit un Mersenne Twister RNG, pe care l-am seed-at cu random_device() la fiecare rulare.
Numerele generate sunt distribuite uniform pentru a simula un set de date cat mai aleatoriu.

**Calculul timpului de rulare**
Pentru a calcula timpul de rulare al fiecarui algoritm, am folosit functia clock() din ctime, pastrand timpul dinaintea executarii algoritmului, apoi scazandu-l din timpul de dupa executare. Am afisat rezultatul in secunde, cu precizie de o milisecunda.

O problema pe care nu am reusit sa o rezolv: Pe calculatorul si sistem-ul pe care am testat, Sort din STL rula foarte incet. Am incercat sa reduc dimensiunea maxima a arrayului, sa folosesc vector in loc de array, dar nu au fost schimbari majore in timpul de executie. Pe internet nu am reusit sa gasesc o solutie.

Observatie: Unii algoritmi au fost mai lenti decat ma asteptam, insa nu pot determina daca este din cauza hardware-ului, software-ului(am rulat cu Visual Studio Community 2019) sau a implementarii.

Voi rula programul pe un sistem cu Linux ca sa vad daca rezultatele difera.

**Radix Sort**
Pentru Radix Sort am folosit varianta Least Significant digit, iar implementarea permite schimbarea bazei in care se face sortarea prin schimbarea parametrului "baza".
Fara modificarea sursei, se ruleaza pentru baza 10 si baza 8.

**Quick Sort**
Am ales pivotul in doua moduri diferite, intai mediana din 3, apoi mereu ultimul element. Pe testele mele, timpul de rulare nu a parut sa fie afectat prea mult.

Am avut probleme de stack overflow la rularea QuickSort-ului pe un N mare, de aceea am folosit o varianta care simuleaza unele recursii folosind instructiunea goto, pentru a reduce adancimea recursiilor.

**Cod extern folosit**
Am inclus in fisierul "Surse cod folosit.txt" sursele de unde am preluat si eventual modificat cod gasit pe internet.
