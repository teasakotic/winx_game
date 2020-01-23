#ifndef PREPREKA_HPP_INCLUDED
#define PREPREKA_HPP_INCLUDED

class Prepreka{
protected:
    SDL_Rect r;
    SDL_Texture* image;
public:

    virtual void update(SDL_Event event) = 0;
    virtual void render(SDL_Renderer * renderer) = 0;

    virtual bool sudar(const winx* winx) {

        SDL_Rect r1 = winx->getRect();
        return SDL_HasIntersection(&r1, &r);


    }

};


class PravougaonikPrepreka : public Prepreka {
private:

public:
    PravougaonikPrepreka(double xx, double yy, double ss, double vv, SDL_Texture* texture) {

        r.x = xx;
        r.y = yy;
        r.w = ss;
        r.h = vv;
        image = texture;
    }

    void update(SDL_Event event) {
        r.y += 1;
    }


    void render(SDL_Renderer * renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderCopy(renderer, image, NULL, &r);
    }
};
#endif // PREPREKA_HPP_INCLUDED
