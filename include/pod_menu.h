#ifndef POD_MENU_H
#define POD_MENU_H


#include <SFML/Graphics.hpp>
#include <windows.h>
#define ILOSC_ELEMENTOW 9
#include <iostream>

class pod_menu
{

    private:
        int wybrany;
        sf::Font font;

    public:
        sf::Text text[ILOSC_ELEMENTOW];
        pod_menu(float width, float height);
        virtual ~pod_menu();
        void draw(sf::RenderWindow &window);
        int wybierz_opcje(sf::RenderWindow &window, sf::Vector2i wektor);
};

#endif // MENU_H
