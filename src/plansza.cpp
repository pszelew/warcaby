#include "plansza.h"

 plansza::plansza()
 {
    tekstura.loadFromFile( "img/Plansza_700.png" );
    sprite.setTexture(tekstura);

}



 void plansza::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->sprite, state);
}


