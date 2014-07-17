#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#undef main
class CGrafDisplay
{
public:
	CGrafDisplay(void);
	~CGrafDisplay(void);
	void setGraf(int** g, int n);
	void Draw();
private:
	void ApplyGraf(int **g, int n);
	void Marking();
	void ApplySurface(int x, int y, int w, int h, SDL_Texture* tex, SDL_Renderer* ren, int image = 0, bool isText = false);
	SDL_Texture* RenderText(std::string mes, std::string fontName, int size, SDL_Renderer* ren);

	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Event* sEvent;
	SDL_Texture* container;
	SDL_Texture* text[10];
	SDL_Texture* fon;
	bool quit;
	int **graf;
	int N;
};

