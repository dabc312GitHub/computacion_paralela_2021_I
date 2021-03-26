//
// Created by daryl on 25/03/2021.
//

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

#define MAX 1000

double A[MAX][ MAX], x [MAX], y[ MAX];

/* Initialize A and x, assign y = 0 */
/* First pair of loops */
void firstPair() {
    for (size_t i = 0; i < MAX ; i++) {
        for (size_t j = 0; j < MAX ; j++) {
//            cout << "A[" << i << "][" << j << "]: " << " ";
//            cout << "x[" << j << "]: " << " ";
            y[i] += A[i][j] * x[j];
//            cout << "y[" << i << "]: " << " | ";
        }
//        cout << endl;
    }

}

/* Assign y = 0 */

/* Second pair of loops */
void secondPair() {
    for (size_t j = 0; j < MAX ; j++) {
        for (size_t i = 0; i < MAX ; i++) {
//            cout << "A[" << i << "][" << j << "]: " << " ";
//            cout << "x[" << j << "]: " << " ";
            y[i] += A[i][j] * x[j];
//            cout << "y[" << i << "]: " << " | ";
        }
//        cout << endl;
    }
}

void medirTiempoTotal_firstPair() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    firstPair();
    end = std::chrono::high_resolution_clock::now();
    int64_t duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                    .count();

    std::cout  << std::setw(30)
               << "Duracion en microsegundos: " + std::to_string(duration) + " us\n";
}

void medirTiempoTotal_secondPair() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    secondPair();
    end = std::chrono::high_resolution_clock::now();
    int64_t duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                    .count();

    std::cout  << std::setw(30)
               << "Duracion en microsegundos: " + std::to_string(duration) + " us\n";
}

int main() {
    srand(time(nullptr));

//    Rellenar A[MAX][MAX]
    for (size_t i = 0; i < MAX; ++i) {
        for (size_t j = 0; j < MAX; ++j) {
            A[i][j] = rand() % MAX;
        }
    }

//    Rellenar x[MAX] , y[MAX]
    for (size_t i = 0; i < MAX; ++i) {
        x[i] = rand() % MAX;
        y[i] = rand() % MAX;
    }


    //////////////////////////////
    cout << "First Pair: " << endl;
//    firstPair();
    medirTiempoTotal_firstPair();

    cout << endl;

    cout << "Second Pair: " << endl;
//    secondPair();
    medirTiempoTotal_secondPair();

    return 0;
}