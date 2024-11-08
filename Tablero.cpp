// Tablero.cpp
#include "Tablero.h"
#include <iomanip>

Tablero::Tablero(int numJugadores) : guia{3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3}, numJugadores(numJugadores) {
    casillas.resize(11);
    for (int i = 0; i < 11; ++i) {
        casillas[i].resize(guia[i]);
        for (int j = 0; j < guia[i]; ++j) {
            casillas[i][j].resize(numJugadores, ".");
        }
    }
}

void Tablero::actualizarTablero(const std::map<std::string, std::map<int, int>>& posicionesJugadores) {
    // Limpiar el tablero
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < guia[i]; ++j) {
            std::fill(casillas[i][j].begin(), casillas[i][j].end(), ".");
        }
    }

    // Actualizar posiciones
    int jugadorIndex = 0;
    for (const auto& jugadorPar : posicionesJugadores) {
        const std::string& color = jugadorPar.first;
        const std::map<int, int>& posiciones = jugadorPar.second;
        
        for (const auto& posicionPar : posiciones) {
            int columna = posicionPar.first;
            int progreso = posicionPar.second;
            int index = columna - 2;
            
            if (progreso < guia[index]) {
                casillas[index][progreso][jugadorIndex] = color;
            }
        }
        jugadorIndex++;
    }
}

void Tablero::mostrar() const {
    std::cout << "\n=== TABLERO ACTUAL ===\n";
    for (int fila = 12; fila >= 2; --fila) {
        std::cout << std::setw(2) << fila << ": ";
        int index = fila - 2;
        
        if (index >= 0 && index < casillas.size()) {
            for (int altura = 0; altura < guia[index]; ++altura) {
                std::cout << "[";
                for (int j = 0; j < numJugadores; ++j) {
                    if (casillas[index][altura][j] == ".") {
                        std::cout << ".";
                    } else {
                        std::cout << "\033[" << casillas[index][altura][j] << "m●\033[0m";
                    }
                }
                std::cout << "]";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "===================\n";
}
