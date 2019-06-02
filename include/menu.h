#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <windows.h>
#define ILOSC_ELEMENTOW 3

class menu
{

    private:
        int wybrany;
        sf::Font font;

    public:
        sf::Text text[ILOSC_ELEMENTOW];
        menu(float width, float height);
        virtual ~menu();
        void draw(sf::RenderWindow &window);
        int wybierz_opcje(sf::RenderWindow &window, sf::Vector2i wektor);




};

#endif // MENU_H
