#include "gra.h"
#include <SFML/Window.hpp>
#include <iostream>


gra::gra(kolory kol, bool PCt) :tryb_gry(kol),aktualny_gracz(bialy), ilosc_bialych(12), ilosc_czarnych(12), czy_bylo_bicie(false), PC(PCt), human(true), ilosc_damek_bialych(0), ilosc_damek_czarnych(0)
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            tablica_pola[i][j].xy_set(j,i);
        }

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(kol==czarny)
            {
                if((i%2==1&&j%2==0)||(i%2==0&&j%2==1))
                {
                    tablica_pola[i][j].kolor_set(bialy);
                }
            }

            if(kol==bialy)
            {
                if((i%2==1&&j%2==0)||(i%2==0&&j%2==1))
                {
                    tablica_pola[i][j].kolor_set(czarny);
                }
            }
        }
    }




    for(int i=7;i>=5;i--)
    {
        for(int j=0;j<8;j++)
        {
            if(kol==bialy)
            {
                if((i%2==1&&j%2==0)||(i%2==0&&j%2==1))
                {
                    tablica_pola[i][j].kolor_set(bialy);
                }
            }

            if(kol==czarny)
            {
                if((i%2==1&&j%2==0)||(i%2==0&&j%2==1))
                {
                    tablica_pola[i][j].kolor_set(czarny);
                }
            }
        }
    }
}

gra::~gra()
{
}

void gra::zmien_gracza()
{
    if(aktualny_gracz==czarny)
        aktualny_gracz=bialy;
    else
        aktualny_gracz=czarny;
}



void gra::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    kolory kol;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            kol=tablica_pola[i][j].zwroc_kolor();
            if(kol!=brak)
            {
                target.draw(this->tablica_pola[i][j], state);
            }
        }
}

bool gra::pole_wolne(int xw, int yw)
{
    if(tablica_pola[xw][yw].zwroc_kolor()==brak)
        return true;
    return false;
}

bool gra::pole_czarny(int xw, int yw)
{
    if(tablica_pola[xw][yw].zwroc_kolor()==czarny)
        return true;
    return false;
}


bool gra::pole_bialy(int xw, int yw)
{
    if(tablica_pola[xw][yw].zwroc_kolor()==bialy)
        return true;
    return false;
}



void gra::przesun_pionek(int x_s, int y_s, int x_k, int y_k)
{
    tablica_pola[y_s][x_s].hide();
    tablica_pola[y_s][x_s].upusc();
    tablica_pola[y_k][x_k].show(aktualny_gracz, tablica_pola[y_s][x_s].zwroc_rodzaj());
}


void gra::usun_pionek(int x_s, int y_s)
{
    tablica_pola[y_s][x_s].hide();
}

void gra::zrob_damke(int x_s, int y_s)
{
    tablica_pola[y_s][x_s].ustaw_rodzaj(damka);
}

bool gra::ruch(int x_s, int y_s, int x_k, int y_k, bool moge_bic)  //tu sie bedzie dzialo XDDDDD
{
    int help_x=x_k;
    int help_y=y_k;
    int help_1=0;
    int help_2=0;
    /*Sprawdzamy czy ruch z start do konca jest mozliwy. Jesli nie to odrazu false, jesli tak , to ruszamy pionkami za pomoca przesun pionek*/
    //sprawdz czy na tym polu jest juz jakis pionek!!!
    if(tablica_pola[y_k][x_k].zwroc_kolor()!=brak)
    {
        tablica_pola[y_s][x_s].upusc();
            return false;
    }

    if(tablica_pola[y_s][x_s].zwroc_rodzaj()==zwykly)
    {
        //sprawdz czy to dozwolony zwykly ruch do przodu
        if(tryb_gry==aktualny_gracz&&!moge_bic)   //jesli jest ruch tego na dole i nie musi bic
            if((x_k==x_s-1&&y_k==y_s-1)||(x_k==x_s+1&&y_k==y_s-1)) //jesli ruszamy sie z dobrym kierunku
            {
                przesun_pionek(x_s, y_s, x_k, y_k);
                czy_bylo_bicie=false;
                return true;
            }
        if(tryb_gry!=aktualny_gracz&&!moge_bic) //jesli jest ruch tego na gorze i nie musi bic
            if((x_k==x_s-1&&y_k==y_s+1)||(x_k==x_s+1&&y_k==y_s+1)) //jesli ruszamy sie z dobrym kierunku
            {
                przesun_pionek(x_s, y_s, x_k, y_k);
                czy_bylo_bicie=false;
                return true;
            }

            if(!moge_bic)    //teraz jesli nie moge bic, to po co sprawdzac dalej
            {
                tablica_pola[y_s][x_s].upusc();
                return false;
            }
            if(aktualny_gracz==bialy)
            {
                if((x_k==x_s-2&&y_k==y_s-2)) //jesli ruszamy do gory i w lewo
                {
                    if(tablica_pola[y_s-1][x_s-1].zwroc_kolor()==czarny) //jesli mozliwosc bicia w danym kierunku
                    {
                        usun_pionek(x_s-1, y_s-1);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[y_s-1][x_s-1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }

                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[y_s-1][x_s-1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }


                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }

                if((x_k==x_s+2&&y_k==y_s-2)) //jesli ruszamy do gory i w prawo
                {
                    if(tablica_pola[y_s-1][x_s+1].zwroc_kolor()==czarny) //jesli mozliwosc bicia w danym kierunku
                    {
                        usun_pionek(x_s+1, y_s-1);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[y_s-1][x_s+1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }

                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[y_s-1][x_s+1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }

                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }

                if((x_k==x_s+2&&y_k==y_s+2)) //jesli ruszamy w dol i w prawo
                {
                    if(tablica_pola[y_s+1][x_s+1].zwroc_kolor()==czarny) //jesli mozliwosc bicia w danym kierunku
                    {
                        usun_pionek(x_s+1, y_s+1);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[y_s+1][x_s+1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }

                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[y_s+1][x_s+1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }

                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }


                if((x_k==x_s-2&&y_k==y_s+2)) //jesli ruszamy w dol i w lewo
                {
                    if(tablica_pola[y_s+1][x_s-1].zwroc_kolor()==czarny) //jesli mozliwosc bicia w danym kierunku
                    {
                        usun_pionek(x_s-1, y_s+1);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[y_s+1][x_s-1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }

                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[y_s+1][x_s-1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }

                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }
            }

            if(aktualny_gracz==czarny)
            {
                if((x_k==x_s-2&&y_k==y_s-2)) //jesli ruszamy do gory i w lewo
                {
                    if(tablica_pola[y_s-1][x_s-1].zwroc_kolor()==bialy) //jesli mozliwosc bicia w danym kierunku
                    {
                        usun_pionek(x_s-1, y_s-1);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[y_s-1][x_s-1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }
                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[y_s-1][x_s-1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }
                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }

                if((x_k==x_s+2&&y_k==y_s-2)) //jesli ruszamy do gory i w prawo
                {
                    if(tablica_pola[y_s-1][x_s+1].zwroc_kolor()==bialy) //jesli mozliwosc bicia w danym kierunku
                    {
                        usun_pionek(x_s+1, y_s-1);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[y_s-1][x_s+1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }
                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[y_s-1][x_s+1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }

                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }

                if((x_k==x_s+2&&y_k==y_s+2)) //jesli ruszamy w dol i w prawo
                {
                    if(tablica_pola[y_s+1][x_s+1].zwroc_kolor()==bialy) //jesli mozliwosc bicia w danym kierunku
                    {
                        usun_pionek(x_s+1, y_s+1);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[y_s+1][x_s+1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }
                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[y_s+1][x_s+1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }

                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }


                if((x_k==x_s-2&&y_k==y_s+2)) //jesli ruszamy w dol i w lewo
                {
                    if(tablica_pola[y_s+1][x_s-1].zwroc_kolor()==bialy) //jesli mozliwosc bicia w danym kierunku
                    {
                        usun_pionek(x_s-1, y_s+1);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[y_s+1][x_s-1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }
                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[y_s+1][x_s-1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }
                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }
            }
    }

    if(tablica_pola[y_s][x_s].zwroc_rodzaj()==damka) //gdy mamy doczynienia z damka
    {
        if(!moge_bic)   //jesli nie moge bic w zaden sposob -> moge sie ruszyc jak chce
        {
            if((((y_k-y_s)==(x_k-x_s))||((y_k-y_s)==-(x_k-x_s)))&&y_k!=y_s) //jesli ruszamy sie po przekatnej
            {
                przesun_pionek(x_s, y_s, x_k, y_k);
                czy_bylo_bicie=false;
                return true;
            }
        }
        //w ktorym kierunku chce sie poruszac


        if(((y_k-y_s)==(x_k-x_s))&&y_k<y_s) //czy poruszamy sie po przekatnej gora i lewo
        {
            while(help_x<x_s-1&&help_y<y_s-1&&tablica_pola[help_y+1][help_x+1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
            {
                help_x++;
                help_y++;
            }
            ///////////////////////////////////////
            help_1=help_x+1; /////////////////////
            help_2=help_y+1; ////////////////////   aktualnie rozwazany pionek
            /////////////////////////////////////
            if(tablica_pola[help_2][help_1].zwroc_kolor()!=aktualny_gracz) //jesli znaleziono pionek przeciwnika w gorze i w lewo
            {
                if(tablica_pola[help_y][help_x].zwroc_kolor()==brak) //jesli poprzednie pole jest puste, pionka mozna zbic
                {
                    //wiemy ze pionka da sie zbic, co najmniej jednego pionka

                    help_x++;
                    help_y++;

                    //szukamy innych pionkow po drodze do naszego celu
                    while(help_x<x_s-1&&help_y<y_s-1&&tablica_pola[help_y+1][help_x+1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
                    {
                        help_x++;
                        help_y++;
                    }

                    if(help_x==x_s-1&&help_y==y_s-1) //jesli nie znaleziono pionka na drodze do naszego celu, wykonujemy ruch
                    {
                        usun_pionek(help_1, help_2);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[help_2][help_1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }

                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[help_2][help_1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }

                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }
            }
        }
        else if(((y_k-y_s)==(x_k-x_s))&&y_k>y_s) //czy poruszamy sie po przekatnej dol i prawo
        {
            while(help_x>x_s+1&&help_y>y_s+1&&tablica_pola[help_y-1][help_x-1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
            {
                help_x--;
                help_y--;

            }
             ///////////////////////////////////////
            help_1=help_x-1; /////////////////////
            help_2=help_y-1; ////////////////////   aktualnie rozwazany pionek
            /////////////////////////////////////


            if(tablica_pola[help_2][help_1].zwroc_kolor()!=aktualny_gracz) //jesli znaleziono pionek przeciwnika w gorze i w lewo
            {
                if(tablica_pola[help_y][help_x].zwroc_kolor()==brak) //jesli poprzednie pole jest puste, pionka mozna zbic
                {
                    //wiemy ze pionka da sie zbic, co najmniej jednego pionka
                    help_x--;
                    help_y--;
                    //szukamy innych pionkow po drodze do naszego celu
                    while(help_x>x_s+1&&help_y>y_s+1&&tablica_pola[help_y-1][help_x-1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
                    {
                        help_x--;
                        help_y--;
                    }

                    if(help_x==x_s+1&&help_y==y_s+1) //jesli nie znaleziono pionka na drodze do naszego celu, wykonujemy ruch
                    {
                        usun_pionek(help_1, help_2);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[help_2][help_1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }
                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[help_2][help_1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }
                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }
            }
        }
        else if(((y_k-y_s)==-(x_k-x_s))&&y_k<y_s) //czy poruszamy sie po przekatnej gora i prawo
        {
            while(help_x>x_s+1&&help_y<y_s-1&&tablica_pola[help_y+1][help_x-1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
            {
                help_x--;
                help_y++;
            }
            ///////////////////////////////////////
            help_1=help_x-1; /////////////////////
            help_2=help_y+1; ////////////////////   aktualnie rozwazany pionek
            /////////////////////////////////////

            if(tablica_pola[help_2][help_1].zwroc_kolor()!=aktualny_gracz) //jesli znaleziono pionek przeciwnika w gorze i w lewo
            {
                if(tablica_pola[help_y][help_x].zwroc_kolor()==brak) //jesli poprzednie pole jest puste, pionka mozna zbic
                {
                    //wiemy ze pionka da sie zbic, co najmniej jednego pionka

                    help_x--;
                    help_y++;

                    //szukamy innych pionkow po drodze do naszego celu
                    while(help_x>x_s+1&&help_y<y_s-1&&tablica_pola[help_y+1][help_x-1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
                    {
                        help_x--;
                        help_y++;
                    }

                    if(help_x==x_s+1&&help_y==y_s-1) //jesli nie znaleziono pionka na drodze do naszego celu, wykonujemy ruch
                    {
                        usun_pionek(help_1, help_2);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[help_2][help_1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }
                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[help_2][help_1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }

                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }
            }
        }
        else if(((y_k-y_s)==-(x_k-x_s))&&y_k>y_s) //czy poruszamy sie po przekatnej dol i lewo
        {
            while(help_x<x_s-1&&help_y>y_s+1&&tablica_pola[help_y-1][help_x+1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
            {
                help_x++;
                help_y--;
            }
            ///////////////////////////////////////
            help_1=help_x+1; /////////////////////
            help_2=help_y-1; ////////////////////   aktualnie rozwazany pionek
            /////////////////////////////////////

            if(tablica_pola[help_2][help_1].zwroc_kolor()!=aktualny_gracz) //jesli znaleziono pionek przeciwnika w gorze i w lewo
            {
                if(tablica_pola[help_y][help_x].zwroc_kolor()==brak) //jesli poprzednie pole jest puste, pionka mozna zbic
                {
                    //wiemy ze pionka da sie zbic, co najmniej jednego pionka

                    help_x++;
                    help_y--;

                    //szukamy innych pionkow po drodze do naszego celu
                    while(help_x<x_s-1&&help_y>y_s+1&&tablica_pola[help_y-1][help_x+1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
                    {
                        help_x++;
                        help_y--;
                    }

                    if(help_x==x_s-1&&help_y==y_s+1) //jesli nie znaleziono pionka na drodze do naszego celu, wykonujemy ruch
                    {
                        usun_pionek(help_1, help_2);   //usun zbity pionek
                        if(aktualny_gracz==bialy)
                        {
                            ilosc_czarnych--;
                            if(tablica_pola[help_2][help_1].zwroc_rodzaj()==damka)
                                ilosc_damek_czarnych--;
                        }

                        else
                        {
                            ilosc_bialych--;
                            if(tablica_pola[help_2][help_1].zwroc_rodzaj()==damka)
                                ilosc_damek_bialych--;
                        }


                        przesun_pionek(x_s, y_s, x_k, y_k);
                        czy_bylo_bicie=true;
                        return true;
                    }
                }
            }
        }
    }
    tablica_pola[y_s][x_s].upusc();
    return false;
}

bool gra::wybierz_pionek(int xw, int yw)
{
        //sprawdzic czy mamy jakis pionek z biciem i go zapamietac
        bool moge_zbic=false; //czy moge zbic jaki kolwiek z pionkow

        if(tablica_pola[yw][xw].zwroc_kolor()==aktualny_gracz) //jesli kliknieto pionek naszego koloru
        {
            for(int i=0; i<8; i++)  //sprawdzamy czy sa jakies nasze pionki ktorymi mozna bic
                for(int j=0; j<8; j++)
                {
                        if(tablica_pola[i][j].zwroc_kolor()==aktualny_gracz&&czy_mam_bicie(j,i))
                        {
                            if(j==xw&&i==yw) //jesli sprawdzilismy ze nasz pionek moze bic, wybieramy go
                            {
                                tablica_pola[yw][xw].podnies();
                                return true;
                            }
                            moge_zbic=true; //moge bic, ale to nie nasz pionek
                            i=8; //lamiemy petle
                            j=8; //lamiemy petle
                        }
                }

            if(moge_zbic==false) //jesli nie znaleziono zadnego pionka ktorym mozna by bic
            {
                tablica_pola[yw][xw].podnies();
                return true;
            }
            if(moge_zbic==true) //jesli inny pionek moze bic
            {
                if(czy_mam_bicie(xw,yw)) //czy nasz ma bicie
                {
                    tablica_pola[yw][xw].podnies();
                    return true;
                }
            }
            //jesli znaleziono pionki ktorymi mozna bic -> sprawdzamy czy nasz pionek nalezy
        }
    return false;
}

void gra::odstaw_pionek(int xw, int yw)
{
    tablica_pola[yw][xw].upusc();
}

bool gra::czy_mam_bicie(int xw, int yw)
{
    int help_x=xw;
    int help_y=yw;
    bool czy_mam_pionek=false;

    //dla zwyklego pionka
    if(tablica_pola[yw][xw].zwroc_rodzaj()==zwykly) //jesli pracujemy ze zwyklym pionkiem
    {
        if(aktualny_gracz==bialy)
        {
            if(xw>=2&&yw>=2&&tablica_pola[yw-1][xw-1].zwroc_kolor()==czarny) // gora lewo
            {
                if(tablica_pola[yw-2][xw-2].zwroc_kolor()==brak)
                {
                    return true;
                }
            }

            if(xw<=5&&yw>=2&&tablica_pola[yw-1][xw+1].zwroc_kolor()==czarny) // gora prawo
            {
                if(tablica_pola[yw-2][xw+2].zwroc_kolor()==brak)
                {
                    return true;
                }
            }

            if(xw>=2&&yw<=5&&tablica_pola[yw+1][xw-1].zwroc_kolor()==czarny) // Dol lewo
            {
                if(tablica_pola[yw+2][xw-2].zwroc_kolor()==brak)
                {
                    return true;
                }
            }

            if(xw<=5&&yw<=5&&tablica_pola[yw+1][xw+1].zwroc_kolor()==czarny) // dol prawo
            {
                if(tablica_pola[yw+2][xw+2].zwroc_kolor()==brak)
                {
                    return true;
                }
            }
        }


        if(aktualny_gracz==czarny)
        {
            if(xw>=2&&yw>=2&&tablica_pola[yw-1][xw-1].zwroc_kolor()==bialy) // gora lewo
            {
                if(tablica_pola[yw-2][xw-2].zwroc_kolor()==brak)
                {
                    return true;
                }
            }

            if(xw<=5&&yw>=2&&tablica_pola[yw-1][xw+1].zwroc_kolor()==bialy) // gora prawo
            {
                if(tablica_pola[yw-2][xw+2].zwroc_kolor()==brak)
                {
                    return true;
                }
            }

            if(xw>=2&&yw<=5&&tablica_pola[yw+1][xw-1].zwroc_kolor()==bialy) // Dol lewo
            {
                if(tablica_pola[yw+2][xw-2].zwroc_kolor()==brak)
                {
                    return true;
                }
            }

            if(xw<=5&&yw<=5&&tablica_pola[yw+1][xw+1].zwroc_kolor()==bialy) // dol prawo
            {
                if(tablica_pola[yw+2][xw+2].zwroc_kolor()==brak)
                {
                    return true;
                }
            }
        }
    }

    if(tablica_pola[yw][xw].zwroc_rodzaj()==damka) //jesli pracujemy z damka
    {
        if(aktualny_gracz==bialy)
        {
            if(help_x>=2&&help_y>=2)
            {
                while(help_x>2&&help_y>2&&tablica_pola[help_y-1][help_x-1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
                {
                    help_x--;
                    help_y--;
                }

                if(tablica_pola[help_y-1][help_x-1].zwroc_kolor()==czarny) //jesli znaleziono czarny pionek w gorze i w lewo
                {
                    if(tablica_pola[help_y-2][help_x-2].zwroc_kolor()==brak) //jesli nastepne pole jest puste
                    {
                        return true;
                    }
                }
            }

            help_x=xw;  //wyzerowanie zmiennych pomocniczych
            help_y=yw;
            if(help_x<=5&&help_y>=2)
            {
                while(help_x<5&&help_y>2&&tablica_pola[help_y-1][help_x+1].zwroc_kolor()==brak) // gora prawo -> szukamy czy znajdziemy pionek
                {
                    help_x++;
                    help_y--;
                }

                if(tablica_pola[help_y-1][help_x+1].zwroc_kolor()==czarny) //jesli znaleziono czarny pionek w gorze i w lewo
                {
                    if(tablica_pola[help_y-2][help_x+2].zwroc_kolor()==brak) //jesli nastepne pole jest puste
                    {
                        return true;
                    }
                }
            }
            help_x=xw;  //wyzerowanie zmiennych pomocniczych
            help_y=yw;
            if(help_x>=2&&help_y<=5)
            {
                while(help_x>2&&help_y<5&&tablica_pola[help_y+1][help_x-1].zwroc_kolor()==brak) // dol lewo -> szukamy czy znajdziemy pionek
                {
                    help_x--;
                    help_y++;
                }

                if(tablica_pola[help_y+1][help_x-1].zwroc_kolor()==czarny) //jesli znaleziono czarny pionek w gorze i w lewo
                {
                    if(tablica_pola[help_y+2][help_x-2].zwroc_kolor()==brak) //jesli nastepne pole jest puste
                    {
                        return true;
                    }
                }
            }
            help_x=xw;  //wyzerowanie zmiennych pomocniczych
            help_y=yw;

            if(help_x<=5&&help_y<=5)
            {
                while(help_x<5&&help_y<5&&tablica_pola[help_y+1][help_x+1].zwroc_kolor()==brak) // dol prawo -> szukamy czy znajdziemy pionek
                {
                    help_x++;
                    help_y++;
                }

                if(tablica_pola[help_y+1][help_x+1].zwroc_kolor()==czarny) //jesli znaleziono czarny pionek w gorze i w lewo
                {
                    if(tablica_pola[help_y+2][help_x+2].zwroc_kolor()==brak) //jesli nastepne pole jest puste
                    {
                        return true;
                    }
                }
            }
        }


        if(aktualny_gracz==czarny)
        {
            if(help_x>=2&&help_y>=2)
            {
                while(help_x>2&&help_y>2&&tablica_pola[help_y-1][help_x-1].zwroc_kolor()==brak) // gora lewo -> szukamy czy znajdziemy pionek
                {
                    help_x--;
                    help_y--;
                }

                if(tablica_pola[help_y-1][help_x-1].zwroc_kolor()==bialy) //jesli znaleziono bialy pionek w gorze i w lewo
                {
                    if(tablica_pola[help_y-2][help_x-2].zwroc_kolor()==brak) //jesli nastepne pole jest puste
                    {
                        return true;
                    }
                }
            }
            help_x=xw;  //wyzerowanie zmiennych pomocniczych
            help_y=yw;


            if(help_x<=5&&help_y>=2)
            {
                while(help_x<5&&help_y>2&&tablica_pola[help_y-1][help_x+1].zwroc_kolor()==brak) // gora prawo -> szukamy czy znajdziemy pionek
                {
                    help_x++;
                    help_y--;
                }

                if(tablica_pola[help_y-1][help_x+1].zwroc_kolor()==bialy) //jesli znaleziono bialy pionek w gorze i w lewo
                {
                    if(tablica_pola[help_y-2][help_x+2].zwroc_kolor()==brak) //jesli nastepne pole jest puste
                    {
                        return true;
                    }
                }
            }
            help_x=xw;  //wyzerowanie zmiennych pomocniczych
            help_y=yw;

            if(help_x>=2&&help_y<=5)
            {
                while(help_x>2&&help_y<5&&tablica_pola[help_y+1][help_x-1].zwroc_kolor()==brak) // dol lewo -> szukamy czy znajdziemy pionek
                {
                    help_x--;
                    help_y++;
                }

                if(tablica_pola[help_y+1][help_x-1].zwroc_kolor()==bialy) //jesli znaleziono bialy pionek w gorze i w lewo
                {
                    if(tablica_pola[help_y+2][help_x-2].zwroc_kolor()==brak) //jesli nastepne pole jest puste
                    {
                        return true;
                    }
                }
            }

            help_x=xw;  //wyzerowanie zmiennych pomocniczych
            help_y=yw;

            if(help_x<=5&&help_y<=5)
            {
                while(help_x<5&&help_y<5&&tablica_pola[help_y+1][help_x+1].zwroc_kolor()==brak) // dol prawo -> szukamy czy znajdziemy pionek
                {
                    help_x++;
                    help_y++;
                }

                if(tablica_pola[help_y+1][help_x+1].zwroc_kolor()==bialy) //jesli znaleziono bialy pionek w gorze i w lewo
                {
                    if(tablica_pola[help_y+2][help_x+2].zwroc_kolor()==brak) //jesli nastepne pole jest puste
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


void gra::zrob_damki()  //damki zrobie z was
{
    if(aktualny_gracz==bialy)
    {
        if(tryb_gry==bialy)
        {
            for(int j=0;j<8;j++)
            {
                if(tablica_pola[0][j].zwroc_kolor()==bialy) //jesli mamy utworzyc damke
                {
                    ilosc_damek_bialych++;
                    zrob_damke(j, 0);
                }
            }
        }
        else
        {
            for(int j=0;j<8;j++)
            {
                if(tablica_pola[7][j].zwroc_kolor()==bialy) //jesli mamy utworzyc damke
                {
                    ilosc_damek_bialych++;
                    zrob_damke(j, 7);
                }
            }
        }
    }

    if(aktualny_gracz==czarny)
    {
        if(tryb_gry==bialy)
        {
            for(int j=0;j<8;j++)
            {
                if(tablica_pola[7][j].zwroc_kolor()==czarny) //jesli mamy utworzyc damke
                {
                    ilosc_damek_czarnych++;
                    zrob_damke(j, 7);
                }
            }
        }
        else
        {
            for(int j=0;j<8;j++)
            {
                if(tablica_pola[0][j].zwroc_kolor()==czarny) //jesli mamy utworzyc damke
                    {
                        ilosc_damek_czarnych++;
                        zrob_damke(j, 0);
                    }
            }
        }
    }

}

void gra::podnies_pionek(int xw, int yw)
{
    tablica_pola[yw][xw].podnies();
}

kolory gra::wygrana()
{
    if(ilosc_bialych==0)
        return czarny;
    if(ilosc_czarnych==0)
        return bialy;
    return brak;
}


int gra::ocena()
{
    return ilosc_bialych-ilosc_czarnych+ilosc_damek_bialych-ilosc_czarnych;
}

sf::Vector2i gra::wybierz_pole(sf::RenderWindow &window, sf::Vector2i wektor)
{
    int width = window.getSize().x;  //pobieramy paramentry naszego wyboru
    int height = window.getSize().y;
    float skala=height/700;
    sf::Vector2i tab;
    tab.x=(wektor.x-30*skala)/(80*skala);
    tab.y=(wektor.y-30*skala)/(80*skala);
    return tab;
}
