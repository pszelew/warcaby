#include "bot.h"
#include <queue>
#include <limits.h>
#include <iostream>
bot::~bot()
{
    //dtor
}


int bot::minimax(gra game, int depth)  //gra przechowuje stan planszy, kolory -czy maksymalizujemy bialego czy czarnego
{
    std::cout<<"mini"<<std::endl;
    int max_ocena;
    int min_ocena;
    int ocena;
    bool udal_ruch=false;
    bool moge_bic=false;
    bool moge_bic_2=false;
    bool kontynuacja_ruchu=false;
    int i_temp;
    int j_temp;
    gra game_2=game;
    /////////Sprawdzamy czy wygrana/////////////////
    ////////////////////////////////////////////////

    kolory czyja_wygrana=game_2.wygrana();  //sprawdz stan wygranej

    if(depth==0||(czyja_wygrana!=brak))
    {
        return game_2.ocena();
    }
    ///////////////////////////////////////////////////////

    //Sprawdzamy sobie pozycje, jakie moga sie teraz wydarzyc!
    if(game_2.zwroc_aktualny_gracz()==bialy) //jesli aktualmym graczem jest bialy
    {
        max_ocena=INT_MIN;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                game_2=game;
                i_temp=i;
                j_temp=j;
                if(game_2.wybierz_pionek(j, i))
                {                                   //trzeba sprawdzic czy to zwykly pionek
                    //tym pionkiem mozemy wykonac jakis ruch, teraz wystarczy sie dowiedziec jaki
                    if(game_2.zwroc_rodzaj(j,i)==zwykly)
                    {
                        moge_bic= game_2.czy_mam_bicie(j_temp, i_temp);
                        if(moge_bic==true)  //jesli pionek nadaje sie do bicia
                        {
                            for(int x=-2;x<=2;x=x+4)
                                for(int y=-2;y<=2;y=y+4)
                                {
                                     if(kontynuacja_ruchu)
                                        moge_bic=moge_bic_2;
                                    if(kontynuacja_ruchu==false)
                                    {
                                        game_2=game;
                                        i_temp=i;
                                        j_temp=j;
                                    }
                                    if(j_temp+y>=0&&j_temp+y<=7&&i_temp+x>=0&&i_temp+x<=7)
                                        udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
                                    else
                                        udal_ruch=false;
                                    moge_bic_2=game_2.czy_mam_bicie(j_temp+y, i_temp+x);
                                    if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                                    {
                                        kontynuacja_ruchu=false;
                                        game_2.zrob_damki();
                                        game_2.zmien_gracza();
                                        ocena=minimax(game_2, depth-1);
                                        max_ocena=std::max(max_ocena, ocena);
                                    }
                                    if(udal_ruch&&game_2.bicie()&&moge_bic_2)  //gdy zbilem, i mozna isc dalej
                                    {
                                        kontynuacja_ruchu=true;
                                        i_temp=x;
                                        j_temp=y;
                                        x=-2;
                                        break;
                                    }
                            }
                        }
                        if(moge_bic==false)
                        {
                            for(int x=-1;x<=1;x=x+2)
                                for(int y=-1;y<=1;y=y+2)
                                {
                                    game_2=game;
                                    if(j_temp+y>=0&&j_temp+y<=7&&i_temp+x>=0&&i_temp+x<=7)
                                        udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
                                    else
                                        udal_ruch=false;
                                    if(udal_ruch) //gdy nic nie zbilem w tym ruchu
                                    {
                                        kontynuacja_ruchu=false;
                                        game_2.zrob_damki();
                                        game_2.zmien_gracza();
                                        ocena=minimax(game_2, depth-1);
                                        max_ocena=std::max(max_ocena, ocena);
                                    }
                            }
                        }

                    }

                    if(game_2.zwroc_rodzaj(j,i)==damka)
                    {

                        for(int x=0;x<8;x++)
                        {
                            moge_bic=game_2.czy_mam_bicie(j_temp, i_temp);                    //jesli wybrany pionek ma bicie
                            for(int y=0;y<8;y++)
                            {
                                if(!kontynuacja_ruchu)
                                {
                                    game_2=game;
                                    i_temp=i;
                                    j_temp=j;
                                }
                                 udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
                                moge_bic_2=game_2.czy_mam_bicie(x, y);
                                if(udal_ruch&&!game_2.bicie()) //gdy nic nie zbilem w tym ruchu
                                {
                                    kontynuacja_ruchu=false;
                                    game_2.zrob_damki();
                                    game_2.zmien_gracza();
                                    ocena=minimax(game_2, depth-1);
                                    max_ocena=std::max(max_ocena, ocena);
                                }

                                if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                                {
                                    kontynuacja_ruchu=false;
                                    game_2.zrob_damki();
                                    game_2.zmien_gracza();
                                    ocena=minimax(game_2, depth-1);
                                    max_ocena=std::max(max_ocena, ocena);
                                }
                                if(udal_ruch&&game_2.bicie()&&moge_bic_2)  //gdy zbilem, i mozna isc dalej
                                {
                                    kontynuacja_ruchu=true;
                                    i_temp=x;
                                    j_temp=y;
                                    x=0;
                                    break;
                                }
                            }
                        }
                    }

    //////////////////////////////////////////////////////smieci//////////////////////////////////
                }
            }
        }
        return max_ocena;
    }

    if(game_2.zwroc_aktualny_gracz()==czarny) //jesli aktualnym graczem jest bialy
    {
        max_ocena=INT_MAX;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                game_2=game;
                i_temp=i;
                j_temp=j;
                if(game_2.wybierz_pionek(j, i))
                {                                   //trzeba sprawdzic czy to zwykly pionek
                    //tym pionkiem mozemy wykonac jakis ruch, teraz wystarczy sie dowiedziec jaki
                    if(game_2.zwroc_rodzaj(j,i)==zwykly)
                    {
                        moge_bic= game_2.czy_mam_bicie(j_temp, i_temp);
                        if(moge_bic==true)  //jesli pionek nadaje sie do bicia
                        {
                            for(int x=-2;x<=2;x=x+4)
                                for(int y=-2;y<=2;y=y+4)
                                {
                                     if(kontynuacja_ruchu)
                                        moge_bic=moge_bic_2;
                                    if(kontynuacja_ruchu==false)
                                    {
                                        game_2=game;
                                        i_temp=i;
                                        j_temp=j;
                                    }
                                    if(j_temp+y>=0&&j_temp+y<=7&&i_temp+x>=0&&i_temp+x<=7)
                                        udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
                                    else
                                        udal_ruch=false;
                                    moge_bic_2=game_2.czy_mam_bicie(j_temp+y, i_temp+x);
                                    if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                                    {
                                        kontynuacja_ruchu=false;
                                        game_2.zrob_damki();
                                        game_2.zmien_gracza();
                                        ocena=minimax(game_2, depth-1);
                                        min_ocena=std::min(min_ocena, ocena);
                                    }
                                    if(udal_ruch&&game_2.bicie()&&moge_bic_2)  //gdy zbilem, i mozna isc dalej
                                    {
                                        kontynuacja_ruchu=true;
                                        i_temp=x;
                                        j_temp=y;
                                        x=-2;
                                        break;
                                    }
                            }
                        }
                        if(moge_bic==false)
                        {
                            for(int x=-1;x<=1;x=x+2)
                                for(int y=-1;y<=1;y=y+2)
                                {
                                    game_2=game;
                                    if(j_temp+y>=0&&j_temp+y<=7&&i_temp+x>=0&&i_temp+x<=7)
                                        udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
                                    else
                                        udal_ruch=false;
                                    if(udal_ruch) //gdy nic nie zbilem w tym ruchu
                                    {
                                        kontynuacja_ruchu=false;
                                        game_2.zrob_damki();
                                        game_2.zmien_gracza();
                                        ocena=minimax(game_2, depth-1);
                                        min_ocena=std::min(min_ocena, ocena);
                                    }
                            }
                        }

                    }

                    if(game_2.zwroc_rodzaj(j,i)==damka)
                    {
                        for(int x=0;x<8;x++)
                        {
                            moge_bic=game_2.czy_mam_bicie(j_temp, i_temp);                    //jesli wybrany pionek ma bicie
                            for(int y=0;y<8;y++)
                            {
                                if(!kontynuacja_ruchu)
                                {
                                    game_2=game;
                                    i_temp=i;
                                    j_temp=j;
                                }
                                udal_ruch=game_2.ruch(j_temp, i_temp, y, x, moge_bic);
                                moge_bic_2=game_2.czy_mam_bicie(x, y);
                                if(udal_ruch&&!game_2.bicie()) //gdy nic nie zbilem w tym ruchu
                                {
                                    kontynuacja_ruchu=false;
                                    game_2.zrob_damki();
                                    game_2.zmien_gracza();
                                    ocena=minimax(game_2, depth-1);
                                    min_ocena=std::min(min_ocena, ocena);
                                }

                                if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                                {
                                    kontynuacja_ruchu=false;
                                    game_2.zrob_damki();
                                    game_2.zmien_gracza();
                                    ocena=minimax(game_2, depth-1);
                                    min_ocena=std::min(min_ocena, ocena);
                                }
                                if(udal_ruch&&game_2.bicie()&&moge_bic_2)  //gdy zbilem, i mozna isc dalej
                                {
                                    kontynuacja_ruchu=true;
                                    i_temp=x;
                                    j_temp=y;
                                    x=0;
                                    break;
                                }
                            }
                        }
                    }

    //////////////////////////////////////////////////////smieci//////////////////////////////////
                }
            }
        }
        return min_ocena;
    }
}


std::vector<parametry_ruchu> bot::ruch(gra game)
{
    int max_ocena=INT_MIN;
    int min_ocena=INT_MAX;
    int depth=max_depth;
    int ocena;
    int i_temp;
    int j_temp;
    bool kontynuacja_ruchu=false;
    bool moge_bic=false;
    bool moge_bic_2=false;
    bool udal_ruch=false;
    bool tab[2][2];
    int tab_i=0;
    int tab_j=0;
    for(int i=0;i<2;i++)      //czy juz sprawdzalem ten przypadek
        for(int j=0;j<2;j++)
            tab[i][j]=false;
    int tab_2[2]; //tablica poprzedniego w ciagu
        for(int i=0;i<2;i++)
            tab_2[i]=-1;
    gra game_2=game;
    //przeszukujemy wszystkie dzieci naszego pionka i dla kazdego z nich robimi minimaksa. Jesli jest bialy -> wybieramy najwieksza wartosc. Jesli jest czarny -> najmniejsza. Dzieci sa innych kolorow
    //robimy liste dzieci naszego korzenia; dziecko ---->
    std::vector<parametry_ruchu> dziecko;  //generujemy sobie dziecko i sprawdzamy minimaxa dla niego
    std::vector<parametry_ruchu> dziecko_temp;  //generujemy sobie pomocnicze dziecko
    parametry_ruchu temp;

    if(game_2.zwroc_aktualny_gracz()==bialy) //jesli aktualmym graczem jest bialy
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                game_2=game;
                i_temp=i;
                j_temp=j;
                if(game_2.wybierz_pionek(j, i))
                {
                    for(int i=0;i<2;i++)
                        for(int j=0;j<2;j++)
                            tab[i][j]=false;

                    if(game_2.zwroc_rodzaj(j,i)==zwykly)
                    {
                        moge_bic= game_2.czy_mam_bicie(j_temp, i_temp);
                        if(moge_bic==true)  //jesli pionek nadaje sie do bicia
                        {
                            if(kontynuacja_ruchu)
                                moge_bic= game_2.czy_mam_bicie(j_temp, i_temp);
                            for(int x=-2;x<=2;x=x+4)
                                for(int y=-2;y<=2;y=y+4)
                                {
                                    if(kontynuacja_ruchu)
                                        moge_bic=moge_bic_2;
                                    if(kontynuacja_ruchu==false)
                                    {
                                        game_2=game;
                                        i_temp=i;
                                        j_temp=j;
                                    }
                                    if(j_temp+y>=0&&j_temp+y<=7&&i_temp+x>=0&&i_temp+x<=7)
                                        udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
                                    else
                                        udal_ruch=false;
                                    if(udal_ruch)
                                        moge_bic_2=game_2.czy_mam_bicie(j_temp+y, i_temp+x);

                                    if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                                    {
                                        game_2.zrob_damki();
                                        game_2.zmien_gracza();
                                        ocena=minimax(game_2, depth);
                                        max_ocena=std::max(max_ocena, ocena);
                                        if(max_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                        {
                                             temp.x_s=j_temp;
                                            temp.y_s=i_temp;
                                            temp.x_k=j_temp+y;
                                            temp.y_k=i_temp+x;

                                            if(!kontynuacja_ruchu)//gdy nie kontynuowalismy ruchu, bo to zupelnie nowe dziecko na 100%
                                            {
                                                dziecko.clear();
                                                dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                            }
                                            else
                                            {
                                                dziecko_temp.push_back(temp); //dodaj parametry do naszego dziecka
                                                dziecko=dziecko_temp;
                                            }
                                        }
                                        kontynuacja_ruchu=false;
                                    }
                                    tab_j=y/2;
                                    tab_i=x/2;

                                     if(udal_ruch&&game_2.bicie()&&moge_bic_2&&tab[tab_i][tab_j]==false)  //gdy zbilem, i mozna isc dalej
                                    {

                                        if(!kontynuacja_ruchu) //gdy wchodze pierwszy raz do petli bicia seryjnego
                                        {
                                            tab[tab_i][tab_j]=true;
                                        }

                                        kontynuacja_ruchu=true;
                                        temp.x_s=j_temp;
                                        temp.y_s=i_temp;
                                        temp.x_k=j_temp+y;
                                        temp.y_k=i_temp+x;

                                        dziecko_temp.push_back(temp);
                                        i_temp=i_temp+x;
                                        j_temp=j_temp+y;
                                        x=-2;
                                        break;
                                    }
                                }
                        }
                        if(moge_bic==false)
                        {
                            for(int x=-1;x<=1;x=x+2)
                                for(int y=-1;y<=1;y=y+2)
                                {
                                    game_2=game;
                                    if(j_temp+y>=0&&j_temp+y<=7&&i_temp+x>=0&&i_temp+x<=7)
                                        udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
                                    else
                                        udal_ruch=false;
                                    if(udal_ruch) //gdy nic nie zbilem w tym ruchu
                                    {
                                        kontynuacja_ruchu=false;
                                        game_2.zrob_damki();
                                        game_2.zmien_gracza();
                                        ocena=minimax(game_2, depth);
                                        max_ocena=std::max(max_ocena, ocena);
                                        if(max_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                        {
                                            temp.x_s=j_temp;
                                            temp.y_s=i_temp;
                                            temp.x_k=j_temp+y;
                                            temp.y_k=i_temp+x;

                                            dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                            dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                        }
                                    }
                                }
                        }
                    }


                    if(game_2.zwroc_rodzaj(j,i)==damka)
                    {
                        for(int x=0;x<8;x++)
                        {
                            moge_bic=game_2.czy_mam_bicie(j_temp, i_temp);                    //jesli wybrany pionek ma bicie
                            for(int y=0;y<8;y++)
                            {
                                if(!kontynuacja_ruchu)
                                {
                                    game_2=game;
                                    i_temp=i;
                                    j_temp=j;
                                }
                                udal_ruch=game_2.ruch(j_temp, i_temp, y, x, moge_bic);
                                moge_bic_2=game_2.czy_mam_bicie(x, y);
                                if(udal_ruch&&!game_2.bicie()) //gdy nic nie zbilem w tym ruchu
                                {
                                    kontynuacja_ruchu=false;
                                    game_2.zrob_damki();
                                    game_2.zmien_gracza();
                                    ocena=minimax(game_2, depth);
                                    max_ocena=std::max(max_ocena, ocena);
                                    if(max_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                    {
                                        temp.x_s=j_temp;
                                        temp.y_s=i_temp;
                                        temp.x_k=j_temp+y;
                                        temp.y_k=i_temp+x;

                                        dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                        dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                    }
                                }

                                if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                                {
                                    game_2.zrob_damki();
                                    game_2.zmien_gracza();
                                    ocena=minimax(game_2, depth);
                                    max_ocena=std::max(max_ocena, ocena);
                                    if(max_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                    {
                                        temp.x_s=j_temp;
                                        temp.y_s=i_temp;
                                        temp.x_k=x;
                                        temp.y_k=y;
                                        if(!kontynuacja_ruchu)//gdy nie kontynuowalismy ruchu, bo to zupelnie nowe dziecko na 100%
                                        {
                                            dziecko.clear();
                                            dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                        }
                                        else
                                        {
                                            dziecko_temp.push_back(temp); //dodaj parametry do naszego dziecka
                                            dziecko=dziecko_temp;
                                        }
                                    }
                                        kontynuacja_ruchu=false;
                                }
                                 if(udal_ruch&&game_2.bicie()&&moge_bic_2)  //gdy zbilem, i mozna isc dalej
                                    {
                                        kontynuacja_ruchu=true;
                                         temp.x_s=j_temp;
                                        temp.y_s=i_temp;
                                        temp.x_k=x;
                                        temp.y_k=y;
                                        dziecko_temp.push_back(temp);
                                        i_temp=x;
                                        j_temp=y;
                                        x=0;
                                        break;
                                    }
                            }
                        }
                    }
                }
            }
        }
        return dziecko;
    }
            /////////////////////////////////////////////////
                    ///////////////////////////////////////////////////
                    ///////////////////////////////////////////////////
                    //tym pionkiem mozemy wykonac jakis ruch, teraz wystarczy sie dowiedziec jaki


   if(game_2.zwroc_aktualny_gracz()==czarny) //jesli aktualnym graczem jest bialy
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                game_2=game;
                i_temp=i;
                j_temp=j;
                if(game_2.wybierz_pionek(j, i))
                {
                    if(game_2.zwroc_rodzaj(j,i)==zwykly)
                    {
                        moge_bic= game_2.czy_mam_bicie(j_temp, i_temp);
                        if(moge_bic==true)  //jesli pionek nadaje sie do bicia
                        {
                            for(int x=-2;x<=2;x=x+4)
                            {
                                for(int y=-2;y<=2;y=y+4)
                                {
                                        game_2=game;  //nowe rozdanie
                                        i_temp=i;
                                        j_temp=j;
                                    if(j_temp+y>=0&&j_temp+y<=7&&i_temp+x>=0&&i_temp+x<=7)
                                    {
                                        udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
                                        if(udal_ruch)
                                        {
                                            std::cout<<j_temp<<" stad "<< i_temp <<std::endl;
                                            std::cout<<j_temp+y<<" dotad "<< i_temp+x <<std::endl;
                                        }
                                    }

                                    else
                                        udal_ruch=false;
                                     if(udal_ruch)
                                    {

                                        moge_bic_2=game_2.czy_mam_bicie(j_temp+y, i_temp+x);
                                    }

                                    if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                                    {
                                        game_2.zrob_damki();
                                        game_2.zmien_gracza();
                                        ocena=minimax(game_2, depth);
                                        min_ocena=std::min(min_ocena, ocena);
                                        if(min_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                        {
                                            temp.x_s=j_temp;
                                            temp.y_s=i_temp;
                                            temp.x_k=j_temp+y;
                                            temp.y_k=i_temp+x;

                                            if(!kontynuacja_ruchu)//gdy nie kontynuowalismy ruchu, bo to zupelnie nowe dziecko na 100%
                                            {
                                                dziecko.clear();
                                                dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                            }
                                            else
                                            {
                                                dziecko_temp.push_back(temp); //dodaj parametry do naszego dziecka
                                                dziecko=dziecko_temp;
                                            }
                                        }
                                        kontynuacja_ruchu=false;
                                    }

                                    j_temp=j_temp+y;
                                    i_temp=i_temp+x;

                                    if(udal_ruch&&moge_bic_2)
                                    while(game_2.bicie()&&moge_bic_2)  //dopoki zbilem, i mozna isc dalej i sie nie wracam
                                    {
                                        std::cout<<"Ruch sie udal i mozna kontynuowac"<<std::endl;
                                        if(kontynuacja_ruchu==false) //gdy wchodze pierwszy raz do petli bicia seryjnego
                                        {
                                            dziecko_temp.clear();
                                            temp.x_s=j_temp-y;  //dodajemy do stosu ruch prowadzacy do tego punktu
                                            temp.y_s=i_temp-x;
                                            temp.x_k=j_temp;
                                            temp.y_k=i_temp;
                                            dziecko_temp.push_back(temp);
                                        }
                                                                            //musimy dodac udany ruch
                                        for(int k=-2;k<=2;k=k+4)
                                        {
                                            for(int l=-2;l<=2;l=l+4)
                                            {
                                                if(j_temp+l>=0&&j_temp+l<=7&&i_temp+k>=0&&i_temp+k<=7)
                                                    udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+l, i_temp+k, moge_bic_2);
                                                else
                                                    udal_ruch=false;
                                                if(udal_ruch)
                                                {
                                                    std::cout<<"ttutut"<<std::endl;
                                                    moge_bic_2=game_2.czy_mam_bicie(j_temp+l, i_temp+k);
                                                }

                                                if(!moge_bic_2&&udal_ruch) //jesli nie moge juz bic i ruch sie udal
                                                {
                                                    game_2.zrob_damki();
                                                    game_2.zmien_gracza();
                                                    ocena=minimax(game_2, depth);
                                                    min_ocena=std::min(min_ocena, ocena);
                                                    if(min_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                                    {
                                                        temp.x_s=j_temp;
                                                        temp.y_s=i_temp;
                                                        temp.x_k=j_temp+l;
                                                        temp.y_k=i_temp+k;
                                                        dziecko_temp.push_back(temp); //dodaj parametry do naszego dziecka
                                                        dziecko=dziecko_temp;
                                                        kontynuacja_ruchu=false;
                                                    }
                                                }

                                                if(moge_bic_2&&udal_ruch) //jesli jeszze moge bic i ruch sie udal
                                                {
                                                    temp.x_s=j_temp;
                                                    temp.y_s=i_temp;
                                                    temp.x_k=j_temp+l;
                                                    temp.y_k=i_temp+k;
                                                    dziecko_temp.push_back(temp);
                                                    i_temp=i_temp+k;
                                                    j_temp=j_temp+l;
                                                    kontynuacja_ruchu=true;
                                                }

                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if(moge_bic==false)
                        {
                            for(int x=-1;x<=1;x=x+2)
                                for(int y=-1;y<=1;y=y+2)
                                {
                                    game_2=game;

                                    if(j_temp+y>=0&&j_temp+y<=7&&i_temp+x>=0&&i_temp+x<=7)
                                        udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
                                    else
                                        udal_ruch=false;
                                    if(udal_ruch)
                                    {
                                        std::cout<<j_temp<<" stad "<< i_temp <<std::endl;
                                        std::cout<<j_temp+y<<" dotad "<< i_temp+x <<std::endl;
                                    }
                                    if(udal_ruch&&!game_2.bicie()) //gdy nic nie zbilem w tym ruchu
                                    {
                                        kontynuacja_ruchu=false;
                                        game_2.zrob_damki();
                                        game_2.zmien_gracza();
                                        ocena=minimax(game_2, depth);
                                        min_ocena=std::min(min_ocena, ocena);
                                        if(min_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                        {
                                            temp.x_s=j_temp;
                                            temp.y_s=i_temp;
                                            temp.x_k=j_temp+y;
                                            temp.y_k=i_temp+x;
                                            dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                            dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                        }
                                    }
                                }
                        }
                    }


                    if(game_2.zwroc_rodzaj(j,i)==damka)
                    {
                        for(int x=0;x<8;x++)
                        {
                            moge_bic=game_2.czy_mam_bicie(j_temp, i_temp);                    //jesli wybrany pionek ma bicie
                            for(int y=0;y<8;y++)
                            {
                                if(!kontynuacja_ruchu)
                                {
                                    game_2=game;
                                    i_temp=i;
                                    j_temp=j;
                                }
                                udal_ruch=game_2.ruch(j_temp, i_temp, y, x, moge_bic);
                                moge_bic_2=game_2.czy_mam_bicie(x, y);
                                if(udal_ruch&&!game_2.bicie()) //gdy nic nie zbilem w tym ruchu
                                {
                                    kontynuacja_ruchu=false;
                                    game_2.zrob_damki();
                                    game_2.zmien_gracza();
                                    ocena=minimax(game_2, depth);
                                    min_ocena=std::min(min_ocena, ocena);
                                    if(min_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                    {
                                        temp.x_s=j_temp;
                                        temp.y_s=i_temp;
                                        temp.x_k=x;
                                        temp.y_k=y;

                                        dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                        dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                    }
                                }

                                if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                                {
                                    game_2.zrob_damki();
                                    game_2.zmien_gracza();
                                    ocena=minimax(game_2, depth);
                                    min_ocena=std::min(min_ocena, ocena);
                                    if(min_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                    {
                                         temp.x_s=j_temp;
                                        temp.y_s=i_temp;
                                        temp.x_k=x;
                                        temp.y_k=y;

                                        if(!kontynuacja_ruchu)//gdy nie kontynuowalismy ruchu, bo to zupelnie nowe dziecko na 100%
                                        {
                                            dziecko.clear();
                                            dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                        }
                                        else
                                        {
                                            dziecko_temp.push_back(temp); //dodaj parametry do naszego dziecka
                                            dziecko=dziecko_temp;
                                        }
                                    }
                                        kontynuacja_ruchu=false;
                                }
                                 if(udal_ruch&&game_2.bicie()&&moge_bic_2)  //gdy zbilem, i mozna isc dalej
                                {
                                        kontynuacja_ruchu=true;
                                         temp.x_s=j_temp;
                                        temp.y_s=i_temp;
                                        temp.x_k=x;
                                        temp.y_k=y;

                                        dziecko_temp.push_back(temp);
                                        i_temp=x;
                                        j_temp=y;
                                        x=0;
                                        break;
                                }
                            }
                        }
                    }
                }
            }
        }
        return dziecko;
    }
}
