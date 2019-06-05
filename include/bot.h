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
        int max_depth = 2;
        kolory kolor_bota;
        int minimax(gra game, int alpha, int beta, int depth);
    public:
        bot(kolory kol){kolor_bota=kol;};
        virtual ~bot();
        kolory zwroc_kolor_bota(){return kolor_bota;};
        void set_kolor_bota(kolory kol){kolor_bota=kol;};
        void set_depth(int dep){max_depth=dep;};
        std::vector<parametry_ruchu> ruch(gra game, int alpha, int beta);  //funkcja zwraca optymalny ruch, jaki wykonuje komputer. Pobiera aktualny stan gry
};






#endif // BOT_H
