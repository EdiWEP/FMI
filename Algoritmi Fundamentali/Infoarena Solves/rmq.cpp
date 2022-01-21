// Podaru Eduard-Cristian
#include <iostream>
#include <fstream>
#include <algorithm>
		
using namespace std;
	
 
ifstream f("rmq.in");
ofstream g("rmq.out");
	
 	
int n, sol, m; 
int Arb[400005];
int val;
int poz;
int x, y; 
	
void Update(int nod, int st, int dr) {
	
    
	
    if(st == dr) {
        Arb[nod] = val;
        return;
	
    }

    int mij = (st + dr) / 2;
    int copil = nod*2;
	
    if(poz <= mij) {
        Update(copil, st, mij);
	
    }
	
    if(poz > mij) {
	   Update(copil + 1, mij+1, dr);
	
    }
	
    Arb[nod] = min(Arb[copil], Arb[copil +1]);
	
}
	
 
	
void Query(int nod, int st, int dr) {
	
   
	
    if(st >= x && dr <= y) {
        sol = min(sol,Arb[nod]);
        return;
	
    }
	
    int mij = (st+dr) / 2;
    int copil = nod*2;

    if(x <= mij) {
        Query(copil,st,mij);
	
    }
	
    if(y > mij) {
        Query(copil + 1, mij+1, dr);
	
    }
	
}
	
 

int main() {
	
    int i;
	
    f>>n>>m;
	
    for(i = 1; i <= n; ++i) {
	
        f>>val;
	
        poz = i;
        Update(1,1,n);
	
    }
	
    for(i = 0; i < m; ++i) {
	
        f>>x>>y;
	
        sol = 100001;
	
        Query(1,1,n);
	
        g<<sol<<'\n';
	
    }
	
    return 0;
	
}