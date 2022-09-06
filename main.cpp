#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include "tridag.hpp"
#include "nrutil.hpp"

using namespace std;


int getDimensionFromData();
void showVector(float *vector, int n);
void showSystem(float** A, float* r, int n);
void getData(float** A, float* a, float* b, float* c, float* r);


int main() {
    int n{getDimensionFromData()};
    float **A{nullptr};
    A = matrix(0,n,0,n);

    float *a, *b, *c, *u, *r;
    a = vector(1,n);
    b = vector(1,n);
    c = vector(1,n);
    u = vector(1,n); 
    r = vector(1,n);

    getData(A, a, b, c, r);

    cout << "Le système à résoudre : " << endl << endl;
    showSystem(A, r, n);
    tridag(a, b, c, r, u, n);

    cout << endl << endl << "La solution est : " << endl << endl;
    showVector(u,n);

    free_vector(a,1,n);
    free_vector(b,1,n);
    free_vector(c,1,n);
    free_vector(u,1,n);
    free_vector(r,1,n);
    free_matrix(A,0,n,0,n);

    return 0;
}

void showVector(float *vector, int n) {
    for(int i = 0; i < n; i++) {
        cout << setw(5) << "|X" << i+1 << '|' <<  setw(3) << '=' << setw(4) << setprecision(3) <<vector[i] << endl;
    }
}

void showSystem(float** A, float* r, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(j == n-1) {
                cout << setw(4) << A[i][j] << " |";
            } else if(j == 0) {
                cout << "|" << setw(2) << A[i][j];
            } else {
                cout << setw(4) << A[i][j];
            }
        }
        cout << setw(5) << "|X" << i+1 << '|' <<  setw(3) << '=' << setw(4) << r[i] << endl;
    }
}

int getDimensionFromData() {
    ifstream inFile{"data.txt"};
    string data{""};
    int N{0};
    if(inFile.is_open()) {
        inFile >> data;
        N = stoi(data);
    }
    inFile.close();
    return N;
}

void getData(float** A, float* a, float* b, float* c, float* r) {
    //Récupérer les données
    ifstream inFile{"data.txt"};
    string data{""};
    int n{0};

    if(inFile.is_open()) {
        //Récupérer la dimension
        inFile >> data;
        n = stoi(data);

        //Récupérer la matrice
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                inFile >> data;
                if(i == j) {
                    b[i] = A[i][j] = stof(data);
                }
                if(abs(i-j) == 1 && i-j > 0) {
                    a[i] = A[i][j] = stof(data);
                }
                if(abs(i-j) == 1 && i-j < 0) {
                    c[i] = A[i][j] = stof(data);
                }
            }
        }

        //Récupérer le vecteur
        for(int i = 0; i < n; i++) {
            inFile >> data;
            r[i] = stof(data);
        }
    }
    inFile.close();
}