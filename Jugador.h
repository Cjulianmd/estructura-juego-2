#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

class Jugador {
private:
    std::string nombre;
    std::map<int, int> progreso;
    std::set<int> columnasActivas;
    std::map<int, int> progresoTemporal;
    int columnasCompletadas;
    std::string color;
    int jugadorIndex;
    std::map<int, bool> columnasFinalizadas;

public:
    Jugador(std::string nombre, std::string color, int index);
    bool avanzarColumna(int columna, const std::vector<int>& guia);
    void finalizarTurno(bool exitoso, const std::vector<int>& guia);
    void mostrarProgreso() const;
    std::string getNombre() const { return nombre; }
    int getProgreso(int columna) const { return progreso.at(columna); }
    int getProgresoTemporal(int columna) const { return progresoTemporal.count(columna) ? progresoTemporal.at(columna) : 0; }
    int getColumnasCompletadas() const { return columnasCompletadas; }
    std::string getColor() const { return color; }
    const std::set<int>& getColumnasActivas() const { return columnasActivas; }
    int getIndex() const { return jugadorIndex; }
    bool tieneColumnaFinalizada(int columna) const { return columnasFinalizadas.at(columna); }
};

#endif // JUGADOR_H
