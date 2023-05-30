#include <iostream>
#include <string>
#include <vector>

using namespace std;

int nrstari, nrtranzitii, nrstarifinale, vstfin[101];

struct {
    int st1, st2, lit;
}tranz[101];

void citire(){
    cin >> nrstari >> nrtranzitii >> nrstarifinale ;
    for(int i = 0; i < nrstari; i++ )
    {
        cin >> tranz[i].st1 >> tranz[i].lit >> tranz[i].st2;

    }
    for(int i = 0; i < nrstarifinale; i++ )
    {
        cin >> vstfin[i] ;
    }
}

bool verificareEchivalenta(int a, int b) {
    for (int i = 0; i < nrtranzitii; i++) {
        if (tranz[i].st1 == a && tranz[i].st2 == b) {
            return true;
        }
    }
    return false;
}

bool verifStarePartitie(int stare, int partiție[], int dimensiune) {
    for (int i = 0; i < dimensiune; i++) {
        if (partiție[i] == stare) {
            return true;
        }
    }
    return false;
}

void MinimizareAFD() {
    int fin1[101], fin2[101];  // Stări finale după minimizare
    int partiții[2][101];  // Partiții inițiale
    int nrPartiții = 2;

    // Separăm stările finale și non-finale în două partiții inițiale
    int nrFin1 = 0, nrFin2 = 0;
    for (int i = 0; i < nrstarifinale; i++) {
        if (verifStarePartitie(vstfin[i], partiții[0], nrPartiții)) {
            fin1[nrFin1++] = vstfin[i];
        } else {
            fin2[nrFin2++] = vstfin[i];
        }
    }

    bool modificare = true;
    while (modificare) {
        modificare = false;

        for (int i = 0; i < nrPartiții; i++) {
            int part1[101], part2[101];  // Stările din partiție
            int nrPart1 = 0, nrPart2 = 0;

            for (int j = 0; j < nrPartiții; j++) {
                if (j != i) {
                    for (int k = 0; k < nrtranzitii; k++) {
                        int st1 = partiții[i][j];
                        int st2 = tranz[k].st2;

                        if (verificareEchivalenta(st1, st2)) {
                            part1[nrPart1++] = st2;
                        } else {
                            part2[nrPart2++] = st2;
                        }
                    }
                }
            }

            if (nrPart1 > 0 && nrPart2 > 0) {
                for (int j = 0; j < nrPart1; j++) {
                    partiții[i][j] = part1[j];
                }

                for (int j = 0; j < nrPart2; j++) {
                    partiții[i][j] = part2[j];
                }

                nrPartiții++;
                modificare = true;
            }
        }
    }

    // Stări finale după minimizare
    cout << "Starile finale dupa minimizare:\n";
    for (int i = 0; i < nrPartiții; i++) {
        bool esteFinala = false;
        for (int j = 0; j < nrFin1; j++) {
            if (verifStarePartitie(fin1[j], partiții[i], nrPartiții)) {
                esteFinala = true;
                break;
            }
        }

        if (esteFinala) {
            for (int j = 0; j < nrPartiții; j++) {
                cout << partiții[i][j] << " ";
            }
        }
    }
}

int main() {
    citire();
    MinimizareAFD();
    return 0;
}

//6
//12
//1
//0 0 1
//0 1 2
//1 0 0
//1 1 3
//2 0 5
//2 1 4
//3 0 5
//3 1 4
//4 0 4
//4 1 4
//5 0 5
//5 1 4
//5
