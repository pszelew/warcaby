#include "pionek.h"
#include <iostream>
pionek::pionek() :kolor(brak), rodz(zwykly), x(9), y(9)
{
    tekstura.loadFromFile( "img/Pionek_80.png" );
    sprite.setTexture(tekstura);
    sprite.setOrigin(40.0f, 40.0f);
}


 pionek::pionek(kolory kol, int xw, int yw): kolor(kol), x(xw), y(yw), rodz(zwykly)
 {
    tekstura.loadFromFile( "img/Pionek_80.png" );
    sprite.setTexture(tekstura);
    sprite.setOrigin(40.0f, 40.0f);
    if(this->kolor==czarny)
        sprite.setColor(sf::Color(160,82, 45)); // brazowy
    ////////////////////////////////////////
    sprite.setPosition(xw*80+70,yw*80+70); //to do zmiany
    //////////////////////////////////////////////
 }


void pionek::kolor_set(kolory kol)
{
    kolor=kol;
    if(this->kolor==czarny)
        sprite.setColor(sf::Color(160,82, 45)); // brazowy
}

void pionek::xy_set(int xw, int yw)
{
    x = xw;
    y = yw;
    sprite.setPosition(xw*80+70,yw*80+70);
}


 void pionek::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->sprite, state);
}

 void pionek::show(kolory kol, rodzaj rod)
{
    kolor=kol;
    rodz=rod;
    if(kol==czarny)
        sprite.setColor(sf::Color(160,82, 45));
    else
        sprite.setColor(sf::Color(255,255, 255));
    ustaw_rodzaj(rod);
}

 void pionek::hide()
{
    kolor=brak;
}


void pionek::podnies()
{
    sprite.setScale(sf::Vector2f(1.5f, 1.5f)); // skala podniesionego
}

void pionek::upusc()
{
    sprite.setScale(sf::Vector2f(1.f, 1.f)); // skala opuszczonego

}


void pionek::ustaw_rodzaj(rodzaj rod)
{
    rodz=rod;
    if(rod==damka)
    {
        tekstura.loadFromFile( "img/Damka_80.png" );
        sprite.setTexture(tekstura);
    }
    else
    {
        tekstura.loadFromFile( "img/Pionek_80.png" );
        sprite.setTexture(tekstura);
    }
}
