#pragma once

#include"Components.h"

namespace SYSTEM {

	void Buttons_and_typingspace(EntityManager&Et_Manager,Entity*Typing_Space,bool &running)
	{
		
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{

			
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				bool war = 0;
				for(auto&e : Et_Manager.entities)
					if(e->hasComponent<Appearance>())
						if (e->getComponent<Appearance>().click(ev.motion.x, ev.motion.y))
						{
							war = 1;
							if (e->getComponent<Tag>().ret_type() != 'x')
							{
								if (Typing_Space->getComponent<Typing_space>().letter_size() && Typing_Space->getComponent<Typing_space>().letter_last() == '!') { Typing_Space->getComponent<Typing_space>().reset_letter_and_charset();}
									Typing_Space->getComponent<Typing_space>().modify(e->getComponent<Tag>().ret_char(), Typing_Space->getComponent<Typing_space>().p, e->getComponent<Tag>().ret_type());
							}
	
							else
							{
								if (Typing_Space->getComponent<Typing_space>().letter_size() && Typing_Space->getComponent<Typing_space>().letter_last() == '!') { Typing_Space->getComponent<Typing_space>().reset_letter_and_charset(); }
								switch (e->getComponent<Tag>().ret_char())
								{
								case 'C':
									Typing_Space->getComponent<Typing_space>().reset_letter_and_charset();
									break;
								case 'B':
									Typing_Space->getComponent<Typing_space>().back_space();
									break;
								case '=':
									Typing_Space->getComponent<Typing_space>().return_state();
									break;
								case 'm':
										Typing_Space->getComponent<Typing_space>().modify('m', Typing_Space->getComponent<Typing_space>().p, 'o');
										Typing_Space->getComponent<Typing_space>().modify('o', Typing_Space->getComponent<Typing_space>().p, 'x');
										Typing_Space->getComponent<Typing_space>().modify('d', Typing_Space->getComponent<Typing_space>().p, 'x');
									
									break;
								case 'q':
									
										Typing_Space->getComponent<Typing_space>().modify('s', Typing_Space->getComponent<Typing_space>().p, 'f');
										Typing_Space->getComponent<Typing_space>().modify('q', Typing_Space->getComponent<Typing_space>().p, 'x');
										Typing_Space->getComponent<Typing_space>().modify('r', Typing_Space->getComponent<Typing_space>().p, 'x');
										Typing_Space->getComponent<Typing_space>().modify('t', Typing_Space->getComponent<Typing_space>().p, 'x');
										if(Typing_Space->getComponent<Typing_space>().letter_last()=='t')
											Typing_Space->getComponent<Typing_space>().modify('(', Typing_Space->getComponent<Typing_space>().p, 'n');

									
									break;
								}

							}


							//Typing_Space->getComponent<Typing_space>().modify(e->getComponent<Tag>().ret_char(), Typing_Space->getComponent<Typing_space>().p, 'o');
						}
				if (war == 0)
					{
					Typing_Space->getComponent<History>().click(ev.motion.x, ev.motion.y, Typing_Space->getComponent<Typing_space>().ret_let(), Typing_Space->getComponent<Typing_space>().ret_char());
					Typing_Space->getComponent<Typing_space>().Reload();
					}
			}
			else if(ev.type == SDL_KEYDOWN)
			{  Typing_Space->getComponent<Typing_space>().updateX(&ev); }
			else if (ev.type == SDL_QUIT) { running = 0; }

			Typing_Space->getComponent<Typing_space>().redo();
		}

		Typing_Space->getComponent<History>().update();
		Typing_Space->getComponent<Typing_space>().show();

	}

	void sett_tags_app(EntityManager& Et_Manager)
	{
		for(auto&e : Et_Manager.entities)
			if (e->hasComponent<Appearance>())
			{


			}

	}

}
