#ifndef GRA_H
#define GRA_H
#include "pionek.h"




class gra :public sf::Drawable
{
    private:
        pionek tablica_pola[8][8];
        kolory tryb_gry;
        kolory aktualny_gracz;
        bool PC;
        int ilosc_czarnych;
        int ilosc_bialych;
        bool czy_bylo_bicie;
        void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
        bool pole_wolne(int xw, int yw); //sprawdza czy pole jest wolne
        bool pole_czarny(int xw, int yw); //sprawdza czy na polu jest czarny pionek
        bool pole_bialy(int xw, int yw); //sprawdza czy na polu jest bialy pionek
        void przesun_pionek(int x_s, int y_s, int x_k, int y_k);
        void usun_pionek(int x_s, int y_s);
        void zrob_damke(int x_s, int y_s);
        void odstaw_pionek(int xw, int yw);
    public:
        gra(kolory kol, bool PCt); //bialy -biale na dole
        ~gra();
        kolory zwroc_aktualny_gracz(){return aktualny_gracz;};
        void zrob_damki();
        bool wybierz_pionek(int xw, int yw);
        bool ruch(int x_s, int y_s, int x_k, int y_k, bool moge_bic);  //sprawdza czy mozliwy jest ruch na dane pole. jesli tak, to porusza pionkami
        void zmien_gracza();
        bool bicie(){return czy_bylo_bicie;};
        bool czy_mam_bicie(int xw, int yw);
        void podnies_pionek(int xw, int yw);
        kolory wygrana();
        int ocena();
        bool zwroc_PC(){return PC;};

};

#endif // GRA_H
