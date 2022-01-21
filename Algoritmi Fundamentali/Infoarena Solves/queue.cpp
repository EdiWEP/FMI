#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

ifstream inputFile("queue.in");
ofstream outputFile("queue.out");

int n;

stack<int> s1;
stack<int> s2;

int main() {

    int i;
    string linie, cuvant;

    inputFile >> n;

    for (i = 0; i < n; ++i) {
        inputFile >> linie;
        cuvant = "";
        for (int j = 0; j < 4; ++j) {
            cuvant += linie[j];
        }
        if (cuvant == "push") {
            int poz = linie.size() - 2;
            int number = 0;
            int exp = 1;

            while (linie[poz] != '(') {
                number += exp * (linie[poz] - '0');
                exp *= 10;

                --poz;
            }
            s1.push(number);
            
            outputFile << i + 1 << ": read(" << number << ") push(1," << number << ")\n";
        }
        else {
            int number;
            if (!s2.empty()) {

                number = s2.top();

                s2.pop();
                outputFile << i + 1 << ": pop(2) write(" << number << ")\n";
            }
            else {

                while (s1.size() > 1) {
                    number = s1.top();
                    s1.pop();
                    s2.push(number);

                    outputFile << i + 1 << ": pop(1) push(2," << number << ") ";

                }

                outputFile << "pop(1) write(" << s1.top() << ")\n";
                s1.pop();
            }
        }
    }

    return 0;
}