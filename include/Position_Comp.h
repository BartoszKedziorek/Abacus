#pragma once
#include"ECS.h"

class Position: public Component
{
private:
	int x, y;
	int h, w;
public:
	bool init() override
	{
		x = y = w = h = 0;
		return 1;
	}

	bool init(int x, int y, int h, int w)
	{
		this->x = x;
		this->y = y;
		this->h = h;
		this->w = w;
		return 1;
	}

	Position(int x, int y, int h, int w)
		:x(x), y(y), h(h), w(w) {};

	~Position() = default;

	inline void update()override { ; }

inline void SetX(int x)
{
	this->x = x;
}

inline void SetY(int y)
{
	this->y = y;
}

inline void SetH(int h)
{
	this->h = h;
}

inline void SetW(int w)
{
	this->w = w;
}

inline void show_data() const
{
	std::cout << "(" << x<<", " << y << ") h = " << h << ", w = " << w << std::endl;
}

};