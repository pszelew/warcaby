#include "pod_menu.h"

pod_menu::pod_menu(float width, float height)
{
    if(!font.loadFromFile("arial.ttf"))
    {
        //blad
    }

    text[0].setFont(font);
    text[0].setColor(sf::Color::White);
    text[0].setString("1v1");
    sf::FloatRect textRect = text[0].getLocalBounds();
    text[0].setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    text[0].setPosition(sf::Vector2f(width/2, height/(ILOSC_ELEMENTOW+1)*1));

    text[1].setFont(font);
    text[1].setColor(sf::Color::White);
    text[1].setString("1vPC");
    textRect = text[1].getLocalBounds();
    text[1].setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    text[1].setPosition(sf::Vector2f(width/2,height/(ILOSC_ELEMENTOW+1)*2));

    text[2].setFont(font);
    text[2].setColor(sf::Color::White);
    text[2].setString("PCvsPC");
    textRect = text[2].getLocalBounds();
    text[2].setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    text[2].setPosition(sf::Vector2f(width/2,height/(ILOSC_ELEMENTOW+1)*3));

    text[3].setFont(font);
    text[3].setColor(sf::Color::White);
    text[3].setString("Zaczyna bot*");
    textRect = text[3].getLocalBounds();
    text[3].setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    text[3].setPosition(sf::Vector2f(width/2,height/(ILOSC_ELEMENTOW+1)*4));


    text[4].setFont(font);
    text[4].setColor(sf::Color::White);
    text[4].setString("Zaczyna gracz*");
    textRect = text[4].getLocalBounds();
    text[4].setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    text[4].setPosition(sf::Vector2f(width/2,height/(ILOSC_ELEMENTOW+1)*5));


    text[5].setFont(font);
    text[5].setColor(sf::Color::White);
    text[5].setString("POWROT");
    textRect = text[5].getLocalBounds();
    text[5].setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    text[5].setPosition(sf::Vector2f(width/2,height/(ILOSC_ELEMENTOW+1)*6));

    //ctor
}

pod_menu::~pod_menu()
{
    //dtor
}


void pod_menu::draw(sf::RenderWindow &window)
{
    for(int i=0;i<ILOSC_ELEMENTOW;i++)
    {
        window.draw(text[i]);
    }
}


int pod_menu::wybierz_opcje(sf::RenderWindow &window, sf::Vector2i wektor)
{
    int width = window.getSize().x;  //pobieramy paramentry naszego wyboru
    int height = window.getSize().y;

    for(int i=0;i<ILOSC_ELEMENTOW;i++)
    {
        if(wektor.x<=(width/2)+100&&wektor.x>=(width/2)-100&&wektor.y<=(height/(ILOSC_ELEMENTOW+1)*(i+1)+50)&&wektor.y>=(height/(ILOSC_ELEMENTOW+1)*(i+1)-50))
        {
            for(int j=0;j<ILOSC_ELEMENTOW;j++)
            {
                text[j].setColor(sf::Color::White);
            }
            text[i].setColor(sf::Color::Red);
            return i;
        }
    }
    return -1;
}
