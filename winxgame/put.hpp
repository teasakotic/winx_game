#ifndef PUT_HPP_INCLUDED
#define PUT_HPP_INCLUDED
#include <vector>
#include "winx.hpp"
#include "srce.hpp"
#include "prepreka.hpp"
using namespace std;
class Put{
private:
    SDL_Rect r;
    SDL_Renderer* renderer;
    winx* winx;
    vector<Srce*> srcei;
    vector<Prepreka*> prepreke;
    int brojac;
    int vremeStvaranja;

    int brojacZaSrce;
    int vremeStvaranjaSrca;

    SDL_Texture* image;

public:

    Put(int duzina, int sirina, SDL_Renderer* re)  {
    r.x = 200;
    r.y = 0;
    r.w = sirina;
    r.h = duzina;

    renderer = re;

    winx = new Winx(250,400,30,40, r.x, r.x + r.w, IMG_LoadTexture(renderer, "slike/auto.png"));

    brojac = 0;
    vremeStvaranja = 100;

    brojacZaSrce = 0;
    vremeStvaranjaSrca = 150;

    image = IMG_LoadTexture(renderer, "slike/put.png");

    }


    void update(SDL_Event event, bool * quit, int* score) {

        brojac++;
        if (brojac > vremeStvaranja){
            stvoriPrepreku( 25, 15);
            brojac=0;
            vremeStvaranja = rand() % 300 + 100;
        }

        brojacZaSrce++;
        if(brojacZaSrce == vremeStvaranjaSrca) {
            stvoriSrce(15,15);
            brojacZaSrce = 0;
            vremeStvaranja = rand() % 500 + 100;
        }

        for (int i = 0; i < srcei.size(); i++){
            srcei[i]->update(event);
        }

        for (int i=srcei.size() -1; i>=0; i--) {
            if(srcei[i] ->pokupio(winx))  {
                *score +=1;
                srcei.erase(srcei.begin() + i);
            }
        }


        for (int i = 0; i < prepreke.size(); i++){
            prepreke[i]->update(event);
            if (prepreke[i]->sudar(winx)) {
                *quit = true;
            }
        }

        winx->update(event);
    }

    void render(SDL_Renderer * renderer) {

        SDL_RenderCopy(renderer, image, NULL, &r);

        for (int i = 0; i < srcei.size(); i++){
            srcei[i]->render(renderer);
        }
        for (int i = 0; i < prepreke.size(); i++){
            prepreke[i]->render(renderer);
        }

        winx->render(renderer);
    }

        void stvoriPrepreku( double s, double v) {

            int x = rand() % r.w + r.x;
            Prepreka * p = new PravougaonikPrepreka(x, 0, s, v, IMG_LoadTexture(renderer, "slike/rock.png"));
            prepreke.push_back(p);
        }


         void stvoriSrce( double s, double v) {

            int x = rand() % r.w + r.x;
            Srce * n = new Srce(x, 0, s, v, IMG_LoadTexture(renderer, "slike/novcic.png"));
            srcei.push_back(n);
        }
};

#endif // PUT_HPP_INCLUDED
