#pragma once
#include"ECS.h"


class TestComp:public Component
{
private:
	int x, y;
public:
	TestComp(int x, int y)
		: x(x), y(y) {};
	void update() override
	{
		x++; y++;
	}

	bool init() override
	{
		this->x = 0;
		this->y = 0;

		return 0;
	}
	
	void  showup()
	{
		std::cout << x << " " << y << std::endl;
	}

};