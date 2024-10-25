//métodos y odjetos de la clase dado
private:
    std::mt19937 generador; // Generador de números aleatorios (Mersenne Twister)
    std::uniform_int_distribution<int> distribucion; // Distribución uniforme entre 1 y 6

public:
    // Constructor
    Dado() : generador(std::random_device{}()), distribucion(1, 6) {}

    // Método para lanzar el dado
    int lanzar() {
        int resultado = distribucion(generador); // Genera un número aleatorio entre 1 y 6
        std::cout << "El dado ha caído en: " << resultado << std::endl;
        return resultado;
    }
};
