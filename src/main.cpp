#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "pionek.h"
#include "plansza.h"
#include "gra.h"
#include "bot.h"
#include <iostream>

int main()
{
    sf::Music music;
    if (!music.openFromFile( "sound/Clutch.wav"))
        return -1; // error
    music.play();
    sf::RenderWindow window(sf::VideoMode{700,700}, "Warcaby");

    plansza plan;
    bool selected=false;
    bool udal_ruch=false;
    bool moge_bic=false;
    bool moge_bic_2=false;
    bool kontynuacja_ruchu=false;
    kolory wygrana=brak;

    bot bot_warcaby(czarny);
    gra game(bialy, true); //gra bez bota

    int tab_1[2];  //tablica wybranego pionka
    int tab_2[2];  //tablica pola do postawienia
    sf::Vector2i localPosition;
    std::vector<parametry_ruchu> lista_ruchow;

    while(window.isOpen())
    {
            sf::Event zdarzenie;
            while(window.pollEvent(zdarzenie))
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                            window.close();
                if(zdarzenie.type==sf::Event::Closed)
                            window.close();

                if(game.zwroc_PC()&&game.zwroc_aktualny_gracz()==bot_warcaby.zwroc_kolor_bota()) //jesli gramy z botem i jest ruch bota
                {
                    lista_ruchow=bot_warcaby.ruch(game);  //wykonuje puste ruchy
                    for( int i = 0; i < lista_ruchow.size() ; i++ )
                    {
                        moge_bic=game.czy_mam_bicie(lista_ruchow[i].x_s, lista_ruchow[i].y_s);
                        game.ruch(lista_ruchow[i].x_s, lista_ruchow[i].y_s, lista_ruchow[i].x_k, lista_ruchow[i].y_k, moge_bic);
                        std::cout<<lista_ruchow[i].x_s<<", "<<lista_ruchow[i].y_s<<" <- Wykonalem ruch ->"<<lista_ruchow[i].x_k<<", "<<lista_ruchow[i].y_k<<std::endl;
                    }
                    game.zrob_damki();
                    game.zmien_gracza();

                }

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!selected)
                {
                    localPosition=sf::Mouse::getPosition(window);
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                    tab_1[0]=(localPosition.x-30)/80;
                    tab_1[1]=(localPosition.y-30)/80;
                    if(localPosition.x<=670&&localPosition.x>=30&&localPosition.y<=670&&localPosition.y>=30&&game.wybierz_pionek(tab_1[0], tab_1[1]))  //jesli kliknieto poprawny pionek -> swoj
                    {
                        selected=true;
                    }
                }

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&selected)
                {
                    localPosition=sf::Mouse::getPosition(window);
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                    tab_2[0]=(localPosition.x-30)/80;
                    tab_2[1]=(localPosition.y-30)/80;
                    if(localPosition.x<=670&&localPosition.x>=30&&localPosition.y<=670&&localPosition.y>=30)  //jesli kliknieto poprawny pionek -> swoj
                    {
                        moge_bic=game.czy_mam_bicie(tab_1[0], tab_1[1]);
                        udal_ruch=game.ruch(tab_1[0], tab_1[1], tab_2[0], tab_2[1], moge_bic);
                        moge_bic_2=game.czy_mam_bicie(tab_2[0], tab_2[1]);

                        if(udal_ruch&&!game.bicie()) //gdy nic nie zbilem w tym ruchu
                        {
                            kontynuacja_ruchu=false;
                            game.zrob_damki();
                            game.zmien_gracza();
                            selected = false;

                        }
                        if(udal_ruch&&game.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                        {
                            kontynuacja_ruchu=false;
                            game.zrob_damki();
                            game.zmien_gracza();
                            selected = false;
                        }

                        if(udal_ruch&&game.bicie()&&moge_bic_2)  //gdy zbilem, i mozna isc dalej
                        {
                            kontynuacja_ruchu=true;
                            tab_1[0]=tab_2[0];  //zmien pionek odniesienia na planszy -> nim bedziemy bic
                            tab_1[1]=tab_2[1];  //zmien pionek odniesienia na planszy -> nim bedziemy bic
                            game.podnies_pionek(tab_2[0], tab_2[1]); //tylko podnosze go do gory, nie sprawdzam juz czy mozna go wybrac
                        }
                        if(!udal_ruch&&!kontynuacja_ruchu)  //gdy nie ruszylem sie i nie kontynuujemy ruchu
                        {
                            selected = false;
                        }
                        if(!udal_ruch&&kontynuacja_ruchu)  //gdy nie ruszylem sie, ale kontynuujemy ruch bicia
                        {
                            game.podnies_pionek(tab_1[0], tab_1[1]); //podnies pionek startowy
                        }
                    }
                }
                 if(game.wygrana()==czarny)
                 {
                    std::cout<<"czarny wygral";
                    window.close();
                 }
                 if(game.wygrana()==bialy)
                 {
                    std::cout<<"bialy wygral";
                    window.close();
                 }

                    window.draw(plan);
                    window.draw(game);
                    window.display();
            }


        }
    return 0;
}
