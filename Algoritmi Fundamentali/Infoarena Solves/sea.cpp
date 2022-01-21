// Podaru Eduard-Cristian
// Intai sortam vapoarele dupa coordonata x, apoi, pentru fiecare far:
// Consideram toate vapoarele care sunt in stanga farului
// Le calculam distanta pana la far
// Apoi, deoarece vapoarele erau deja sortate, distantele vor fi aproape sortate(dar descrescator), asa ca bubble-sort dureaza putin
// Luam a Fni-a cea mai mica distanta
	
#include <iostream>
#include <fstream>
#include<math.h>
#include<algorithm>
#include <iomanip>	
 
using namespace std;
	
	
ifstream inputFile("sea.in"); ofstream outputFile("sea.out");
	
struct Vapor {

    double x;
    double y;	
};
	
 
Vapor v[400];
double dist[400];      // Vector in care pastram distanta vapoarelor fata de farul curent
		
int n, m;
	
double distance(double x, double y, double xFar) {
	
    x = x - xFar;
    return x * x + y * y;
}
		
bool comp(Vapor a, Vapor b) {
	
    
	
    return a.x < b.x;
	
}

	
int main() {
	
    int Fni, index;
    double x;
	
    inputFile >> n >> m;
	
    for(int i = 0 ; i < n; ++i) {
	
        inputFile >> v[i].x >> v[i].y;
    }
	
    sort(v, v + n, comp);
	
    index = 0;

    for(int i = 0; i < m; ++i) {
	
        inputFile >> x >> Fni;
	
        while( v[index].x <= x && index < n) {
            ++index;
        } 
	
        for(int j = 0; j < index; ++j) {
	
            dist[j] = distance(v[j].x, v[j].y, x); 
        }
        bool inversari = true;
        for(int k = 0; k < index - 1 && inversari; ++k) {
            inversari = false;
            for(int j = index - 1; j >= k + 1; --j) {
                if(dist[j - 1] < dist[j]) {
                    swap(dist[j-1],dist[j]);
                    swap(v[j-1],v[j]);
                    inversari = true;
                }
            }
        }
	
        outputFile<< setprecision(4) << fixed << sqrt(dist[index-Fni]) << '\n';
    } 
	
	
    return 0;
	
}