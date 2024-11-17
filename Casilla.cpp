#include "Casilla.hpp"
#include <iostream>

void Casilla::dibujar(sf::RenderWindow &window, int x, int y, int tam)
{
    sf::RectangleShape rect(sf::Vector2f(tam, tam));
    sf::Sprite sprite;
    rect.setPosition(x * tam, y * tam);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(1);

    if (descubierta)
    {
        if (tieneMina)
        {
            sprite = asignarSprite(0, tam, x, y);
        }
        else if (minasCercanas > 0)
        {
            sprite = asignarSprite(1, tam, x, y);
        }
        else
        {
            sprite = asignarSprite(2, tam, x, y);
        }
    }
    else
    {
        if (!marcada)
        {
            sprite = asignarSprite(3, tam, x, y);
        }
        else
        {
            sprite = asignarSprite(4, tam, x, y);
        }
    }
    window.draw(sprite);
}

// 1 = Número de minas
// 2 = Sin minas cercanas
// 3 = Casilla sin abrir
// 4 = bandera
// 0 = Mina

sf::Sprite Casilla::asignarSprite(int tipo, int tam, int x, int y)
{
    sf::Sprite sprite;
    if (tipo == 1)
    {
        texture.loadFromFile("recursos/" + std::to_string(minasCercanas) + ".png");
    }
    else if (tipo == 2)
    {
        texture.loadFromFile("recursos/nada.png");
    }
    else if (tipo == 3)
    {
        texture.loadFromFile("recursos/casilla.png");
    }
    else if (tipo == 4)
    {
        texture.loadFromFile("recursos/marcada.png");
    }
    else if (tipo == 0)
    {
        texture.loadFromFile("recursos/mina.png");
    }
    sprite.setTexture(texture);
    sprite.setScale(
        static_cast<float>(tam) / texture.getSize().x,
        static_cast<float>(tam) / texture.getSize().y);

    // Posicionar el sprite
    sprite.setPosition(x * tam, y * tam);

    return sprite;
}

void Casilla::setMinasCercanas(int minasCercanas){
    this->minasCercanas = minasCercanas;
}

void Casilla::setMina(){
    tieneMina = true;
}
