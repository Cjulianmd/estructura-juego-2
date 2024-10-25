# Proyecto: Juego de Dados

## Descripción
Este proyecto implementa un juego de dados en el que varios jugadores compiten para completar columnas en un tablero. Cada jugador avanza lanzando dados y utilizando los resultados para avanzar en las columnas activas. El juego termina cuando un jugador completa tres columnas.

## Estructura del Código

### Clases

1. **Juego**
   - Maneja la lógica principal del juego.
   - **Atributos**:
     - `jugadores`: vector de punteros a objetos `Jugador`.
     - `dados`: vector que almacena los resultados de los dados lanzados.
     - `tablero`: objeto de la clase `Tablero`.
     - `numJugadores`: número de jugadores en el juego.
   - **Métodos**:
     - `lanzarDados()`: Lanza los dados y muestra los resultados.
     - `comprobarVictoria()`: Verifica si algún jugador ha ganado.
     - `obtenerMovimientosPosibles()`: Devuelve movimientos posibles basados en los dados.
     - `puedeAvanzar()`: Verifica si un jugador puede avanzar en alguna columna.

2. **Jugador**
   - Representa a un jugador en el juego.
   - **Atributos**:
     - `nombre`: nombre del jugador.
     - `color`: color que representa al jugador en el tablero.
     - `progreso`: progreso en las columnas.
     - `progresoTemporal`: progreso temporal.
     - `columnasActivas`: columnas que el jugador puede avanzar.
     - `columnasCompletadas`: columnas que el jugador ha completado.
   - **Métodos**:
     - `avanzarColumna()`: Avanza en una columna si es posible.
     - `finalizarTurno()`: Restablece el progreso temporal al final del turno.
     - Métodos para obtener información sobre el progreso y las columnas activas.

3. **Tablero**
   - Representa el estado del tablero del juego.
   - **Atributos**:
     - `casillas`: matriz que representa las casillas del tablero.
     - `guia`: guía de columnas.
   - **Métodos**:
     - `actualizarTablero()`: Actualiza el tablero según las posiciones de los jugadores.
     - `mostrar()`: Muestra el estado actual del tablero.

4. **Dado**
   - Representa un dado que se puede lanzar.
   - **Atributos**:
     - `generador`: generador de números aleatorios.
     - `distribucion`: distribución uniforme entre 1 y 6.
   - **Métodos**:
     - `lanzar()`: Lanza el dado y devuelve el resultado.

