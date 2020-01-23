#ifndef SRCE_HPP_INCLUDED
#define SRCE_HPP_INCLUDED
class Srce{
private:
    SDL_Rect r;
    SDL_Texture* image;
public:
    Srce(double xx, double yy, double ss, double vv, SDL_Texture* texture)  {

        r.x = xx;
        r.y = yy;
        r.w = ss;
        r.h = vv;
        image = texture;

    }

    void update(SDL_Event event) {
        r.y += 1;
    }
    virtual bool pokupio(const winx* winx) {

        SDL_Rect r1 = winx->getRect();
        return SDL_HasIntersection(&r1, &r);


    }


    void render(SDL_Renderer * renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderCopy(renderer, image, NULL, &r);

    }

};


#endif // SRCE_HPP_INCLUDED
