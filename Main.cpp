#include "VentanaMensaje.hpp"
#include "Cuadricula.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Buscaminas", sf::Style::Titlebar | sf::Style::Close);
    Cuadricula cuadricula(10, 10, 10, 60);

    bool reiniciarJuego = false;
    bool victoriaMostrada = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && !victoriaMostrada && !cuadricula.perdiste()) {
                int x = event.mouseButton.x / 60;
                int y = event.mouseButton.y / 60;
                if (event.mouseButton.button == sf::Mouse::Left) {
                    cuadricula.descubrirCasilla(x, y);
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    cuadricula.marcarCasilla(x, y);
                }
            }
            if (event.type == sf::Event::KeyPressed && cuadricula.perdiste()) {
                 cuadricula = Cuadricula(10, 10, 10, 60);
            }
        }

        if (!victoriaMostrada && cuadricula.todasDescubiertas()) {
            victoriaMostrada = true;
            VentanaMensaje ventanaVictoria("Victoria!", "Has ganado!");
            ventanaVictoria.mostrar(reiniciarJuego);
            if (reiniciarJuego) {
                cuadricula = Cuadricula(10, 10, 10, 60);
                reiniciarJuego = false;
                victoriaMostrada = false;
            }
        }

        window.clear();
        cuadricula.dibujar(window);
        window.display();
    }

    return -1;
}
