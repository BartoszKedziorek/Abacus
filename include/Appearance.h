#pragma once
#include"ECS.h"
#include"TextureManager.h"

class Appearance :public Component
{
private:
	SDL_Texture* look;
	SDL_Texture* active_look;
	SDL_Texture* a_look;
	SDL_Texture* charset;
	TextureManager* TXmanager;
	SDL_Rect* DEST;
	SDL_Rect* P_DEST;
	SDL_Rect* SRC;
	int egz;
public:
	Appearance()
	{
		TXmanager = nullptr;
		DEST = new SDL_Rect;
		DEST->x = 0;
		DEST->y = 0;
		DEST->h = 0;
		DEST->w = 0;

		SRC = new SDL_Rect;
		SRC->x = 0;
		SRC->y = 0;
		SRC->h = 0;
		SRC->w = 0;

		active_look = nullptr;
		look = nullptr;
		charset = nullptr;

		a_look = look;
		egz = 0;
	}



	Appearance(TextureManager* tmp_manager,const char * path, int x, int y, int h, int w)
	{
		TXmanager = tmp_manager;
		look = TXmanager->LoadTexture(path);

		std::string tmp = path; tmp.resize(tmp.size() + 1);
		int i = 1;
		for (i; i < 5; i++)
		{
			tmp[tmp.size() - i] = tmp[tmp.size() - i - 1];
		}
		tmp[tmp.size() - i ] = 'a';
		std::cout << tmp << std::endl;

		active_look = TXmanager->LoadTexture(tmp.c_str());

		charset = nullptr;

		SRC = new SDL_Rect;
		DEST = new SDL_Rect;

		SRC->x = DEST->x = x;
		SRC->y = DEST->y = y;
		SRC->w = DEST->w = w;
		SRC->h = DEST->h = h;

		SRC->x = SRC->y = 0;
		P_DEST = nullptr;

		a_look = look;
		egz = 0;
	};

	Appearance(TextureManager* tmp_manager, const char* path, int x, int y, int h, int w,std::string letter,int x2=0,int y2=0,int h2=0,int w2=0)
	{
		TXmanager = tmp_manager;
		look = TXmanager->LoadTexture(path);
		charset = TXmanager->LoadText(letter, 0, 0, 0, 10);

		std::string tmp = path; tmp.resize(tmp.size() + 1);
		int i = 1;
		for (i; i < 5; i++)
		{
			tmp[tmp.size() - i] = tmp[tmp.size() - i - 1];
		}
		tmp[tmp.size() - i] = 'a';
		std::cout << tmp << std::endl;

		active_look = TXmanager->LoadTexture(tmp.c_str());



		SRC = new SDL_Rect;
		DEST = new SDL_Rect;
		P_DEST = new SDL_Rect;

		SRC->x = DEST->x = x;
		SRC->y = DEST->y = y;
		SRC->w = DEST->w = w;
		SRC->h = DEST->h = h;

		P_DEST->h = h+h2;
		P_DEST->w = w+w2;
		P_DEST->x = x+x2;
		P_DEST->y = y+y2;

		SRC->x = SRC->y = 0; 
		a_look = look;
		egz = 0;
	};


	bool init()override
	{
	return 0;
	}

	void update()override
	{
		show();
	}
	
	inline bool click(int&x,int&y)
	{
		if (DEST->x <= x && DEST->x + DEST->w >= x && DEST->y <= y && DEST->y + DEST->h >= y)
		{
			a_look = active_look;
			egz = 1000;
			return 1;
		}
		else
			return 0;
	}

	void state()
	{
		std::cout << "(look==NULL) = " << (look == NULL) << std::endl;
		std::cout << "(SRC==NULL) = " << (SRC == NULL) << std::endl;
		std::cout << "(DEST==NULL) = " << (DEST == NULL) << std::endl;
		std::cout << "(TXmanager==NULL)" << (TXmanager == NULL) << std::endl;
	}

	 void show()
	{
		 if (egz != 0) { a_look = active_look; egz--; }
		 else
		 {
			 a_look = look;
		 } 
		TXmanager->DrawTexture(a_look,SRC,DEST);
		TXmanager->DrawTexture(charset, SRC, P_DEST);
		
	}

	~Appearance()
	{
		static int i = 1;

		delete DEST;
		delete P_DEST;
		delete SRC;

		DEST = nullptr;
		SRC = nullptr;
		P_DEST = nullptr;

		SDL_DestroyTexture(charset);
		charset = nullptr;

		TXmanager = nullptr;
		SDL_DestroyTexture(look);
		look = nullptr;

		SDL_DestroyTexture(active_look);
		active_look = nullptr;

		a_look = nullptr;

		std::cout<<"Apperance SHINE!!!NANI? " <<i<< std::endl;
		i++;
	}


};