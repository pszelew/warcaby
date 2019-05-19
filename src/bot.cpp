#include "bot.h"
#include <queue>
#include <limits.h>
bot::bot()
{
    //ctor
}

bot::~bot()
{
    //dtor
}


int bot::minimax(gra game, int depth)  //gra przechowuje stan planszy, kolory -czy maksymalizujemy bialego czy czarnego
{
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
                if(game_2.wybierz_pionek(j, i))
                {
                    i_temp=i;
                    j_temp=j;
                    //tym pionkiem mozemy wykonac jakis ruch, teraz wystarczy sie dowiedziec jaki
                    for(int x=0;x<8;x++)
                    {                      //sprawdzamy wszystkie mozliwosci gdzie taki pionek moze trafic
                        for(int y=0;y<8;y++)
                        {
                            if(!kontynuacja_ruchu)
                            {
                                game_2=game;
                            }
                            moge_bic=game_2.czy_mam_bicie(j_temp, i_temp);
                            udal_ruch=game_2.ruch(j_temp, i_temp, y, x, moge_bic);
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
            }
        }
        return max_ocena;
    }

    if(game_2.zwroc_aktualny_gracz()==czarny) //jesli aktualmym graczem jest bialy
    {
        min_ocena=INT_MAX;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(game_2.wybierz_pionek(j, i))
                {
                    i_temp=i;
                    j_temp=j;
                    //tym pionkiem mozemy wykonac jakis ruch, teraz wystarczy sie dowiedziec jaki
                    for(int x=0;x<8;x++)
                    {                      //sprawdzamy wszystkie mozliwosci gdzie taki pionek moze trafic
                        for(int y=0;y<8;y++)
                        {
                            if(!kontynuacja_ruchu)
                            {
                                game_2=game;
                            }
                            moge_bic=game_2.czy_mam_bicie(j_temp, i_temp);
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
                if(game_2.wybierz_pionek(j, i))
                {
                    i_temp=i;
                    j_temp=j;
                    //tym pionkiem mozemy wykonac jakis ruch, teraz wystarczy sie dowiedziec jaki
                    for(int x=0;x<8;x++)
                    {                      //sprawdzamy wszystkie mozliwosci gdzie taki pionek moze trafic
                        for(int y=0;y<8;y++)
                        {
                            if(!kontynuacja_ruchu)
                            {
                                game_2=game;
                            }
                            moge_bic=game_2.czy_mam_bicie(j_temp, i_temp);
                            udal_ruch=game_2.ruch(j_temp, i_temp, y, x, moge_bic);
                            moge_bic_2=game_2.czy_mam_bicie(x, y);
                            if(udal_ruch&&!game_2.bicie()) //gdy nic nie zbilem w tym ruchu
                            {
                                kontynuacja_ruchu=false;
                                game_2.zrob_damki();
                                game_2.zmien_gracza();
                                ocena=minimax(game_2, depth-1);
                                max_ocena=std::max(max_ocena, ocena);
                                if(max_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                {
                                    temp.x_s=j_temp;
                                    temp.y_s=i_temp;
                                    temp.x_k=y;
                                    temp.y_k=x;
                                    dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                    dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                }
                            }

                            if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                            {
                                game_2.zrob_damki();
                                game_2.zmien_gracza();
                                ocena=minimax(game_2, depth-1);
                                max_ocena=std::max(max_ocena, ocena);
                                if(max_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                {
                                    temp.x_s=j_temp;
                                    temp.y_s=i_temp;
                                    temp.x_k=y;
                                    temp.y_k=x;
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
                                temp.x_k=y;
                                temp.y_k=x;
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
        return dziecko;
    }

    if(game_2.zwroc_aktualny_gracz()==czarny) //jesli aktualmym graczem jest czarny
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(game_2.wybierz_pionek(j, i))
                {
                    i_temp=i;
                    j_temp=j;
                    //tym pionkiem mozemy wykonac jakis ruch, teraz wystarczy sie dowiedziec jaki
                    for(int x=0;x<8;x++)
                    {                      //sprawdzamy wszystkie mozliwosci gdzie taki pionek moze trafic
                        for(int y=0;y<8;y++)
                        {
                            if(!kontynuacja_ruchu)
                            {
                                game_2=game;
                            }
                            moge_bic=game_2.czy_mam_bicie(j_temp, i_temp);
                            udal_ruch=game_2.ruch(j_temp, i_temp, y, x, moge_bic);
                            moge_bic_2=game_2.czy_mam_bicie(x, y);
                            if(udal_ruch&&!game_2.bicie()) //gdy nic nie zbilem w tym ruchu
                            {
                                kontynuacja_ruchu=false;
                                game_2.zrob_damki();
                                game_2.zmien_gracza();
                                ocena=minimax(game_2, depth-1);
                                min_ocena=std::min(min_ocena, ocena);
                                if(min_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                {
                                    temp.x_s=j_temp;
                                    temp.y_s=i_temp;
                                    temp.x_k=y;
                                    temp.y_k=x;
                                    dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                    dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                }
                            }

                            if(udal_ruch&&game_2.bicie()&&!moge_bic_2)  //gdy zbilem, ale nie mozna juz bic dalej
                            {
                                game_2.zrob_damki();
                                game_2.zmien_gracza();
                                ocena=minimax(game_2, depth-1);
                                min_ocena=std::min(min_ocena, ocena);
                                if(min_ocena==ocena) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                {
                                    temp.x_s=j_temp;
                                    temp.y_s=i_temp;
                                    temp.x_k=y;
                                    temp.y_k=x;
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
                                temp.x_k=y;
                                temp.y_k=x;
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
        return dziecko;
    }
}
