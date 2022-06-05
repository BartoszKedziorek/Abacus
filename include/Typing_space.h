#pragma once

#include"ECS.h"
#include<string>
#include"TextureManager.h"
#include"Stos.h"
#include<math.h>


short int op_values[7] = {1,0,0,0,0,1,2};
short int l_values[7] = {2,2,0,1,0,1,3};

class Typing_space :public Component
{
private:
	SDL_Texture* performance;
	std::string letter;
	std::vector<char> charset;
	SDL_Rect position;
	int m_x, m_y, m_w, m_h;
	std::shared_ptr<TextureManager> myTxManager = nullptr;

public:
	int p;

	inline~Typing_space()
	{
		std::cout << "SHINE KAKYOIN! BAKANA!!!!" << std::endl;
		SDL_DestroyTexture(performance);
		performance = nullptr;

		charset.erase(charset.begin(), charset.end());
		myTxManager = nullptr;

	}


	std::string& ret_let()
	{
		return letter;
	}

	std::vector<char>& ret_char()
	{
		return charset;
	}

	bool init()
	{
		return 0;
	}

	inline void Reload()
	{
		SDL_DestroyTexture(performance);
		performance = std::move(myTxManager->LoadText(letter, 0, 0, 0, 10));
	}

	long double string_to_double(string&lt)
	{
		//-48;
		int it = 0;
		long double wynik = 0;
		int k = -1;
		int multi = 1;
		if(lt[0]=='-')
			{
			it++;
			multi = -1;
			}

		while (it != lt.size())
		{
			if (lt[it] == '.') { k = it; it++; }
			else { wynik *= 10; wynik += int (lt[it] - 48);   it++; }
		}
		if (k != -1)
		{
			k = lt.size() - 1 - k;
			while (k != 0) { wynik /= 10; k--; }
		}
		return (wynik*multi);
	}

	double rounds(int m, double liczba)
	{
		int z = m;
		while (m != -1) { liczba *= 10; m--; }
		if (int(liczba) % 10 >= 5) { liczba += 10; }
		std::cout << liczba << std::endl;
		liczba /= 10;
		liczba = int(liczba);
		while (z != 0) { liczba /= 10; z--; }
		std::cout << liczba << std::endl;
		return liczba;
	}


	std::string double_to_string(double& number)
	{
		std::string tmp = "";
		bool var = (number < 0);
		int czyn = 0;
		double f = fabs(number - int(number));
		while (fabs(number-int(number))>=0.9 ) {
			double x = number;
			int y = int(number);
			number = number * 10; 
			czyn++;
		}

		if(number>=0)
			while (int(number) != 0) { tmp.push_back(std::move(char(int(number) % 10) + 48)); number /= 10; }
		else
			while (int(number) != 0) { tmp.push_back(std::move(char(int (number*-1) % 10) + 48)); number /= 10; }

		int i = 0;
		std::cout << tmp << std::endl;
		std::string result = "";
		
		while (i < tmp.size()) { std::cout << tmp[tmp.size() - 1 - i] << std::endl; result.push_back(std::move(tmp[tmp.size() - i - 1])); i++; }
		if(czyn!=0)
			result.insert(czyn + 1, ".");
		if (var)
			result.insert(0,"-");

		return result;
	}

	void reset_letter_and_charset()
	{
		letter = "";
		charset.erase(charset.begin(), charset.end());
		position.x = m_x;
		position.w = m_w;
		position.h = m_h;
		position.y = m_y;

		SDL_DestroyTexture(performance);
		performance = std::move(myTxManager->LoadText(letter, 0, 0, 0, 5));
	}


	void reset_pos()
	{
		position.x = m_x;
		position.w = m_w;
	}

	void reset_pos(int x, int w)
	{
		position.x = x;
		position.w = w;
	}

	void power_of(short int pot,long double &b)
	{
		long double wynik = b;
		if (pot <= 0)
		{
			do { wynik /= b; pot++;} while (pot != 1);
		}
		else
		{
			while (pot != 1)
			{
				wynik*= b;
				pot--;
			}
		}
		b = wynik;
	}

	void mod(int& p, int&typ, char&x)
	{
		position.x -= p;
		position.w += p;
		letter.push_back(std::move(x));
		SDL_DestroyTexture(performance);
		performance = std::move(myTxManager->LoadText(letter, 0, 0, 0, 10));
		charset.emplace_back(typ);
	}

	void modify(char x, int& p, int &&typ)
	{
		if (charset.size() != 0)
		{
			char& n = charset[charset.size() - 1];
			char& tmp = letter.back();
			switch (typ)
			{
			case'l':
				mod(p, typ, x); break;
			case'o':
			if (x != '-')
			{
				if (n == 'l' || n == 'z') { mod(p, typ, x); }
			}
			else
			{
				if (n == 'n')
				{
				int l = int('l');
				mod(p,l, x);
				}
				else if (n == 'l' || n =='z')
				{
					mod(p, typ, x);
				}
			}
					break;
			case'k':
			case'z':
				if (n == 'l'||n == 'z') { mod(p, typ, x); }break;
			case'n':
				if (n == 'o' || n=='n' || n=='x') { mod(p, typ, x); } break;
			case 'f':
				if (n == 'o' || n == 'n')
					mod(p, typ, x);
			case'x':
				if((n=='o'&& (tmp=='m')) || (n=='x' && tmp!='d') || (n=='f'))
					mod(p, typ, x);
				break;
			}
		}
			else {
				if(typ=='l' || typ=='n' || typ=='f')
					mod(p, typ, x);
				}
	}

	int ov(int x)
	{
		if (x == 'm')
		{
			return 5;
		}
		else if(x =='^')
		{
			return 6;
		}
		else { return x - 42; }
	}

	void swap(std::string& str, vector<char>& charset)
	{
		letter = str;
		this->charset = charset;
	}


	char inline letter_last()
	{
		return letter.back();
	}

	bool letter_size()
	{
		return (letter.size() > 0);
	}

	inline short int real_size()
	{
		return letter.size();
	}

	void back_space()
	{
		
		if (letter.size() != 0)
		{
			if (letter.back() == '!') { reset_letter_and_charset(); }
			else
			if (letter[letter.size() - 1] == 'd')
			{

				position.x += (p * 3);
				position.w -= (p * 3);
				for (int i = 0; i < 3; i++)
				{
					letter.pop_back();
					charset.pop_back();
				}
				SDL_DestroyTexture(performance);
				performance = std::move(myTxManager->LoadText(letter, 0, 0, 0, 5));
			}
			else
			{
				position.x += p;
				position.w -= p;
				letter.pop_back();
				charset.pop_back();
				SDL_DestroyTexture(performance);
				performance = std::move(myTxManager->LoadText(letter, 0, 0, 0, 5));
			}

		};
	}

	void return_state()
	{
		if (letter.size() != 0 && letter.back() != '!')
		{
			processing();
			SDL_DestroyTexture(performance);
			performance = myTxManager->LoadText(letter, 0, 0, 0, 10);
		}
	}

	void processing()
	{
		std::cout << charset.back();
		if(charset.back() == 'k' || charset.back() == 'o')
		{
			letter = "blad!";
			for (int i = 0; i < 5; i++)
				charset.emplace_back(std::move('x'));
			position.x = m_x - p * 5;
			position.w = p * 5;
			return;
		}

		std::string output = "";
		std::string charset_o = "";
		int it = 0;
		std::cout << letter[it] << std::endl;
		STOS<char> stack(letter.size());

		while (it < letter.size())
		{
			
			char type = charset[it];
			char sym = letter[it];
			switch (type)
			{
			case 'l':
				
					output.push_back(letter[it]);
					charset_o.push_back('l');
					it++;
					while (charset.size()>it && charset[it] == 'l')
					{
						output.push_back(letter[it]);
						charset_o.push_back('l');
						it++;
					}
					if (charset.size() > it && charset[it] != 'k')
					{
						output.push_back(' ');
						charset_o.push_back('s');
					}
					
				it--;
				break;
			case 'k':
				output.push_back(letter[it]);
				charset_o.push_back('k');
				break;
			case 'o':
			
					while ( ((l_values[ov(sym)]<=2 && (op_values[ov(sym)] <= op_values[ov(stack.get())])) || (l_values[ov(sym)]>=2 && (op_values[ov(sym)] < op_values[ov(stack.get())]))) && stack.CZY_PELNY()!=STOS_PUSTY  && stack.get()!='(' && stack.get()!='q')
					{
						char tmp;
						stack.pop(tmp);
						output.push_back(tmp);
						charset_o.push_back('o');
					}
				
				stack.push(sym); break;
			case 'n':
				stack.push(std::move('('));break;
			case'z':
				char sym2;
				stack.pop(sym2);
				while (sym2 != '(')
				{
					output.push_back(sym2);
					charset_o.push_back('o');
					if (stack.pop(sym2) == STOS_PUSTY) {
						letter = "blad!";
						position.x = m_x - p * 5;
						position.w = p * 5;
						return;
					}
				}break;
			case 'f':
				stack.push('q');
				break;
			}
			it++;
		}
		
		while (stack.CZY_PELNY() != STOS_PUSTY)
		{
			char tmp;
			stack.pop(tmp);
			if (tmp == '(' || tmp == ')')
			{
				it = output.size();
				letter = "blad!";
				position.x = m_x - p * 5;
				position.w = p * 5;
				return;
			}
			output.push_back(tmp);
			if (tmp != 'q')
			{
				charset_o.push_back('o');
			}
			else { charset_o.push_back('f'); }
		}/*
		std::cout << letter << std::endl;
		std::cout << output << std::endl;
		std::cout << charset_o << std::endl;
		std::cout << std::endl;*/
		//std::cout << output << std::endl;
		
		int indeks = 0;
		STOS<long double> numbers(100);
		std::string tmp = "";
		while (indeks < output.size())
		{
			switch (charset_o[indeks])
			{
				case 'l':
					
					tmp.push_back(output[indeks]);
					indeks++;
					while (charset_o[indeks]=='l' || charset_o[indeks]=='k')
					{
						tmp.push_back(output[indeks]);
						indeks++;
					}
					numbers.push(std::move(string_to_double(tmp)));
					tmp = "";
					break;
				case 'o':
					long double a, b;
					numbers.pop(a);
					numbers.pop(b);
					switch (output[indeks])
					{
					case '+':
						numbers.push(std::move(b + a));
						break;
					case '-':
						numbers.push(std::move(b - a));
						break;
					case '*':
						numbers.push(std::move(b * a));
						break;
					case ':':
						if (a == 0)
						{
							it = output.size();
							letter = "blad!";
							for (int i = 0; i < 5; i++)
								charset.emplace_back(std::move('x'));
							position.x = m_x - p * 5;
							position.w = p * 5;
							return;
						}
						numbers.push(std::move(b / a));
						break;
					case '^':
						power_of(a, b);
						numbers.push(std::move(b));
						break;
					case 'm':
							if (int(a) == a && int(b) == b && a!=0)
							{
								//std::cout << int(b) % int(a)<<std::endl
								if (a > 0)
								{
									if (b >= 0)
									{
										numbers.push(std::move(int(b) % int(a)));
									}
									else
									{
										std::cout << "to" << std::endl;
										numbers.push(std::move(int(a) + (int(b)%int(a))));
									}

								}
								else 
								{
									if (b >= 0)
									{
										numbers.push(int(b) % int(a));
									}
									else
									{
										numbers.push(-int(a)+int(b) % int(a));
									}
					
								}
							}
							else
							{
								it = output.size();
								letter = "blad!";
								for (int i = 0; i < 5; i++)
									charset.emplace_back(std::move('x'));
								position.x = m_x - p * 5;
								position.w = p * 5;
								return;
							}
							/// <summary>
							/// //SPÓJRZ DO GRY.CPP to ci oszczêdzi pracy buraku
							/// </summary>
							break;
					}
					indeks++;
					break;
				case 'f':
					
					long double c;
					numbers.pop(c);
					if (c >= 0)
					{
						c = sqrt(c);
						numbers.push(std::move(c));
					}
					else
					{
						letter = "blad!";
						for (int i = 0; i < 5; i++)
							charset.emplace_back(std::move('x'));
						position.x = m_x - p * 5;
						position.w = p * 5;
						return;
					}
					indeks++;
					break;
				case's':
					indeks++; break;

			}
		}
		long double wynik = 0;
		numbers.pop(wynik);
		//tutaj spojrzyj czy trzeba to przestawiæ czy nie trzeba aby historia dostawa³a prawid³owe charsety i stringi
		owner->getComponent<History>().add(letter,charset);
	
		if (wynik != (long int)wynik)
		{
			letter = to_string(wynik);
			while (letter.back() == '0') { letter.pop_back(); }
			}
		else {
			letter = to_string(long int(wynik));
			}

		if (wynik > 0)
		{
			if (letter.size() > 23)
			{
			
			letter = "poza zakresem!";
			charset.erase(charset.begin(), charset.end());
			for (int i = 0; i < 14; i++)
				charset.emplace_back(std::move('x'));
			position.x = m_x - p * 14;
			position.w = p * 14;

			return;
			}
		}
		else if(letter.size()>24)
		{
			letter = "poza zakresem!";
			charset.erase(charset.begin(), charset.end());
			for (int i = 0; i < 14; i++)
				charset.emplace_back(std::move('x'));
			position.x = m_x - p * 14;
			position.w = p * 14;

			return;
		}

		if (letter[letter.size() - 1] == '.')
		{
			/*letter = "poza zakresem!";
				charset.erase(charset.begin(),charset.end());
				for (int i = 0; i < 14; i++)
					charset.emplace_back(std::move('x'));
				position.x = m_x - p * 14;
				position.w = p * 14;*/
			letter.pop_back();
			charset.pop_back();
			position.x += p;
			position.w -= p;
		}


		charset.erase(charset.begin(), charset.end());

		
		for (int i = 0; i < letter.size(); i++)
			{
			charset.emplace_back('l');
			}

		if (wynik < 0)
			{
				letter.insert(0, "("); letter.push_back(')');
				charset.insert(charset.begin(), 'n'); charset.push_back('z');
			}

		reset_pos(std::move(m_x - letter.size() * p), std::move(letter.size()* p));
		/*SDL_DestroyTexture(performance);
		performance = std::move(myTxManager->LoadText("undefined.medium.ttf", letter, 0, 0, 0, 10));*/

	}

	inline void update()
	{
		;
	}

	void redo()
	{
		if (letter.size() >= 10)
		{
			p = 15; position.h = 25;
			position.w = letter.size() * p;
			position.x = m_x - letter.size() * p;
			position.y = m_y + position.h;
		}
		else { p = 30; position.h = 50; position.y = m_y; position.x = m_x - letter.size() * p; position.w = letter.size() * p; }
	}

	inline void updateX(SDL_Event* ev)
	{

		SDL_PumpEvents();
		
			
			const Uint8* mk_State = SDL_GetKeyboardState(NULL);
			
				
				if (mk_State[SDL_SCANCODE_RSHIFT] || mk_State[SDL_SCANCODE_LSHIFT])
				{
					

					
						
						if (letter.size() != 0 && letter.back() == '!')
						{
							letter = "";
							charset.erase(charset.begin(), charset.end());
							position.w = m_w;
							position.x = m_x;
						}


						int& key = ev->key.keysym.sym;
						switch (key)
						{
						case SDLK_EQUALS:
							modify('+', p, 'o'); break;
						case SDLK_8:
							modify('*', p, 'o'); break;
						case SDLK_SEMICOLON:
							modify(':', p, 'o'); break;
						case SDLK_9:
							modify('(', p, 'n'); break;
						case SDLK_0:
							modify(')', p, 'z'); break;
						case SDLK_6:
							modify('^', p, 'o'); break;
						case SDLK_5:
							modify('m', p, 'o');
							modify('o', p, 'x');
							modify('d', p, 'x');
							break;
						}
					
				}
				else
				{

					
						
						if (letter.size()!= 0 && letter.back() == '!')
						{
							letter = "";
							charset.erase(charset.begin(), charset.end());
							position.w = m_w;
							position.x = m_x;
						}
						
						int& key = ev->key.keysym.sym;
						if ((key > 47 && key < 58) || (key > 1073741912 && key < 1073741922)) {  modify(char(key % 1073741864), p, 'l'); }
						else
						{
							switch (key)
							{
							case SDLK_KP_PLUS:
								modify('+', p, 'o'); break;
							case SDLK_MINUS:
							case SDLK_KP_MINUS:
								modify('-', p, 'o'); break;
							case SDLK_KP_0:
								modify('0', p, 'l'); break;
							case SDLK_BACKSPACE:
								back_space();
								break;
							case SDLK_KP_MULTIPLY:
								modify('*', p, 'o'); break;
							case SDLK_SLASH:
							case SDLK_KP_DIVIDE:
								modify(':', p, 'o'); break;
							case SDLK_COMMA:
							case SDLK_PERIOD:
								modify('.', p, 'k'); break;
							case SDLK_EQUALS:
							case SDLK_RETURN:
								return_state();
								break;
							}

						}
					


				}
			 if (ev->type == SDL_MOUSEBUTTONDOWN)
				{
					int i = (ev->motion.y - m_y) / 25;
					History tmp = owner->getComponent<History>();
					if (i < tmp.amount && i>0)
					{
						if (ev->motion.x >= tmp.positions[i].x && ev->motion.x <= tmp.positions[i].x + tmp.positions[i].w)
						{
							letter = tmp.letterings[i];
							charset = tmp.charsets[i];
							position.x = m_x - letter.size() * p;
							position.w = letter.size() * p;
							SDL_DestroyTexture(performance);
							performance = std::move(myTxManager->LoadText( letter, 0, 0, 0, 5));
						}

					}

				}

			
	}



	void show()
	{
		myTxManager->DrawTexture(performance, NULL, &position);
	}


	Typing_space(TextureManager* newManager, int x, int y, int h, int w)
	{
		myTxManager = std::make_shared<TextureManager>(*newManager);
		m_x = position.x = x;
		m_y = position.y = y;
		m_h = position.h = h;
		m_w = position.w = w;
		p = 30;
		letter = "";
	}


	

};