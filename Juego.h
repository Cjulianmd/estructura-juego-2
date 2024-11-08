#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <queue>
#include <vector>
#include "Jugador.h"
#include "Dado.h"
#include "Tablero.h"

class Juego {
private:
    std::vector<Jugador*> jugadores;
    std::vector<int> dados;
    Tablero tablero;
    int numJugadores;
    
    void lanzarDados();
    bool comprobarVictoria() const;
    std::vector<std::pair<int, int>> obtenerMovimientosPosibles() const;
    bool puedeAvanzar(const Jugador* jugador, const std::vector<std::pair<int, int>>& movimientos) const;
    void mostrarEstadoJuego(); // Removed const

public:
    Juego(int numJugadores);
    ~Juego();
    void iniciar();
};

#endif
