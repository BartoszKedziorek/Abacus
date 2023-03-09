//#include"ECS/Components.h"

#include<Windows.h>
#include"include/System.h"

#define PRG = 1;
#define TEST = 0;



std::string double_do_string(double&& number)
{
	std::string tmp = "";
	int czyn = 0;
	while (number != int(number)) { number *= 10; czyn++; }
	while (int(number) != 0) { tmp.push_back(std::move(char(int(number) % 10)+48)); number /= 10; }
	int i = 0;
	std::string result = "";
	while (i < tmp.size()) { result.push_back(std::move(tmp[tmp.size()-i-1])); i++; }
	result.insert(czyn+1,".");
	return result;
}


int main(int argc, char* argv[])
{
#ifdef TEST
	/*double_to_string_u_can_not_redo(1235);
	//double_do_string(13.4);

	//std::cout << SDLK_0 << " " << SDLK_1<<" " <<SDLK_2<< std::endl;
	std::cout <<"\\" << SDLK_SLASH << std::endl;
	std::cout << "*" << SDLK_ASTERISK << std::endl;
	std::cout << "+" << SDLK_PLUS << std::endl;
	std::cout << "-" << SDLK_MINUS << std::endl;
	std::cout << '(' <<" "<< int('(') << std::endl;
	std::cout << ')' << " " << int(')') << std::endl;
	//std::cout << "ENTER" << SDLK_RETURN << std::endl;
	/*std::cout << SDLK_KP_0 << std::endl;
	std::cout << SDLK_KP_1 << std::endl;
	std::cout << SDLK_KP_9 << std::endl;
	
	std::cout << int('1') << std::endl;
	std::cout << int('9') << std::endl;
	std::cout << int('0') << std::endl;*/
	/*
	long double tmp1, tmp2;
	while (tmp1 > 0) { tmp1++; tmp2 = tmp1; }
	std::cout << tmp2 << std::endl;
	*/

#endif


#ifdef PRG
	
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	SDL_Window* window;
	SDL_Renderer* renderer;
	TextureManager::InitWindow(window, renderer, "kalkulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 490, 300);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	TextureManager* TX_manager = new TextureManager(renderer,"undefined.medium.ttf");
	EntityManager* ENT_manager = new EntityManager;

	Entity* equal = new Entity;
	equal->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Rowna_sie.png", 240, 430, 60, 60);
	equal->addComponent<Tag>('=','x');

	Entity* plus = new Entity;
	plus->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Plus.png", 180, 250, 60, 60);
	plus->addComponent<Tag>('+','o');

	Entity* minus = new Entity;
	minus->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Minus.png", 180, 310, 60, 60);
	minus->addComponent<Tag>('-','o');

	Entity* mulit = new Entity;
	mulit->addDrawableComponent<Appearance>(TX_manager,	"Grafiki/Mnozenie.png", 180, 370, 60, 60);
	mulit->addComponent<Tag>('*','o');

	Entity* div = new Entity;
	div->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Dzielenie.png", 180, 430, 60, 60);
	div->addComponent<Tag>(':','o');

	Entity* backspace = new Entity;
	backspace->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Backspace.png", 0, 190, 60, 180);
	backspace->addComponent<Tag>('B','x');

	Entity* C = new Entity;
	C->addDrawableComponent<Appearance>(TX_manager, "Grafiki/C.png", 180, 190, 60, 120,"C",37,2,0,-70);
	C->addComponent<Tag>('C','x');

	Entity* dot = new Entity;
	dot->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Kropka.png", 120, 430, 60, 60);
	dot->addComponent<Tag>('.','k');


	Entity* power_of = new Entity;
	power_of->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Potega.png", 240, 250, 60, 60);
	power_of->addComponent<Tag>('^','o');

	Entity* root = new Entity;
	root->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Pierwiastek.png", 240, 310, 60, 60);
	root->addComponent<Tag>('q','x');

	Entity* mod = new Entity;
	mod->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Mod.png", 240, 370, 60, 60);
	mod->addComponent<Tag>('m','x');







	Entity* one = new Entity;
	one->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 0, 250, 60, 60,"1",7,2,0,0);
	one->addComponent<Tag>('1','l');

	Entity* two = new Entity;
	two->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 60, 250, 60, 60, "2",12,2,0,-15);
	two->addComponent<Tag>('2','l');

	Entity* three = new Entity;
	three->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 120, 250, 60, 60, "3", 10, 2, 0, -15);
	three->addComponent<Tag>('3','l');

	Entity* four = new Entity;
	four->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 0, 310, 60, 60, "4", 10, 2, 0, -10);
	four->addComponent<Tag>('4','l');

	Entity* five = new Entity;
	five->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 60, 310, 60, 60, "5", 10, 2, 0, -15);
	five->addComponent<Tag>('5','l');

	Entity* six = new Entity;
	six->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 120, 310, 60, 60, "6", 11, 2, 0, -15);
	six->addComponent<Tag>('6','l');

	Entity* seven = new Entity;
	seven->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 0, 370, 60, 60, "7", 11, 2, 0, -15);
	seven->addComponent<Tag>('7','l');

	Entity* eight = new Entity;
	eight->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 60, 370, 60, 60, "8", 11, 2, 0, -15);
	eight->addComponent<Tag>('8','l');

	Entity* nine = new Entity;
	nine->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 120, 370, 60, 60, "9", 11, 2, 0, -15);
	nine->addComponent<Tag>('9','l');

	Entity* zero = new Entity;
	zero->addDrawableComponent<Appearance>(TX_manager, "Grafiki/Podstawa.png", 0, 430, 60, 120, "0", 40, 3, 0, -70);
	zero->addComponent<Tag>('0','l');




	Entity* typingspace =  new Entity;
	typingspace->addDrawableComponent<Typing_space>(TX_manager, 300, 145, 50, 0);
	typingspace->addDrawableComponent<History>(6, 147, TX_manager);
	

	
	ENT_manager->AddEntity(*equal);
	ENT_manager->AddEntity(*plus);
	ENT_manager->AddEntity(*minus);
	ENT_manager->AddEntity(*mulit);
	ENT_manager->AddEntity(*div);
	ENT_manager->AddEntity(*backspace);
	ENT_manager->AddEntity(*C);
	ENT_manager->AddEntity(*typingspace);
	ENT_manager->AddEntity(*dot);
	ENT_manager->AddEntity(*power_of);
	ENT_manager->AddEntity(*root);
	ENT_manager->AddEntity(*mod);

	
	ENT_manager->AddEntity(*one);
	ENT_manager->AddEntity(*two);
	ENT_manager->AddEntity(*three);
	ENT_manager->AddEntity(*four);
	ENT_manager->AddEntity(*five);
	ENT_manager->AddEntity(*six);
	ENT_manager->AddEntity(*seven);
	ENT_manager->AddEntity(*eight);
	ENT_manager->AddEntity(*nine);
	ENT_manager->AddEntity(*zero);
	
	bool running = 1;
	while (running)
	{
		SDL_RenderClear(renderer);
	//ENT_manager->update();
		SYSTEM::Buttons_and_typingspace(*ENT_manager,typingspace,running);
		ENT_manager->draw();
		SDL_RenderPresent(renderer);
	}

	//Appearance* xp = &zero->getComponent<Appearance>();


	ENT_manager->~EntityManager();
	ENT_manager = nullptr;

	TX_manager->~TextureManager();
	TX_manager = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	
	SDL_Quit();
	TTF_Quit();

#endif
return 0;
}