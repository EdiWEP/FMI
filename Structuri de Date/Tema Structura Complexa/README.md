# Pairing Heaps

Proiect realizat de Podaru Eduard-Cristian, grupa 131, pentru Tema 3 din cadrul laboratorului de Structuri de Date

## Detalii despre implementare

* Am ales sa implementez nod-urile si heap-urile ca si clase
* Programul e facut sa mearga conform [cerintei de pe inforarena](https://infoarena.ro/problema/mergeheap) aferenta proiectului
* Pentru stergerea radacinii, pentru a garanta pastrarea proprietatii max-heap, am folosit tehnica two-pass merge, care e alcatuita din doi pasi: 
    1. Se efectueaza merge pe cate doua subheap-uri
    2. De la dreapta la stanga, se efectueaza merge intre heap-ul curent si urmatorul
* Pentru operatia insert, am folosit un merge cu un heap cu un singur element
* Desi nu contribuie la rezolvarea cerintei de pe infoarena, clasa PairingHeap contine si o metoda care primeste un std::vector de elemente si construieste din ele un heap in obiectul apelant, prin insert-uri succesive


## Surse de informare
Pentru a invata mai multe despre aceasta structura de date, am citit aceste articole:
* [Pairing Heap, briliant.org](https://brilliant.org/wiki/pairing-heap/)
* [Pairing Heap, wikipedia.org](https://en.wikipedia.org/wiki/Pairing_heap)
* [Pairing Heap, geeksforgeeks.com](https://en.wikipedia.org/wiki/Pairing_heap)

