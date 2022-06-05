#pragma once
#include"SDL.h"
#include"SDL_image.h"
#include"SDL_ttf.h"
#include<string>
#include<iostream>
#include<memory>



class TextureManager
{
private:
	SDL_Renderer* renderer;
	std::shared_ptr<TTF_Font>Font;
	
public:
	
	 TextureManager(SDL_Renderer* renderer,const char * font)
		//:Font(nullptr,TTF_CloseFont)
	{
		 if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { std::cout << SDL_GetError() << std::endl; }
		 if (TTF_Init() < 0) { std::cout << TTF_GetError() << std::endl; }
		this->renderer = renderer;
		Font = std::shared_ptr<TTF_Font>(TTF_OpenFont(font, 10), TTF_CloseFont);
		//Font.reset(TTF_OpenFont(font,10));
		//Font = std::make_shared<TTF_Font>(TTF_OpenFont(font,10),&TTF_CloseFont);
		//Font.reset(TTF_OpenFont(font, 10));	
		//	= TTF_OpenFont(font, 10);
	}

	inline SDL_Texture* LoadTexture(const char* path)
	{
		SDL_Surface* tmp = IMG_Load(path);
		SDL_Texture* ReturnTexture = SDL_CreateTextureFromSurface(renderer, tmp);
		SDL_FreeSurface(tmp);
		tmp = nullptr;

		return ReturnTexture;
	}

	inline void DrawTexture(SDL_Texture* texture, SDL_Rect* SrcRect, SDL_Rect* DestRect)
	{
		SDL_RenderCopy(renderer, texture, SrcRect, DestRect);
	}



	static void InitWindow(SDL_Window*& window, SDL_Renderer*& renderer, const char* title, int x, int y, int h, int w)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { std::cout << SDL_GetError(); abort(); }
		else
		{
			window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
			renderer = SDL_CreateRenderer(window, -1, 0);
			SDL_Surface* tmp;
			tmp = IMG_Load("Grafiki/Ikonka.png");
			SDL_SetWindowIcon(window, tmp);
			SDL_FreeSurface(tmp);
		}
	}

	inline SDL_Texture* LoadText( std::string lettering, Uint8 r, Uint8 g, Uint8 b, int size)
	{
		//std::cout << TTF_GetError() <<" nani?" << std::endl;
		//if (Font.get() == NULL) { std::cout << TTF_GetError() << std::endl; }
		SDL_Color color = {r,g , b,Uint8(255)};
		std::unique_ptr<SDL_Surface,decltype (&SDL_FreeSurface)> textsurface (TTF_RenderText_Blended(Font.get(), lettering.c_str(), color),(&SDL_FreeSurface));
		SDL_Texture* ReturnTexture = SDL_CreateTextureFromSurface(renderer, textsurface.get());
		
		return ReturnTexture;
	}

	inline SDL_Texture* LoadTextureText(std::string lettering, std::string path, Uint8 r, Uint8 g, Uint8 b)
	{
		SDL_Color color = { r,g,b,Uint8(255) };
		std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> tmp1(TTF_RenderText_Blended(Font.get(), lettering.c_str(), color), (&SDL_FreeSurface));
		std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>tmp2(IMG_Load(path.c_str()), SDL_FreeSurface);
		SDL_BlitSurface(tmp1.get(), NULL, tmp2.get(), NULL);
		SDL_Texture* ReturnTexture = SDL_CreateTextureFromSurface(renderer, tmp1.get());
		return ReturnTexture;

	}

	~TextureManager()
	{
		renderer = nullptr;
		Font = nullptr;
	}
};