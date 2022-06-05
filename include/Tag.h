#pragma once
#include"ECS.h"

class Tag :public Component
{
private:
	char character;
	char type;
public:
	Tag()
	{
		character = 'E';
		type = 'E';
		///E - empty...
	}

	Tag(char a, char b)
	{
		character = a;
		type = b;
	}

	void draw()
	{

	}

	bool init()
	{
		return 0;
	}

	char ret_char()
	{
		return character;
	}

	inline char ret_type()
	{
		return type;
	}

	void update()
	{
		;
	}

	~Tag() = default;

};