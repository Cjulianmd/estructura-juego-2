// métodos de la clase tablero

private:
    std::vector<std::vector<std::string>> casillas; // Matriz de casillas
    std::vector<int> guia; // Guía de columnas

public:
    // Constructor
    Tablero() : guia{3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3} {
        casillas.resize(11); // Inicializa las casillas
        for (int i = 0; i < 11; ++i) {
            casillas[i].resize(guia[i], "."); // Inicializa cada casilla con "."
        }
    }

    // Método para actualizar el tablero con las posiciones de los jugadores
    void actualizarTablero(const std::map<std::string, std::map<int, int>>& posicionesJugadores) {
        for (int i = 0; i < 11; ++i) {
            std::fill(casillas[i].begin(), casillas[i].end(), "."); // Restaura las casillas
        }

        for (const auto& jugadorPar : posicionesJugadores) {
            const std::string& color = jugadorPar.first;
            const std::map<int, int>& posiciones = jugadorPar.second;
            for (const auto& posicionPar : posiciones) {
                int columna = posicionPar.first;
                int progreso = posicionPar.second;
                int index = columna - 2;
                if (progreso < guia[index]) {
                    casillas[index][progreso] = color; // Asigna el color del jugador
                }
            }
        }
    }

    // Método para mostrar el tablero
    void mostrar() const {
        std::cout << "-------------------" << std::endl;
        for (int fila = 12; fila >= 2; --fila) {
            std::cout << std::setw(2) << fila << ": ";
            for (const std::string& c : casillas[fila - 2]) {
                if (c == ".") {
                    std::cout << c; // Muestra casilla vacía
                } else {
                    std::cout << "\033[" << c << "m●\033[0m"; // Muestra color del jugador
                }
            }
            std::cout << std::endl;
        }
        std::cout << "-------------------" << std::endl;
    }
};
