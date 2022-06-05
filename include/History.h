#pragma once
#include"ECS.h"
#include"TextureManager.h"

using charset = std::vector<char>;


class History :public Component
{
private:
	std::vector<SDL_Texture*> m_textures;
	std::vector<SDL_Rect> positions;
	std::vector<charset> charsets;
	std::vector<std::string> letterings;
	std::shared_ptr<TextureManager> m_TX;
	int m_y, m_max,amount;
	friend class Typing_space;
public:

	inline ~History()
	{
		for (auto& e : m_textures)
		{SDL_DestroyTexture(e);
		e = nullptr;}
		
		positions.erase(positions.begin(), positions.end());

		charsets.erase(charsets.begin(), charsets.end());

		letterings.erase(letterings.begin(), letterings.end());

		m_TX = nullptr;

		std::cout << "YOU Are going to Brazil" << std::endl;
	}



	inline History(int max, int y,TextureManager * newman)
		:m_y(y), m_max(max)
	{
		amount = 0;
		m_TX = std::make_shared<TextureManager>(*newman);
		m_textures.reserve(m_max);
		positions.reserve(m_max);
		/*charsets.reserve(m_max);
		letterings.reserve(m_max);*/
	}

	inline void add(std::string& lettering,std::vector<char>& vect)
	{
		amount++;
		if (amount > m_max)
		{
			positions.erase(positions.end()-1);
			m_textures.erase(m_textures.end()-1);
			letterings.erase(letterings.end() - 1);
			charsets.erase(charsets.end() - 1);
			amount--;
		}
		//positions.insert(positions.begin(),SDL_Rect{ int(300 - lettering.size() * 15),int (150-(amount*25)),int(lettering.size()*15),25});
		positions.insert(positions.begin(), SDL_Rect{ int(300 - lettering.size()*15),m_y,int(lettering.size() * 15),25});
		letterings.insert(letterings.begin(),lettering);
		charsets.insert(charsets.begin(), vect);

		for(auto&e: positions)
		{
			e.y -= 25;
		}
		m_textures.insert(m_textures.begin(),std::move(m_TX->LoadText(lettering,185,185,185,5)));
	}

	
	void update()
	{
	
		for (int i = 0; i < amount; i++)
		{
			m_TX->DrawTexture(m_textures[i], NULL, &positions[i]);
		}

	}
	
	void click(int& x, int& y,std::string&letter,std::vector<char>&charset)
	{
		short int i = (m_y - y) / 25;
		if (i<amount && i>-1)
		{
			
			if (positions[i].x <= x && x <= positions[i].x + positions[i].w)
			{
				letter = letterings[i];
				charset = charsets[i];
				return;
			}
		}

	}


	bool init()
	{
		return 1;
	}

};