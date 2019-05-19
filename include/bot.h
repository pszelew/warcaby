#ifndef BOT_H
#define BOT_H
#include "gra.h"
struct parametry_ruchu
{
    int x_s;
    int y_s;
    int x_k;
    int y_k;
};

class bot
{
    private:
        int max_depth = 1;
        kolory kolor_bota;
        int minimax(gra game, int depth);
    public:
        bot(kolory kol){kolor_bota=kol;};
        virtual ~bot();
        kolory zwroc_kolor_bota(){return kolor_bota;};
        std::vector<parametry_ruchu> ruch(gra game);  //funkcja zwraca optymalny ruch, jaki wykonuje komputer. Pobiera aktualny stan gry
};






#endif // BOT_H
