#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "mapa.hpp"
#include "score.hpp"
#include <sstream>
#include <SDL2/SDL_image.h>
#include <SDL2/sdl.h>


using namespace std;

class Game
{

private:
    SDL_Window* window;
    SDL_Renderer * renderer;
    SDL_Event event;
    TTF_Font* font;

    bool quit;

    Mapa* mapa;
    int score;
public:

    Game()
    {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("W I N X   G A M E",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        int ret = TTF_Init();
        font = TTF_OpenFont("lazy.ttf", 24);

        mapa = new Mapa(renderer);
        score = 0;

        quit = false;
    }
    void startGame()
    {

        while (!quit)
        {

            SDL_Delay(10);
            SDL_PollEvent(&event);
            update(event);
            render();
        }
    }

    void update(SDL_Event event)
    {


        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN: //SDL_KEYUP:
            switch( event.key.keysym.sym )
            {
            case SDLK_ESCAPE:
                quit = true;
                break;

            }
        }

        mapa->update(event, &quit, &score);

    }
    void render(){


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawScore(score, font, renderer);
        mapa->render(renderer);


        SDL_Texture* img = IMG_LoadTexture(renderer, "auto.png");
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = 200;
        r.h = 200;

        SDL_RenderCopy(renderer, img, NULL, &r);

        SDL_RenderPresent(renderer);
    }

    void drawScore(int score, TTF_Font* font, SDL_Renderer* renderer){
        SDL_Color white = {255, 255, 255};
        stringstream ss;
        ss << "Score: " << score;

        SDL_Surface* sm = TTF_RenderText_Solid(font, ss.str().c_str(), white);
        SDL_Texture* poruka = SDL_CreateTextureFromSurface(renderer, sm);

        SDL_Rect poruka_box;
        poruka_box.x = 70;
        poruka_box.y = 200;
        poruka_box.w = sm->w;
        poruka_box.h = sm->h;
        SDL_RenderCopy(renderer, poruka, NULL, &poruka_box);
    }

    ~Game()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }

};

#endif // GAME_HPP_INCLUDED
