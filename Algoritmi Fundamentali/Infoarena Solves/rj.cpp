#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

ifstream inputFile("rj.in"); ofstream outputFile("rj.out");

int main() {

    int n, m;       // Linii, coloane

    char map[102][102];
    int romeo[102][102];  int rx, ry; // matricea pentru Lee pentru romeo si pozitia lui
    int juliet[102][102]; int jx, jy; // matricea pentru Lee pentru julieta si pozitia ei

    queue <pair <int,int> > q;  // Coada pentru algoritmul lui Lee

    string line;                // Pentru citire

    inputFile >> n >> m;
    inputFile.ignore();

    for(int i = 0; i < n; ++i) {

        
        getline(inputFile, line);

        
        for(int j = 0; j < m; ++j) {
            map[i][j] = line[j];
            romeo[i][j] = 0;
            juliet[i][j] = 0;
            
            if (line[j] == 'R') {
                romeo[i][j] = 1;
                rx = i;
                ry = j;
            }
            if (line[j] == 'J') {
                juliet[i][j] = 1;
                jx = i;
                jy = j;
            }
        }
    }

    q.push(make_pair(rx,ry));

    while(!q.empty()) {

        int x, y;
        x = q.front().first;
        y = q.front().second;
        
        q.pop();

        if (x > 0) if (map[x-1][y] == ' ') if( romeo[x-1][y] == 0 )  { romeo[x-1][y] = romeo[x][y] + 1; q.push(make_pair(x-1,y));}
            
        if ( x > 0 && y > 0) if ( map[x-1][y-1] == ' ') if (romeo[x-1][y-1] == 0) {romeo[x-1][y-1] = romeo[x][y] + 1; q.push(make_pair(x-1,y-1));}

        if ( x > 0 && y < m-1) if (map[x-1][y+1] == ' ') if (romeo[x-1][y+1] == 0) {romeo[x-1][y+1] = romeo[x][y] + 1; q.push(make_pair(x-1,y+1));}
        
        if (y < m - 1) if (map[x][y+1] == ' ') if (romeo[x][y+1] == 0) {romeo[x][y+1] = romeo[x][y] + 1; q.push(make_pair(x,y+1));}
              
        if (x < n-1 && y < m-1 ) if ( map[x+1][y+1] == ' ') if(romeo[x+1][y+1] == 0) {romeo[x+1][y+1] = romeo[x][y] +1; q.push(make_pair(x+1,y+1));}
             
        if (x < n-1 ) if ( map[x+1][y] == ' ') if(romeo[x+1][y] == 0) {romeo[x+1][y] = romeo[x][y] +1; q.push(make_pair(x+1,y));}
             
        if (x < n-1 && y > 0 ) if ( map[x+1][y-1] == ' ') if(romeo[x+1][y-1] == 0) {romeo[x+1][y-1] = romeo[x][y] +1; q.push(make_pair(x+1,y-1));}
           
        if (y > 0 ) if ( map[x][y-1] == ' ') if(romeo[x][y-1] == 0) {romeo[x][y-1] = romeo[x][y] +1; q.push(make_pair(x,y-1));}
           
    }

    q.push(make_pair(jx,jy));

    while(!q.empty()) {

        int x, y;
        x = q.front().first;
        y = q.front().second;
        
        q.pop();

        if (x > 0) if (map[x-1][y] == ' ') if( juliet[x-1][y] == 0 )  { juliet[x-1][y] = juliet[x][y] + 1; q.push(make_pair(x-1,y));}
            
        if ( x > 0 && y > 0) if ( map[x-1][y-1] == ' ') if (juliet[x-1][y-1] == 0) {juliet[x-1][y-1] = juliet[x][y] + 1; q.push(make_pair(x-1,y-1));}

        if ( x > 0 && y < m-1) if (map[x-1][y+1] == ' ') if (juliet[x-1][y+1] == 0) {juliet[x-1][y+1] = juliet[x][y] + 1; q.push(make_pair(x-1,y+1));}
        
        if (y < m - 1) if (map[x][y+1] == ' ') if (juliet[x][y+1] == 0) {juliet[x][y+1] = juliet[x][y] + 1; q.push(make_pair(x,y+1));}
              
        if (x < n-1 && y < m-1 ) if ( map[x+1][y+1] == ' ') if(juliet[x+1][y+1] == 0) {juliet[x+1][y+1] = juliet[x][y] +1; q.push(make_pair(x+1,y+1));}
             
        if (x < n-1 ) if ( map[x+1][y] == ' ') if(juliet[x+1][y] == 0) {juliet[x+1][y] = juliet[x][y] +1; q.push(make_pair(x+1,y));}
             
        if (x < n-1 && y > 0 ) if ( map[x+1][y-1] == ' ') if(juliet[x+1][y-1] == 0) {juliet[x+1][y-1] = juliet[x][y] +1; q.push(make_pair(x+1,y-1));}
           
        if (y > 0 ) if ( map[x][y-1] == ' ') if(juliet[x][y-1] == 0) {juliet[x][y-1] = juliet[x][y] +1; q.push(make_pair(x,y-1));}
           
    }

    int minDistance = 200;
    int minx, miny;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {

            int x = romeo[i][j];

            if(x) {
                if(x == juliet[i][j]) {

                    if(x < minDistance) {
                        minDistance = x;
                        minx = i; miny = j;
                    }
                }
            }
        }
    }

    outputFile << minDistance <<' ' << minx +1 << ' '<< miny+1;
}

