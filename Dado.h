// Dado.h
#ifndef DADO_H
#define DADO_H

#include <vector>
#include <cstdlib>

class Dado {
public:
    std::vector<int> lanzarDados() {
        std::vector<int> resultados(4);
        for (int& dado : resultados) {
            dado = rand() % 6 + 1;
        }
        return resultados;
    }
};

#endif // DADO_H
