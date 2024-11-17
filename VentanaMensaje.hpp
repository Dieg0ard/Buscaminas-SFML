#ifndef VENTANA_MENSAJE_HPP
#define VENTANA_MENSAJE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class VentanaMensaje {
public:
    VentanaMensaje(const std::string& titulo, const std::string& mensaje)
        : titulo(titulo), mensaje(mensaje) {}

    void mostrar(bool& reiniciarJuego) {
        sf::RenderWindow ventana(sf::VideoMode(300, 150), titulo, sf::Style::Titlebar | sf::Style::Close);
        sf::Font font;
        if (!font.loadFromFile("recursos/Monocraft.ttf")) {
            std::cerr << "Error cargando la fuente" << std::endl;
            return;
        }

        sf::Text texto(mensaje, font, 24);
        texto.setFillColor(sf::Color::White);
        texto.setPosition(50, 50);

        while (ventana.isOpen()) {
            sf::Event event;
            while (ventana.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    ventana.close();
                    reiniciarJuego = true;
                }
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.display();
        }
    }

private:
    std::string titulo;
    std::string mensaje;
};

#endif
