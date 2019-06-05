#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "pionek.h"
#include "plansza.h"
#include "gra.h"
#include "bot.h"
#include <iostream>
#include <windows.h>
#include <menu.h>
#include <pod_menu.h>
#include <chrono>
#include <fstream>
int main()
{
    sf::Music music;
    if (!music.openFromFile( "sound/song_1.wav"))
        return -1; // error
    music.setLoop(true);
    music.play();
    sf::RenderWindow window(sf::VideoMode{700,700}, "Warcaby");

    menu _menu(window.getSize().x, window.getSize().y);
    pod_menu _pod_menu(window.getSize().x, window.getSize().y);

    plansza plan;
    bool selected=false;
    bool selected_2=false;
    bool udal_ruch=false;
    bool moge_bic=false;
    bool moge_bic_2=false;
    bool kontynuacja_ruchu=false;
    bool menu=true;
    bool menu_2=false;
    kolory wygrana=brak;
    sf::Texture tekstura;
    sf::Sprite sprite;
    std::fstream testy;
    remove("testy_efektywnosci.txt");
    long long czas=0;
	testy.open( "testy_efektywnosci.txt", std::ios::out|std::ios::app);
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;


    bot bot_warcaby(czarny);
    gra game(bialy, false); //gra bez bota

    int tab_1[2];  //tablica wybranego pionka
    int tab_2[2];  //tablica pola do postawienia
    sf::Vector2i localPosition;
    std::vector<parametry_ruchu> lista_ruchow;

    tekstura.loadFromFile( "img/Start.png" );
    sprite.setTexture(tekstura);
    window.draw(sprite);
    window.display();
    Sleep(6000);

    while(window.isOpen())
    {

            if(game.zwroc_human()==false||(game.zwroc_PC()&&game.zwroc_aktualny_gracz()==bot_warcaby.zwroc_kolor_bota())) //jesli gramy z botem i jest ruch bota
            {
                    window.draw(plan);
                    window.draw(game);
                    window.display();

                    t1 = std::chrono::high_resolution_clock::now();
                    lista_ruchow=bot_warcaby.ruch(game, INT_MIN, INT_MAX);  //wykonuje puste ruchy
                    t2 = std::chrono::high_resolution_clock::now();
                    testy <<czas<<std::endl;
                    for( int i = 0; i < lista_ruchow.size() ; i++ )
                    {
                        moge_bic=game.czy_mam_bicie(lista_ruchow[i].x_s, lista_ruchow[i].y_s);
                        game.ruch(lista_ruchow[i].x_s, lista_ruchow[i].y_s, lista_ruchow[i].x_k, lista_ruchow[i].y_k, moge_bic);
                        czas=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                        std::cout<<lista_ruchow[i].x_s<<", "<<lista_ruchow[i].y_s<<" <- Wykonalem ruch ->"<<lista_ruchow[i].x_k<<", "<<lista_ruchow[i].y_k<<std::endl;
                        if(i<lista_ruchow.size()-1)
                            Sleep(1000);
                    }
                    std::cout<<"Liczba bialych "<< game.zwroc_ilosc_bialych()<<std::endl;
                    std::cout<<"Liczba czarnych "<< game.zwroc_ilosc_czarnych()<<std::endl;
                    game.zrob_damki();
                    game.zmien_gracza();

                    window.draw(plan);
                    window.draw(game);
                    window.display();
                    Sleep(1000);
            }

            sf::Event zdarzenie;
            while(!menu_2&&menu&&window.pollEvent(zdarzenie)) //jesli jestesmy w menu
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!selected_2)
                {
                    localPosition=sf::Mouse::getPosition(window);
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                    int opcja_2=_menu.wybierz_opcje(window, localPosition);
                    switch(opcja_2)
                    {
                        case 0:
                            menu=false;
                            break;
                        case 1:
                            menu_2=true;
                            menu=false;
                            break;
                        case 2:
                            window.close();
                            return 0;
                            break;
                    }
                }
            }


            while(menu_2&&window.pollEvent(zdarzenie)) //jesli jestesmy w menu
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!selected_2)
                {
                    localPosition=sf::Mouse::getPosition(window);
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                    int opcja_2=_pod_menu.wybierz_opcje(window, localPosition);
                    switch(opcja_2)
                    {
                        case 0:
                            game.set_PC(false);
                            game.set_human(true);
                            break;
                        case 1:
                            game.set_PC(true);
                            game.set_human(true);
                            break;
                        case 2:
                            game.set_PC(true);
                            game.set_human(false);
                            break;
                        case 3:
                            bot_warcaby.set_kolor_bota(bialy);
                            break;
                        case 4:
                            bot_warcaby.set_kolor_bota(czarny);
                            break;
                        case 5:
                            bot_warcaby.set_depth(1);
                            break;
                        case 6:
                            bot_warcaby.set_depth(2);
                            break;
                        case 7:
                            bot_warcaby.set_depth(3);
                            break;
                        case 8:
                            menu_2=false;
                            menu=true;
                            break;

                    }

                }
            }

            while(!menu_2&&!menu&&window.pollEvent(zdarzenie))  //jesli nie jestesmy w menu
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    game.reset(bialy);
                    menu=true;
                    menu_2=false;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                {
                    game.reset(bialy);
                }

                if(zdarzenie.type==sf::Event::Closed)
                            window.close();


                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!selected)
                {
                    localPosition=sf::Mouse::getPosition(window);
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                    sf::Vector2i tab=game.wybierz_pole(window, localPosition);
                    tab_1[0]=tab.x;
                    tab_1[1]=tab.y;
                    if(tab.x<=7&&tab.x>=0&&tab.y<=7&&tab.y>=0&&game.wybierz_pionek(tab.x,tab.y))  //jesli kliknieto poprawny pionek -> swoj
                    {

                        selected=true;
                    }
                }

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&selected)
                {
                    localPosition=sf::Mouse::getPosition(window);
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                    sf::Vector2i tab=game.wybierz_pole(window, localPosition);
                    tab_2[0]=tab.x;
                    tab_2[1]=tab.y;
                    if(tab.x<=7&&tab.x>=0&&tab.y<=7&&tab.y>=0)  //jesli kliknieto poprawny pionek -> swoj
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
            if(!menu_2&&menu)
            {
                window.clear();
                _menu.draw(window);
            }

             if(menu_2)
            {
                window.clear();
                _pod_menu.draw(window);
            }
            if(!menu_2&&!menu)
            {
                window.draw(plan);
                window.draw(game);
            }

            window.display();
        }
    return 0;
}
