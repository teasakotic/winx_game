
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>
using namespace std;

class Shape{
  public:
    virtual void draw(SDL_Renderer* renderer){

    };

    virtual void move(int, int){};
};

class Line:public Shape{
  public:
    Line(int, int, int, int);
    int x1, y1, x2, y2;
    void draw(SDL_Renderer*);
    void move(int, int);
};

class Circle:public Shape{
public:
  Circle(int, int, int);
  int xc;
  int yc;
  int r;
  void draw(SDL_Renderer*);
  void move(int, int);
};

Line::Line(int aX1, int aY1, int aX2, int aY2){
  x1 = aX1;
  y1 = aY1;
  x2 = aX2;
  y2 = aY2;
}

void Line::draw(SDL_Renderer* renderer){
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Line::move(int dX, int dY){
  x1 += dX;
  x2 += dX;
  y1 += dY;
  y2 += dY;
}

class Reket:public Line{
  public:
    Reket(int x1, int y1, int x2, int y2):Line(x1, y1, x2, y2){};
    void draw(SDL_Renderer*);
};

void Reket::draw(SDL_Renderer* renderer){
  SDL_RenderDrawLine(renderer, x1, y1-1, x2, y2-1);
  SDL_RenderDrawLine(renderer, x1, y1+1, x2, y2+1);
}

Circle::Circle(int aXc, int aYc, int aR){
    xc = aXc;
    yc = aYc;
    r = aR;
}

void Circle::draw(SDL_Renderer* renderer){
  int s = 30;
  float d_a = 2*M_PI/s;
  float angle = d_a;

  float x0, y0;
  float x1, y1;
  x1 = xc+r;
  y1 = yc;
  for (int i=0; i<s; i++){
    x0 = x1;
    y0 = y1;
    x1 = xc + cos(angle) * r;
    y1 = yc + sin(angle) * r;
    angle += d_a;
    SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
  }
}

void Circle::move(int dX, int dY){
  xc += dX;
  yc += dY;
}

void drawScore(int score, int total, TTF_Font* font, SDL_Renderer* renderer){
  SDL_Color white = {255, 255, 255};
  stringstream ss;
  ss << "[" << score<<"/"<<total << "]";
  SDL_Surface* sm = TTF_RenderText_Solid(font, ss.str().c_str(), white);
  SDL_Texture* poruka = SDL_CreateTextureFromSurface(renderer, sm);
  SDL_Rect poruka_box;
  poruka_box.x = 320-sm->w/2;
  poruka_box.y = 200-2-sm->h;
  poruka_box.w = sm->w;
  poruka_box.h = sm->h;
  SDL_RenderCopy(renderer, poruka, NULL, &poruka_box);
}

