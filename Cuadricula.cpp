#include "Cuadricula.hpp"
#include <cstdlib>
#include <ctime>


Cuadricula::Cuadricula(int filas, int columnas, int minas, int tamCasilla)
    : filas(filas), columnas(columnas), totalMinas(minas), tamañoCasilla(tamCasilla) {

    cuadricula.resize(filas, std::vector<Casilla>(columnas));

    // Inicialización aleatoria de las minas
    srand(time(0));
    for (int i = 0; i < totalMinas; ++i) {
        int x = rand() % filas;
        int y = rand() % columnas;
        // Asegurarse de que no haya minas duplicadas
        while (cuadricula[x][y].tieneMina) {
            x = rand() % filas;
            y = rand() % columnas;
        }
        cuadricula[x][y].setMina();
    }

    // Calcular las minas cercanas para cada casilla
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (cuadricula[i][j].tieneMina) {
                continue;
            }
            int minasCercanas = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = i + dx;
                    int ny = j + dy;
                    if (nx >= 0 && ny >= 0 && nx < filas && ny < columnas && cuadricula[nx][ny].tieneMina) {
                        minasCercanas++;
                    }
                }
            }
            cuadricula[i][j].setMinasCercanas(minasCercanas);
        }
    }
}

//Abre la casilla de coordenadas (x, y)
void Cuadricula::descubrirCasilla(int x, int y) {
    if (x < 0 || x >= filas || y < 0 || y >= columnas || cuadricula[x][y].descubierta) {
        return;
        //Si las coordenadas no corresponden a ninguna casiilla o
        //si la casilla ya está descubierta, no hace nada
    }
    cuadricula[x][y].descubierta = true;
    if (cuadricula[x][y].tieneMina && cuadricula[x][y].descubierta && !minaAbierta)
    {
        descubrirMinas();
        minaAbierta = true;
    }
    
    if (cuadricula[x][y].minasCercanas == 0 && !cuadricula[x][y].tieneMina) {
        // Si la casilla no tiene minas cercanas, descubrir las adyacentes
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                descubrirCasilla(x + dx, y + dy);
            }
        }
    }
}

//Pone o quita una bandera sobre la casilla de coordenadas (x, y)
void Cuadricula::marcarCasilla(int x, int y) {
    if (!cuadricula[x][y].descubierta) {
        cuadricula[x][y].marcada = !cuadricula[x][y].marcada;
    }
}

//Itera sobre cada casilla de la cuadricula
//invocando al método dibujar
void Cuadricula::dibujar(sf::RenderWindow& window) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cuadricula[i][j].dibujar(window, i, j, tamañoCasilla);
        }
    }
}

//Devuelve true si el jugador perdió
bool Cuadricula::perdiste() {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (cuadricula[i][j].descubierta && cuadricula[i][j].tieneMina) {
                return true;
            }
        }
    }
    return false; 
}

bool Cuadricula::todasDescubiertas() const {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Si hay una casilla sin mina que no está descubierta, devolver false
            if (!cuadricula[i][j].descubierta && !cuadricula[i][j].tieneMina) {
                return false;
            }
        }
    }
    return true; // Todas las casillas sin mina están descubiertas
}

//Abre todas las minas cuando el jugador pierde
void Cuadricula::descubrirMinas() {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (cuadricula[i][j].tieneMina) {
                descubrirCasilla(i, j);
            }
        }
    }
    todasMinasAbiertas = true;
}

bool Cuadricula::getTodasMinasAbiertas(){
    return todasMinasAbiertas;
}




