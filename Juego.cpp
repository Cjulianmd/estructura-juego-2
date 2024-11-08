//Juego.cpp

#include "Juego.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

Juego::Juego(int numJugadores) : numJugadores(numJugadores), tablero(numJugadores) {
    srand(time(nullptr));
    std::vector<std::string> colores = {"31", "32", "33", "34"}; // Rojo, Verde, Amarillo, Azul
    for (int i = 0; i < numJugadores; ++i) {
        jugadores.push_back(new Jugador("Jugador " + std::to_string(i + 1), colores[i], i));
    }
}

Juego::~Juego() {
    for (auto jugador : jugadores) {
        delete jugador;
    }
}

void Juego::lanzarDados() {
    Dado dado;
    dados = dado.lanzarDados();
    std::cout << "\nResultados de los dados: ";
    for (int d : dados) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
}

bool Juego::comprobarVictoria() const {
    return std::any_of(jugadores.begin(), jugadores.end(),
                      [](const Jugador* j) { return j->getColumnasCompletadas() >= 3; });
}

std::vector<std::pair<int, int>> Juego::obtenerMovimientosPosibles() const {
    std::vector<std::pair<int, int>> movimientos;
    movimientos.push_back(std::make_pair(dados[0] + dados[1], dados[2] + dados[3]));
    movimientos.push_back(std::make_pair(dados[0] + dados[2], dados[1] + dados[3]));
    movimientos.push_back(std::make_pair(dados[0] + dados[3], dados[1] + dados[2]));
    
    // Eliminar duplicados y combinaciones inválidas
    auto it = std::unique(movimientos.begin(), movimientos.end());
    movimientos.erase(it, movimientos.end());
    
    // Filtrar combinaciones fuera del rango 2-12
    movimientos.erase(
        std::remove_if(movimientos.begin(), movimientos.end(),
                      [](const std::pair<int, int>& p) {
                          return p.first < 2 || p.first > 12 || p.second < 2 || p.second > 12;
                      }),
        movimientos.end()
    );
    
    return movimientos;
}

bool Juego::puedeAvanzar(const Jugador* jugador, const std::vector<std::pair<int, int>>& movimientos) const {
    const auto& columnasActivas = jugador->getColumnasActivas();
    for (const auto& movimiento : movimientos) {
        int col1 = movimiento.first;
        int col2 = movimiento.second;
        if ((columnasActivas.empty() && (!jugador->tieneColumnaFinalizada(col1) || !jugador->tieneColumnaFinalizada(col2))) ||
            (columnasActivas.count(col1) > 0 && !jugador->tieneColumnaFinalizada(col1)) || 
            (columnasActivas.count(col2) > 0 && !jugador->tieneColumnaFinalizada(col2))) {
            return true;
        }
    }
    return false;
}

void Juego::mostrarEstadoJuego() { // Removed const
    std::map<std::string, std::map<int, int>> posicionesJugadores;
    for (const auto& jugador : jugadores) {
        for (int col = 2; col <= 12; ++col) {
            int progresoTotal = jugador->getProgreso(col) + jugador->getProgresoTemporal(col);
            if (progresoTotal > 0) {
                posicionesJugadores[jugador->getColor()][col] = progresoTotal;
            }
        }
    }
    tablero.actualizarTablero(posicionesJugadores);
    tablero.mostrar();
    
}

void Juego::iniciar() {
    std::cout << "\n=== ¡Bienvenido a Can't Stop! ===\n";
    std::cout << "Objetivo: Llegar al final de tres columnas diferentes.\n";
    std::cout << "Cada jugador avanza por su propio carril en cada columna.\n";
    
    while (!comprobarVictoria()) {
        for (Jugador* jugadorActual : jugadores) {
            if (comprobarVictoria()) break;
            
            bool continuarTurno = true;
            bool primerLanzamiento = true;

            std::cout << "\n=== Turno de " << jugadorActual->getNombre() 
                      << " (\033[" << jugadorActual->getColor() << "m●\033[0m) ===\n";

            while (continuarTurno) {
                mostrarEstadoJuego();
                lanzarDados();
                auto movimientosPosibles = obtenerMovimientosPosibles();

                if (!primerLanzamiento && !puedeAvanzar(jugadorActual, movimientosPosibles)) {
                    std::cout << "\n¡No puedes avanzar en ninguna columna activa!\n";
                    std::cout << "Pierdes todo el progreso de este turno.\n";
                    jugadorActual->finalizarTurno(false, tablero.getGuia());
                    break;
                }

                std::cout << "\nMovimientos posibles:\n";
                for (size_t i = 0; i < movimientosPosibles.size(); ++i) {
                    std::cout << i + 1 << ". Columnas " << movimientosPosibles[i].first 
                             << " y " << movimientosPosibles[i].second << std::endl;
                }

                int eleccion;
                do {
                    std::cout << "\nElige un movimiento (1-" << movimientosPosibles.size() 
                             << ") o 0 para pasar: ";
                    std::cin >> eleccion;
                    
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        eleccion = -1;
                    }
                } while (eleccion < 0 || eleccion > static_cast<int>(movimientosPosibles.size()));

                if (eleccion == 0) {
                    std::cout << "\n" << jugadorActual->getNombre() << " decide detenerse.\n";
                    jugadorActual->finalizarTurno(true, tablero.getGuia());
                    continuarTurno = false;
                } else {
                    int col1 = movimientosPosibles[eleccion - 1].first;
                    int col2 = movimientosPosibles[eleccion - 1].second;
                    
                    bool avance1 = jugadorActual->avanzarColumna(col1, tablero.getGuia());
                    bool avance2 = jugadorActual->avanzarColumna(col2, tablero.getGuia());

                    if (!avance1 && !avance2) {
                        std::cout << "\nNo pudiste avanzar en ninguna columna. Elige otro movimiento.\n";
                        continue;
                    }

                    if (continuarTurno && !primerLanzamiento) {
                        char respuesta;
                        do {
                            mostrarEstadoJuego();
                            std::cout << "\n¿Deseas continuar tu turno? (s/n): ";
                            std::cin >> respuesta;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        } while (respuesta != 's' && respuesta != 'n');
                        
                        if (respuesta == 'n') {
                            std::cout << "\n" << jugadorActual->getNombre() << " decide detenerse.\n";
                            jugadorActual->finalizarTurno(true, tablero.getGuia());
                            continuarTurno = false;
                        }
                    }
                }
                
                primerLanzamiento = false;
            }
        }
    }
    
    // Encontrar y anunciar al ganador
    auto ganador = std::find_if(jugadores.begin(), jugadores.end(),
                               [](const Jugador* j) { return j->getColumnasCompletadas() >= 3; });
                               
    std::cout << "\n¡¡¡FELICITACIONES!!!\n";
    std::cout << "¡" << (*ganador)->getNombre() << " ha ganado el juego!\n";
    mostrarEstadoJuego();
}
