#include "bot.h"
#include <queue>
#include <limits.h>
#include <iostream>
bot::~bot()
{
    //dtor
}


int bot::minimax(gra game, int alpha, int beta, int depth)  //gra przechowuje stan planszy, kolory -czy maksymalizujemy bialego czy czarnego
{
    int max_ocena=INT_MIN;
    int min_ocena=INT_MAX;
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
									game_2=game;  //nowe rozdanie
                                    i_temp=i;
                                    j_temp=j;

									if(j_temp+y>=0&&j_temp+y<=7&&i_temp+x>=0&&i_temp+x<=7)
                                    {
                                        udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+y, i_temp+x, moge_bic);
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
                                        ocena=minimax(game_2, alpha, beta, depth-1);
                                        if(game.zwroc_aktualny_gracz()==bialy)
                                        {
                                            max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                            alpha=std::max(alpha, ocena);
                                            if(beta<=alpha)
                                            {
                                                return max_ocena;
                                            }
                                        }
                                        if(game.zwroc_aktualny_gracz()==czarny)
                                        {
                                            min_ocena=std::min(min_ocena, ocena); //jesli gramy jako
                                            beta=std::min(beta, ocena);
                                            if(beta<=alpha)
                                            {

                                                return min_ocena;
                                            }
                                        }

                                        kontynuacja_ruchu=false;
                                    }

                                    j_temp=j_temp+y;
                                    i_temp=i_temp+x;

									if(udal_ruch&&moge_bic_2)
                                    while(game_2.bicie()&&moge_bic_2)  //dopoki zbilem, i mozna isc dalej i sie nie wracam  //gdy zbilem, i mozna isc dalej
                                    {
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
                                                    moge_bic_2=game_2.czy_mam_bicie(j_temp+l, i_temp+k);
                                                }

                                                if(!moge_bic_2&&udal_ruch) //jesli nie moge juz bic i ruch sie udal
                                                {
                                                    game_2.zrob_damki();
                                                    game_2.zmien_gracza();
                                                    ocena=minimax(game_2, alpha,  beta, depth-1);
                                                    if(game.zwroc_aktualny_gracz()==bialy)
                                                    {
                                                        max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                                        alpha=std::max(alpha, ocena);
                                                        if(beta<=alpha)
                                                        {
                                                            return max_ocena;
                                                        }
                                                    }
                                                    if(game.zwroc_aktualny_gracz()==czarny)
                                                    {
                                                        min_ocena=std::min(min_ocena, ocena); //jesli gramy jako
                                                        beta=std::min(beta, ocena);
                                                        if(beta<=alpha)
                                                        {
                                                            return min_ocena;
                                                        }
                                                    }
                                                    kontynuacja_ruchu=false;
                                                }
                                                if(moge_bic_2&&udal_ruch) //jesli jeszze moge bic i ruch sie udal
                                                {
                                                    j_temp=j_temp+l;
                                                    i_temp=i_temp+k;
                                                    kontynuacja_ruchu=true;
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
                                    if(udal_ruch&&!game_2.bicie()) //gdy nic nie zbilem w tym ruchu
                                    {
                                        kontynuacja_ruchu=false;
                                        game_2.zrob_damki();
                                        game_2.zmien_gracza();
                                        ocena=minimax(game_2, alpha, beta, depth-1);
                                         if(game.zwroc_aktualny_gracz()==bialy)
                                        {
                                            max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                            alpha=std::max(alpha, ocena);
                                            if(beta<=alpha)
                                            {
                                                return max_ocena;
                                            }
                                        }
                                        if(game.zwroc_aktualny_gracz()==czarny)
                                        {
                                            min_ocena=std::min(min_ocena, ocena); //jesli gramy jako
                                            beta=std::min(beta, ocena);
                                            if(beta<=alpha)
                                            {
                                                return min_ocena;
                                            }
                                        }

                                    }
                            }
                        }

                    }

                    if(game_2.zwroc_rodzaj(j,i)==damka)
                    {
                        moge_bic= game_2.czy_mam_bicie(j_temp, i_temp);
                        if(moge_bic==true)  //jesli pionek nadaje sie do bicia
                        {
                            for(int x=-7;x<=7;x++)     //gdzie mozemy go zbic???
                            {
                                for(int y=-7;y<=7;y++)
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
                                        ocena=minimax(game_2, alpha, beta, depth-1);
                                         if(game.zwroc_aktualny_gracz()==bialy)
                                        {
                                            max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                            alpha=std::max(alpha, ocena);
                                            if(beta<=alpha)
                                            {
                                                std::cout<<max_ocena<<std::endl;
                                                return max_ocena;
                                            }
                                        }
                                        if(game.zwroc_aktualny_gracz()==czarny)
                                        {
                                            min_ocena=std::min(min_ocena, ocena); //jesli gramy jako
                                            beta=std::min(beta, ocena);
                                            if(beta<=alpha)
                                            {
                                                std::cout<<min_ocena<<std::endl;
                                                return min_ocena;
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
                                                                            //musimy dodac udany ruch
                                        for(int k=-7;k<=7;k++)
                                        {
                                            for(int l=-7;l<=7;l++)
                                            {
                                                if(j_temp+l>=0&&j_temp+l<=7&&i_temp+k>=0&&i_temp+k<=7)
                                                    udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+l, i_temp+k, moge_bic_2);
                                                else
                                                    udal_ruch=false;
                                                if(udal_ruch)
                                                {
                                                    moge_bic_2=game_2.czy_mam_bicie(j_temp+l, i_temp+k);
                                                }

                                                if(!moge_bic_2&&udal_ruch) //jesli nie moge juz bic i ruch sie udal
                                                {
                                                    game_2.zrob_damki();
                                                    game_2.zmien_gracza();
                                                    ocena=minimax(game_2, alpha,  beta, depth-1);
                                                     if(game.zwroc_aktualny_gracz()==bialy)
                                                    {
                                                        max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                                        alpha=std::max(alpha, ocena);
                                                        if(beta<=alpha)
                                                        {
                                                            std::cout<<max_ocena<<std::endl;
                                                            return max_ocena;
                                                        }
                                                    }
                                                    if(game.zwroc_aktualny_gracz()==czarny)
                                                    {
                                                        min_ocena=std::min(min_ocena, ocena); //jesli gramy jako
                                                        beta=std::min(beta, ocena);
                                                        if(beta<=alpha)
                                                        {
                                                            std::cout<<min_ocena<<std::endl;
                                                            return min_ocena;
                                                        }
                                                    }
                                                }

                                                if(moge_bic_2&&udal_ruch) //jesli jeszze moge bic i ruch sie udal
                                                {
                                                    j_temp=j_temp+l;
                                                    i_temp=i_temp+k;
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
                                        ocena=minimax(game_2, alpha, beta, depth-1);

                                         if(game.zwroc_aktualny_gracz()==bialy)
                                        {
                                            max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                            alpha=std::max(alpha, ocena);
                                            if(beta<=alpha)
                                            {
                                                std::cout<<max_ocena<<std::endl;
                                                return max_ocena;
                                            }
                                        }
                                        if(game.zwroc_aktualny_gracz()==czarny)
                                        {
                                            min_ocena=std::min(min_ocena, ocena); //jesli gramy jako
                                            beta=std::min(beta, ocena);
                                            if(beta<=alpha)
                                            {
                                                std::cout<<min_ocena<<std::endl;
                                                return min_ocena;
                                            }
                                        }

                                    }
                                }
                        }
                    }
                }
            }
        }
        if(game.zwroc_aktualny_gracz()==bialy)
        {
            return max_ocena;
        }
        else
        {
            return min_ocena;
        }

}



std::vector<parametry_ruchu> bot::ruch(gra game, int alpha, int beta)
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


        for(int i=0;i<8;i++)  //sprawdzam wszystkie wiersze
        {
            for(int j=0;j<8;j++) //sprawdzam wszystkie kolumny
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
                            for(int x=-2;x<=2;x=x+4)     //gdzie mozemy go zbic???
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
                                        ocena=minimax(game_2, alpha, beta, depth-1);

                                        if(game.zwroc_aktualny_gracz()==bialy)
                                        {
                                            max_ocena=std::max(max_ocena, ocena);//jesli gramy jako bialy
                                        }
                                        if(game.zwroc_aktualny_gracz()==czarny)
                                        {
                                            min_ocena=std::min(min_ocena, ocena); //jesli gramy jako czarny
                                        }
                                        if(min_ocena==ocena&&game.zwroc_aktualny_gracz()==czarny) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
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

                                        if(max_ocena==ocena&&game.zwroc_aktualny_gracz()==bialy) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
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

                                        if(game.zwroc_aktualny_gracz()==bialy)
                                        {
                                            alpha=std::max(alpha, ocena);
                                            if(beta<=alpha)
                                            {
                                                return dziecko;
                                            }
                                        }

                                        if(game.zwroc_aktualny_gracz()==czarny)
                                        {
                                            beta=std::min(beta, ocena);
                                            if(beta<=alpha)
                                            {
                                                return dziecko;
                                            }
                                        }

                                    }

                                    j_temp=j_temp+y;
                                    i_temp=i_temp+x;

                                    if(udal_ruch&&moge_bic_2)
                                    while(game_2.bicie()&&moge_bic_2)  //dopoki zbilem, i mozna isc dalej i sie nie wracam
                                    {
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
                                                    moge_bic_2=game_2.czy_mam_bicie(j_temp+l, i_temp+k);
                                                }

                                                if(!moge_bic_2&&udal_ruch) //jesli nie moge juz bic i ruch sie udal
                                                {
                                                    game_2.zrob_damki();
                                                    game_2.zmien_gracza();
                                                    ocena=minimax(game_2, alpha, beta, depth-1);
                                                    if(game.zwroc_aktualny_gracz()==bialy)
                                                        max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                                    if(game.zwroc_aktualny_gracz()==czarny)
                                                        min_ocena=std::min(min_ocena, ocena); //jesli gramy jako czarny
                                                    if(min_ocena==ocena&&game.zwroc_aktualny_gracz()==czarny) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                                    {
                                                        temp.x_s=j_temp;
                                                        temp.y_s=i_temp;
                                                        temp.x_k=j_temp+l;
                                                        temp.y_k=i_temp+k;
                                                        dziecko_temp.push_back(temp); //dodaj parametry do naszego dziecka
                                                        dziecko=dziecko_temp;
                                                        kontynuacja_ruchu=false;
                                                    }
                                                    if(max_ocena==ocena&&game.zwroc_aktualny_gracz()==bialy) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                                    {
                                                        temp.x_s=j_temp;
                                                        temp.y_s=i_temp;
                                                        temp.x_k=j_temp+l;
                                                        temp.y_k=i_temp+k;
                                                        dziecko_temp.push_back(temp); //dodaj parametry do naszego dziecka
                                                        dziecko=dziecko_temp;
                                                        kontynuacja_ruchu=false;
                                                    }

                                                    if(game.zwroc_aktualny_gracz()==bialy)
                                                    {
                                                        alpha=std::max(alpha, ocena);
                                                        if(beta<=alpha)
                                                        {
                                                            std::cout<<"Maksymalna ocena:"<<max_ocena<<std::endl;
                                                            return dziecko;
                                                        }
                                                    }

                                                    if(game.zwroc_aktualny_gracz()==czarny)
                                                    {
                                                        beta=std::min(beta, ocena);
                                                        if(beta<=alpha)
                                                        {
                                                            std::cout<<"Minimalna ocena:"<<min_ocena<<std::endl;
                                                            return dziecko;
                                                        }
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
                                        ocena=minimax(game_2, alpha, beta, depth-1);

                                        if(game.zwroc_aktualny_gracz()==bialy)
                                            max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                        if(game.zwroc_aktualny_gracz()==czarny)
                                            min_ocena=std::min(min_ocena, ocena);

                                        if(min_ocena==ocena&&game.zwroc_aktualny_gracz()==czarny) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                        {
                                            temp.x_s=j_temp;
                                            temp.y_s=i_temp;
                                            temp.x_k=j_temp+y;
                                            temp.y_k=i_temp+x;
                                            dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                            dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                        }
                                        if(max_ocena==ocena&&game.zwroc_aktualny_gracz()==bialy) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                        {
                                            temp.x_s=j_temp;
                                            temp.y_s=i_temp;
                                            temp.x_k=j_temp+y;
                                            temp.y_k=i_temp+x;
                                            dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                            dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                        }

                                        if(game.zwroc_aktualny_gracz()==bialy)
                                        {
                                            alpha=std::max(alpha, ocena);
                                            if(beta<=alpha)
                                            {
                                                return dziecko;
                                            }
                                        }

                                        if(game.zwroc_aktualny_gracz()==czarny)
                                        {
                                            beta=std::min(beta, ocena);
                                            if(beta<=alpha)
                                            {
                                                return dziecko;
                                            }
                                        }
                                    }
                                }
                        }
                    }

                    if(game_2.zwroc_rodzaj(j,i)==damka)
                    {
                        moge_bic= game_2.czy_mam_bicie(j_temp, i_temp);
                        if(moge_bic==true)  //jesli pionek nadaje sie do bicia
                        {
                            for(int x=-7;x<=7;x++)     //gdzie mozemy go zbic???
                            {
                                for(int y=-7;y<=7;y++)
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
                                        ocena=minimax(game_2, alpha, beta, depth-1);
                                        if(game.zwroc_aktualny_gracz()==bialy)
                                            max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                        if(game.zwroc_aktualny_gracz()==czarny)
                                            min_ocena=std::min(min_ocena, ocena); //jesli gramy jako czarny
                                        if(min_ocena==ocena&&game.zwroc_aktualny_gracz()==czarny) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
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

                                        if(max_ocena==ocena&&game.zwroc_aktualny_gracz()==bialy) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
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

                                        if(game.zwroc_aktualny_gracz()==bialy)
                                        {
                                            alpha=std::max(alpha, ocena);
                                            if(beta<=alpha)
                                            {
                                                return dziecko;
                                            }
                                        }

                                        if(game.zwroc_aktualny_gracz()==czarny)
                                        {
                                            beta=std::min(beta, ocena);
                                            if(beta<=alpha)
                                            {
                                                return dziecko;
                                            }
                                        }

                                    }

                                    j_temp=j_temp+y;
                                    i_temp=i_temp+x;

                                    if(udal_ruch&&moge_bic_2)
                                    while(game_2.bicie()&&moge_bic_2)  //dopoki zbilem, i mozna isc dalej i sie nie wracam
                                    {
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
                                        for(int k=-7;k<=7;k++)
                                        {
                                            for(int l=-7;l<=7;l++)
                                            {
                                                if(j_temp+l>=0&&j_temp+l<=7&&i_temp+k>=0&&i_temp+k<=7)
                                                    udal_ruch=game_2.ruch(j_temp, i_temp, j_temp+l, i_temp+k, moge_bic_2);
                                                else
                                                    udal_ruch=false;
                                                if(udal_ruch)
                                                {
                                                    moge_bic_2=game_2.czy_mam_bicie(j_temp+l, i_temp+k);
                                                }

                                                if(!moge_bic_2&&udal_ruch) //jesli nie moge juz bic i ruch sie udal
                                                {
                                                    game_2.zrob_damki();
                                                    game_2.zmien_gracza();
                                                    ocena=minimax(game_2,alpha,beta, depth-1);
                                                    if(game.zwroc_aktualny_gracz()==bialy)
                                                        max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                                    if(game.zwroc_aktualny_gracz()==czarny)
                                                        min_ocena=std::min(min_ocena, ocena); //jesli gramy jako czarny
                                                    if(min_ocena==ocena&&game.zwroc_aktualny_gracz()==czarny) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                                    {
                                                        temp.x_s=j_temp;
                                                        temp.y_s=i_temp;
                                                        temp.x_k=j_temp+l;
                                                        temp.y_k=i_temp+k;
                                                        dziecko_temp.push_back(temp); //dodaj parametry do naszego dziecka
                                                        dziecko=dziecko_temp;
                                                        kontynuacja_ruchu=false;
                                                    }
                                                    if(max_ocena==ocena&&game.zwroc_aktualny_gracz()==bialy) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                                    {
                                                        temp.x_s=j_temp;
                                                        temp.y_s=i_temp;
                                                        temp.x_k=j_temp+l;
                                                        temp.y_k=i_temp+k;
                                                        dziecko_temp.push_back(temp); //dodaj parametry do naszego dziecka
                                                        dziecko=dziecko_temp;
                                                        kontynuacja_ruchu=false;
                                                    }

                                                    if(game.zwroc_aktualny_gracz()==bialy)
                                                    {
                                                        alpha=std::max(alpha, ocena);
                                                        if(beta<=alpha)
                                                        {
                                                            return dziecko;
                                                        }
                                                    }

                                                    if(game.zwroc_aktualny_gracz()==czarny)
                                                    {
                                                        beta=std::min(beta, ocena);
                                                        if(beta<=alpha)
                                                        {
                                                            return dziecko;
                                                        }
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
                                        ocena=minimax(game_2, alpha, beta, depth-1);

                                        if(game.zwroc_aktualny_gracz()==bialy)
                                            max_ocena=std::max(max_ocena, ocena);  //jesli gramy jako bialy
                                        if(game.zwroc_aktualny_gracz()==czarny)
                                            min_ocena=std::min(min_ocena, ocena);

                                        if(min_ocena==ocena&&game.zwroc_aktualny_gracz()==czarny) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                        {
                                            temp.x_s=j_temp;
                                            temp.y_s=i_temp;
                                            temp.x_k=j_temp+y;
                                            temp.y_k=i_temp+x;
                                            dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                            dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                        }
                                        if(max_ocena==ocena&&game.zwroc_aktualny_gracz()==bialy) //jesli doszlo do zamiany, to nowe dziecko -> tworzymy parametry dziecka -> dodajemy do wektrora
                                        {
                                            temp.x_s=j_temp;
                                            temp.y_s=i_temp;
                                            temp.x_k=j_temp+y;
                                            temp.y_k=i_temp+x;
                                            dziecko.clear();  //bo to zupelnie nowe dziecko na 100%
                                            dziecko.push_back(temp); //dodaj parametry do naszego dziecka
                                        }

                                        if(game.zwroc_aktualny_gracz()==bialy)
                                        {
                                            alpha=std::max(alpha, ocena);
                                            if(beta<=alpha)
                                            {
                                                return dziecko;
                                            }
                                        }

                                        if(game.zwroc_aktualny_gracz()==czarny)
                                        {
                                            beta=std::min(beta, ocena);
                                            if(beta<=alpha)
                                            {
                                                return dziecko;
                                            }
                                        }
                                    }
                                }
                        }
                    }
                }
            }
        }
        return dziecko;
}
