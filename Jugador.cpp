// Jugador.cpp
#include "Jugador.h"

Jugador::Jugador(std::string nombre, std::string color, int index) 
    : nombre(nombre), columnasCompletadas(0), color(color), jugadorIndex(index) {
    for (int i = 2; i <= 12; ++i) {
        progreso[i] = 0;
        columnasFinalizadas[i] = false;
    }
}

bool Jugador::avanzarColumna(int columna, const std::vector<int>& guia) {
    if (columnasFinalizadas[columna]) {
        std::cout << "Esta columna ya está completada." << std::endl;
        return false;
    }
    
    if (columnasActivas.size() < 3 || columnasActivas.count(columna) > 0) {
        if (progreso[columna] + progresoTemporal[columna] >= guia[columna - 2]) {
            std::cout << "No puedes avanzar más en esta columna." << std::endl;
            return false;
        }
        
        columnasActivas.insert(columna);
        progresoTemporal[columna]++;
        return true;
    }
    
    std::cout << "No puedes activar más columnas." << std::endl;
    return false;
}

void Jugador::finalizarTurno(bool exitoso, const std::vector<int>& guia) {
    if (exitoso) {
        for (const auto& par : progresoTemporal) {
            int columna = par.first;
            int avance = par.second;
            progreso[columna] += avance;
            
            if (progreso[columna] >= guia[columna - 2]) {
                if (!columnasFinalizadas[columna]) {
                    columnasFinalizadas[columna] = true;
                    columnasCompletadas++;
                }
            }
        }
    }
    columnasActivas.clear();
    progresoTemporal.clear();
}

void Jugador::mostrarProgreso() const {
    std::cout << "\nProgreso de " << nombre << " (\033[" << color << "m●\033[0m):" << std::endl;
    for (int col = 2; col <= 12; ++col) {
        std::cout << col << ": " << progreso.at(col);
        if (columnasFinalizadas.at(col)) {
            std::cout << " (Completada)";
        }
        std::cout << " | ";
    }
    std::cout << "\nColumnas completadas: " << columnasCompletadas << std::endl;
}
