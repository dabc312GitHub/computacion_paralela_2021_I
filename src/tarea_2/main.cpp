//
// Created by daryl on 25/03/2021.
//

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <array>

using namespace std;
using namespace std::chrono;

    #define MAX_i 1000
#define MAX_k 2000
#define MAX_j 3000

double A[MAX_i][MAX_k], B[MAX_k][MAX_j], res[MAX_i][MAX_j];

//double C[MAX][ MAX];
//double A[3][2] = {
//    {1,2},
//    {3,4},
//    {5,6}
//};
//
//double B[2][1] = {
//    {11},
//    {44}
//};


void multiplicacion_clasica() {
    for (size_t i = 0; i < MAX_i; i++) {
        for (size_t j = 0; j < MAX_j; j++) {
            for (size_t k = 0; k < MAX_k; k++) {
                res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


//https://www.netlib.org/utk/papers/autoblock/node2.html
void multiplicacion_bloques() {
    int bsize = max(MAX_i, MAX_j);

    for (int i = 0; i < MAX_i; i+=bsize) {
        for (int j = 0; j < MAX_j; j=+bsize) {
            for (int k = 0; k < MAX_k; k=+bsize) {
                for (size_t ii = i; ii < min(i+bsize, MAX_i); ii++) {
                    for (size_t jj = j; jj < min(j+bsize, MAX_j); jj++) {
                        for (size_t kk = k; kk < min(k+bsize, MAX_k); kk++) {
                            res[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}


void medirTiempoTotal_multiplicacion_clasica() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

//    Modificar uso de función
    multiplicacion_clasica();

    end = std::chrono::high_resolution_clock::now();
    int64_t duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                    .count();

    std::cout  << std::setw(30)
               << "Duracion en milisegundos: " + std::to_string(duration) + " ms\n";
}

void medirTiempoTotal_multiplicacion_bloques() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

//    Modificar uso de función
    multiplicacion_bloques();

    end = std::chrono::high_resolution_clock::now();
    int64_t duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                    .count();

    std::cout  << std::setw(30)
               << "Duracion en milisegundos: " + std::to_string(duration) + " ms\n";
}

//void imprimir_matriz(double& matrix, int ii, int jj) {
//    for (int i = 0; i < ii; ++i) {
//        for (int j = 0; j < jj; ++j) {
//            cout << matriX[i][j] << " ";
//        }
//        cout << endl;
//    }
//}


int main() {
//    cout << "hola" << endl;
//    return 0;
    srand(time(nullptr));

//    Rellenar A[MAX][MAX]
//    cout << "Matriz A: " << endl;
//    cout << "A= [";
    for (size_t i = 0; i < MAX_i; ++i) {
        for (size_t j = 0; j < MAX_k; ++j) {
            A[i][j] = rand() % 1000;
//            cout << A[i][j] << " ";
        }
    }
//    cout << "]";
//    cout << endl;
//    cout << endl;

//    Rellenar B[MAX][MAX]
//    cout << "Matriz B: " << endl;
//    cout << "B= [";
    for (size_t i = 0; i < MAX_k; ++i) {
        for (size_t j = 0; j < MAX_j; ++j) {
            B[i][j] = rand() % 1000;
//            cout << B[i][j] << " ";
        }
    }
//    cout << "]";
//    cout << endl;
//    cout << endl;


    //////////////////////////////
//    medirTiempoTotal();

    medirTiempoTotal_multiplicacion_clasica();
//        for (size_t i = 0; i < MAX_i; i++)
//            for (size_t j = 0; j < MAX_j; j++)
//                res[i][j] = 0.0;
//        medirTiempoTotal_multiplicacion_bloques();

//    cout << "solucion: " << endl;
//    for (int i = 0; i < MAX_i; ++i) {
//        for (int j = 0; j < MAX_j; ++j) {
//            cout << res[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;

    return 0;
}