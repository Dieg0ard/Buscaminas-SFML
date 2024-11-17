#ifndef CUADRICULA_HPP
#define CUADRICULA_HPP

#include "Casilla.hpp"
#include <vector>

class Cuadricula
{
private:
    int filas;
    int columnas;
    int tamañoCasilla;
    std::vector<std::vector<Casilla>> cuadricula;
    int totalMinas;
    bool minaAbierta;
    bool todasMinasAbiertas;
    bool pierdes = false;

public:
    Cuadricula(int filas, int columnas, int minas, int tamCasilla);

    // Función para descubrir una casilla
    void descubrirCasilla(int x, int y);

    // Función para marcar una casilla
    void marcarCasilla(int x, int y);

    // Dibujar la cuadrícula en la ventana
    void dibujar(sf::RenderWindow &window);

    bool todasDescubiertas() const;

    bool perdiste();

    void descubrirMinas();

    bool getTodasMinasAbiertas();
};

#endif
