// Atributos de la clase Jugador
private:
    std::string nombre;
    std::string color;
    std::map<int, int> progreso; // Progreso en columnas
    std::map<int, int> progresoTemporal; // Progreso temporal
    std::set<int> columnasActivas; // Columnas activas
    int columnasCompletadas; // Columnas completas

public:
    // Constructor
    Jugador(const std::string& nombre, const std::string& color) 
        : nombre(nombre), color(color), columnasCompletadas(0) {}

    // Método para obtener el nombre del jugador
    std::string getNombre() const {
        return nombre;
    }

    // Método para obtener el color del jugador
    std::string getColor() const {
        return color;
    }

    // Método para avanzar en una columna
    bool avanzarColumna(int columna) {
        if (columnasActivas.count(columna) > 0) {
            progreso[columna]++;
            if (progreso[columna] >= 3) { // Suponiendo que se completan con 3 avances
                columnasCompletadas++;
                columnasActivas.erase(columna);
            }
            return true;
        }
        return false;
    }

    // Método para finalizar el turno
    void finalizarTurno(bool continuar) {
        // Si el jugador no puede avanzar más, restablece el progreso temporal
        if (!continuar) {
            for (auto& col : progresoTemporal) {
                progreso[col.first] = std::max(0, progreso[col.first] - col.second);
            }
            progresoTemporal.clear();
        }
    }

    // Método para agregar progreso temporal a una columna
    void agregarProgresoTemporal(int columna, int cantidad) {
        progresoTemporal[columna] += cantidad;
    }

    // Método para obtener el progreso de una columna
    int getProgreso(int columna) const {
        return progreso.at(columna);
    }

    // Método para obtener el progreso temporal de una columna
    int getProgresoTemporal(int columna) const {
        return progresoTemporal.at(columna);
    }

    // Método para obtener las columnas activas
    const std::set<int>& getColumnasActivas() const {
        return columnasActivas;
    }

    // Método para obtener las columnas completadas
    int getColumnasCompletadas() const {
        return columnasCompletadas;
    }
