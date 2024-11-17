#ifndef CASILLA_HPP
#define CASILLA_HPP

#include <SFML/Graphics.hpp>

class Casilla {
public:

    sf::Texture texture;
    bool tieneMina = false;   // Indica si la casilla tiene una mina
    bool descubierta = false;  // Indica si la casilla ha sido descubierta
    bool marcada = false;      // Indica si la casilla está marcada
    int minasCercanas = 0;     // Número de minas cercanas

    // Método para dibujar la casilla (rectángulo)
    void setMina();
    void setMinasCercanas(int minasCercanas);
    void dibujar(sf::RenderWindow& window, int x, int y, int tam);
    sf::Sprite asignarSprite(int minas, int tam, int x, int y);
};

#endif
