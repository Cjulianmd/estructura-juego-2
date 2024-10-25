// Atributos de la clase Juego
private:
    std::vector<Jugador*> jugadores;
    std::vector<int> dados;
    Tablero tablero;
    int numJugadores;

// Métodos de la clase Juego

// Constructor
Juego(int numJugadores) : numJugadores(numJugadores) {
    srand(time(nullptr));
    std::vector<std::string> colores = {"31", "32", "33", "34"}; // Rojo, Verde, Amarillo, Azul
    for (int i = 1; i <= numJugadores; ++i) {
        jugadores.push_back(new Jugador("Jugador " + std::to_string(i), colores[i-1]));
    }
}

// Destructor
~Juego() {
    for (auto jugador : jugadores) {
        delete jugador;
    }
}

// Lanza los dados para el turno actual
void lanzarDados() {
    Dado dado;
    dados = dado.lanzarDados();
    std::cout << "Resultados de los dados: ";
    for (int d : dados) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
}

// Verifica si algún jugador ha ganado el juego
bool comprobarVictoria() const {
    return std::any_of(jugadores.begin(), jugadores.end(),
                       [](const Jugador* j) { return j->getColumnasCompletadas() >= 3; });
}

// Devuelve los movimientos posibles basados en los dados lanzados
std::vector<std::pair<int, int>> obtenerMovimientosPosibles() const {
    std::vector<std::pair<int, int>> movimientos;
    movimientos.push_back(std::make_pair(dados[0] + dados[1], dados[2] + dados[3]));
    movimientos.push_back(std::make_pair(dados[0] + dados[2], dados[1] + dados[3]));
    movimientos.push_back(std::make_pair(dados[0] + dados[3], dados[1] + dados[2]));
    return movimientos;
}

// Verifica si el jugador puede avanzar en alguna columna
bool puedeAvanzar(const Jugador* jugador, const std::vector<std::pair<int, int>>& movimientos) const {
    const auto& columnasActivas = jugador->getColumnasActivas();
    for (const auto& movimiento : movimientos) {
        int col1 = movimiento.first;
        int col2 = movimiento.second;
        if (columnasActivas.count(col1) > 0 || columnasActivas.count(col2) > 0) {
            return true;
        }
    }
    return false;
}
