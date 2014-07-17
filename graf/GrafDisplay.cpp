#include "GrafDisplay.h"


CGrafDisplay::CGrafDisplay(void)
{
	sEvent = new SDL_Event;
	quit = false;
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init eror\n";
		quit = true;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout <<"SDL_Init eror\n";
		quit = true;
	}
	win = SDL_CreateWindow("Graf", 200, 50, 800, 800, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	container = nullptr;
	container = IMG_LoadTexture(ren, "data/box.gif");
	text[0] = RenderText("0", "data/SourceSansPro-Regular.ttf", 80, ren);
	text[1] = RenderText("1", "data/SourceSansPro-Regular.ttf", 80, ren);
	text[2] = RenderText("2", "data/SourceSansPro-Regular.ttf", 80, ren);
	text[3] = RenderText("3", "data/SourceSansPro-Regular.ttf", 80, ren);
	text[4] = RenderText("4", "data/SourceSansPro-Regular.ttf", 80, ren);
	text[5] = RenderText("5", "data/SourceSansPro-Regular.ttf", 80, ren);
	text[6] = RenderText("6", "data/SourceSansPro-Regular.ttf", 80, ren);
	text[7] = RenderText("7", "data/SourceSansPro-Regular.ttf", 80, ren);
	text[8] = RenderText("8", "data/SourceSansPro-Regular.ttf", 80, ren);
	text[9] = RenderText("9", "data/SourceSansPro-Regular.ttf", 80, ren);

	if (container == nullptr)
	{
		quit = true;
		std::cout << "Load box eror\n";
	}
}

void CGrafDisplay::ApplySurface(int x, int y, int imW, int imH, SDL_Texture* tex, SDL_Renderer* ren, int image, bool isText)
{
	int w, h;
	SDL_Rect pos, clip;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	pos.x = x;
	pos.y = y;
	if (!isText)
	{
		pos.w = imW;
		pos.h = imH;
	}
	clip.h = h;
	clip.w = w / 3;
	clip.x = image * w / 3;
	clip.y = 0;

	if (isText)
		SDL_RenderCopy(ren, tex, NULL, &pos);
	else
		SDL_RenderCopy(ren, tex, &clip, &pos);

}

void CGrafDisplay::Draw()
{
	while (!quit && sEvent -> type != SDL_QUIT)
	{
		SDL_PollEvent(sEvent);
		if (sEvent -> type == SDL_QUIT)
			quit = true;
		SDL_RenderClear(ren);
		ApplySurface(0, 0, 2000, 2000, container, ren, 2); //fon
		Marking();
		ApplyGraf(graf, N);

		SDL_RenderPresent(ren);
	}
}

SDL_Texture* CGrafDisplay::RenderText(std::string mes, std::string fontName, int size, SDL_Renderer* ren)
{
	TTF_Font* font = nullptr;
	font = TTF_OpenFont(fontName.c_str(), size);
	if (font == nullptr)
	{
		quit = true;
		std::cout << "TTF_Font eror\n";
	}
	SDL_Color color = {0, 0, 0};
	SDL_Surface* surf = TTF_RenderText_Blended(font, mes.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return tex;

}

CGrafDisplay::~CGrafDisplay(void)
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_DestroyTexture(container);
	for (int i(0); i < 10; i++)
		SDL_DestroyTexture(text[i]);
}

void CGrafDisplay::setGraf(int** g, int n)
{
	graf = g;
	N = n;
}

void CGrafDisplay::ApplyGraf(int **g, int n)
{
	for (int i(0); i < n; i++)
		for (int j(0); j < n; j++)
		{
			if (g[i][j] == 1)
				ApplySurface(i * 100 + 100, j * 100 + 100, 100, 100, container, ren, 0);
			else
				ApplySurface(i * 100 + 100, j * 100 + 100, 100, 100, container, ren, 1);
		}
}

void CGrafDisplay::Marking()
{
	for (int i(0); i < 8; i++)
		ApplySurface(100 * i + 100, 0, 0, 0, text[i], ren, 0, true);
	for (int i(0); i < 8; i++)
		ApplySurface(0, 100 * i + 100, 0, 0, text[i], ren, 0, true);
}
