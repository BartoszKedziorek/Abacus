#pragma once
#include<array>
#include<vector>
#include<memory>
#include<algorithm>
#include<iostream>
#include<bitset>


class Component;
class Entity;



using ComponentID = std::size_t;

inline ComponentID GetComponentID()
{
	static int LastID = 0;
	return LastID++;
}

template <typename T>
inline ComponentID GetComponentID()
{
	static ComponentID ReturnID = GetComponentID();
	return ReturnID;
}

constexpr ComponentID MAX_COMPONENT_ID = 32;
using ComponentBitSet = std::bitset<MAX_COMPONENT_ID>;


//klasa abstrakcyjna
class Component
{
protected:
	Entity* owner = nullptr;
public:
	virtual void update() = 0;
	virtual bool init() = 0;
	virtual ~Component() { ; }
	
	friend Entity;
};

using ComponentArray = std::array<Component*, MAX_COMPONENT_ID>;
using ComponentVector = std::vector<Component*>;


class Appearance;


class Entity
{
private:
	bool isActive = 1;
	ComponentArray Acomponents;
	ComponentVector Vcomponents;
	ComponentVector DrawableComps;
public:
	ComponentBitSet CComponents;

	Entity()
	{
		Vcomponents.reserve(MAX_COMPONENT_ID+1);
	}

	~Entity()
	{
		
		/*
		for (auto& v : Vcomponents)
		{
			delete &v;
			v = nullptr;
		}*/
		//isActive = 0;
	
		for (auto& v : Vcomponents)
			delete v;
		Vcomponents.erase(Vcomponents.begin(), Vcomponents.end());
	//	Vcomponents.clear();
		DrawableComps.erase(DrawableComps.begin(), DrawableComps.end());

		for (auto& a : Acomponents)
			a = nullptr;

		for (auto& d : DrawableComps)
			d = nullptr;
		
	}

	template<typename T, typename...TArgs>
	inline void addComponent(TArgs&&...mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->owner = this;
		/*
		std::unique_ptr<Component> uPtr(c);
		Vcomponents.emplace_back(std::move(uPtr));*/
		Vcomponents.emplace_back(std::move(c));

		Acomponents[GetComponentID<T>()] = c;
		CComponents[GetComponentID<T>()] = true;

		c = nullptr;
	}

	template<typename T, typename...TArgs>
	inline void addDrawableComponent(TArgs&&...mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->owner = this;

		Vcomponents.emplace_back(std::move(c));
		DrawableComps.emplace_back(std::move(c));

		Acomponents[GetComponentID<T>()] = c;
		CComponents[GetComponentID<T>()] = true;

		c = nullptr;
	}

	template<typename t>
	inline bool hasComponent() const
	{
		return CComponents[GetComponentID<t>()];
	}

	template <typename T>
	T& getComponent() const
	{
		auto ptr(Acomponents[GetComponentID<T>()]);
		return *static_cast<T*>(ptr);
	}

	inline void update()
	{
		for (auto& c : Vcomponents)
			c->update();
	}

	inline void draw()
	{
		for (auto& dc : DrawableComps)
			dc->update();
	}
	
	inline bool Active()
	{
		return isActive;
	}
};

class EntityManager
{

public:
	std::vector<std::unique_ptr<Entity>> entities;
	void update()
	{
		for (auto& e : entities)
			e->update();
	}


	void draw()
	{
		for (auto& e : entities)
			e->draw();
	}

	void AddEntity(Entity& entity)
	{
		std::unique_ptr<Entity> uPtr(&entity);
		entities.emplace_back(std::move(uPtr));
	}


	void Refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return mEntity->Active();
			}

		));

	}

	~EntityManager()
	{
		entities.erase(entities.begin(), entities.end());
		
		;
	
	}

};