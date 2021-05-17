// Aceasta este o implementare a unui Pairing Heap(max-heap), realizata pentru Tema 3(structura complexa) din cadrul laboratorului de Structuri de Date
// De catre Podaru Eduard-Cristian, grupa 131

#include<iostream>
#include<fstream>
#include<vector>

using namespace std;


ifstream inputFile("mergeheap.in");
ofstream outputFile("mergeheap.out");

int n, q;           // Semnificatia din enuntul de pe infoarena

int tipOperatie;
int x, y;           // Variabile auxiliare pentru citire


class Node {
public:
    int value;
    Node* child;
    Node* sibling;

    Node() {
        child = NULL;
        sibling = NULL;
        value = 0;
    }

    Node(int valoare) {
        value = valoare;
        child = NULL;
        sibling = NULL;
    }

    Node(int valoare, Node* copil, Node* frate) {
        value = valoare;
        child = copil;
        sibling = frate;
    }
};

class PairingHeap {

public:
    Node* root;

    PairingHeap() {
        root = NULL;
    }

    PairingHeap(int x) {                                        // Constructor folositor pentru a face merge-uri cu un singur element
        Node* n = new Node(x);
        root = n;
    }

    bool empty() {
        return (root == NULL);
    }

    void mergeWith(PairingHeap heap2) {                         // Metoda folosita pentru merging, poate fi practic folosita si pentru insert-uri,
                                                                // deoarece putem merge-ui cu un heap cu un singur element
        if (heap2.empty()) {
            return;
        }

        if (this->empty()) {

            root = heap2.root;
            return;
        }


        if (this->root->value >= heap2.root->value) {
            heap2.root->sibling = this->root->child;            // Adaugam heap2 la lista de subheapuri 
            this->root->child = heap2.root;
                                                            
        }
        else {
            this->root->sibling = heap2.root->child;            // Intai adaugam la heap2 obiectul curent in lista de subheapuri ale lui heap2
            heap2.root->child = this->root;
            this->root = heap2.root;                            
       
        }


    }

    void insert(int val) {
        PairingHeap heap2 = PairingHeap(val);

        this->mergeWith(heap2);

        
    }

    int getMax() {
        return root->value;
    }

    void heapify(vector<int> listaElemente) {              // Metoda care primeste o lista de elemente si formeaza in obiectul curent un pairing heap care le contine

        int lungime = listaElemente.size();

        if (lungime) {                                      // Daca nu e gol
            Node* n = new Node(listaElemente[0]);
            this->root = n;

            for (int i = 1; i < lungime; ++i) {
                this->insert(listaElemente[i]);
            }
        }
    }

    void twoPassMerge() {

 

        if (root->child == NULL) {                                   // Daca exista un singur nod(radacina), heapul ramane gol
            root = NULL;

 
            
            return;
        }

        if (root->child->sibling == NULL) {
            root = root->child;                                     // Daca exista un singur subheap, devine noul heap principal
            


            return;
        }

        vector<PairingHeap> pairs;
        int nrPairs = 0;

        Node* current = this->root->child;
        Node* currentSibling = this->root->child->sibling;
        Node* nextSibling = currentSibling->sibling;        // Variabila necesara pentru a nu pierde legatura catre urmatorul frate, daca exista
       
        do {                                                        // Acesta este primul pass, care cupleaza subheapurile cate doua (ultimul poate ramane necuplat)     
            
            pairs.push_back(PairingHeap());                         

            PairingHeap siblingHeap = PairingHeap();

            pairs[nrPairs].root = current;
           
             
            siblingHeap.root = currentSibling;
             
            pairs[nrPairs].mergeWith(siblingHeap); 
                      
            if (nextSibling == NULL) {
                    
                ++nrPairs;
                break;
            }
            
            current = nextSibling;
            
            if (current->sibling == NULL) {
                ++nrPairs;

                pairs.push_back(PairingHeap());
                pairs[nrPairs].root = current;
                
                ++nrPairs;
                break;
            }

            currentSibling = current->sibling;
            nextSibling = currentSibling->sibling;

            ++nrPairs;
        } while (current != NULL);

        
        this->root = pairs[nrPairs - 1].root;                         // La al doilea pass luam de la dreapta la stanga perechile si le tot merge-uim succesiv
                                                                    // Luand mereu rezultatul ultimului merge si urmatorul pair din stanga 
        
        for (int i = nrPairs - 2; i >= 0; --i) {

            this->mergeWith(pairs[i]);

        }
        
    }

    void deleteMax() {                                              // Pentru a sterge maximul, folosim un two-pass merge/two-pass pairing
        if (!this->empty()) {
            this->twoPassMerge();
        }
    }


};

vector<PairingHeap> listaHeapuri;

int main() {

    inputFile >> n >> q;

    for (int i = 0; i <= n; ++i) {
        listaHeapuri.push_back(PairingHeap());
    }

    for (int i = 0; i < q; ++i) {

        inputFile >> tipOperatie;

        if (tipOperatie == 2) {
            inputFile >> x;
            outputFile <<listaHeapuri[x].getMax()<<'\n';
            listaHeapuri[x].deleteMax();

        }

        if (tipOperatie == 1) {
            inputFile >> x >> y;
            listaHeapuri[x].insert(y);

        }

        if (tipOperatie == 3) {
            inputFile >> x >> y;
       
            listaHeapuri[x].mergeWith(listaHeapuri[y]);

            listaHeapuri[y].root = NULL;

       }
    }


    return 0;
}
