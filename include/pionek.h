#ifndef PIONEK.H //hfgh
#define PIONEK.H //ghh
#include <SFML/Graphics.hpp>
enum kolory
{
    bialy = 'b',
    czarny = 'c',
    brak= 'n'
};

enum rodzaj
{
    damka = 'd',
    zwykly = 'z'
};

class pionek :public sf::Drawable
{
    private:
        sf::Texture tekstura;
        sf::Sprite sprite;
        kolory kolor; //kolor pionka
        rodzaj rodz;
        int x; //wspolrzedna x
        int y; //wspolrzedna y
        void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    public:
        pionek();
        pionek(kolory kol, int xw, int yw);
        rodzaj zwroc_rodzaj() const {return rodz;};
        void ustaw_rodzaj(rodzaj rod);
        int x_zw()const {return x;};
        int y_zw()const {return y;} ;
        void xy_set(int xw, int yw);
        void kolor_set(kolory kol);
        kolory zwroc_kolor()const {return kolor;} ;
        void show(kolory kol, rodzaj rod);
        void hide();
        void podnies();
        void upusc();
};



#endif // PIONEK
