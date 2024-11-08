// Tablero.h
#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

class Tablero {
private:
    std::vector<int> guia;
    std::vector<std::vector<std::vector<std::string>>> casillas;
    int numJugadores;

public:
    Tablero(int numJugadores);
    void actualizarTablero(const std::map<std::string, std::map<int, int>>& posicionesJugadores);
    void mostrar() const;
    const std::vector<int>& getGuia() const { return guia; }
};

#endif // TABLERO_H
