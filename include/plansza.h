#ifndef PLANSZA.H
#define PLANSZA.H
#include <SFML/Graphics.hpp>

class plansza :public sf::Drawable
{
    private:
        sf::Texture tekstura;
        sf::Sprite sprite;
        void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    public:
        plansza();
};



#endif // PIONEK
