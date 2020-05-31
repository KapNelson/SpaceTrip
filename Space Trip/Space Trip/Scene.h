#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <list>
#include "GameObject.h"
using namespace sf;

class Engine;

class Scene
{
protected:
	std::list<GameObject*> gameObjects;
public:
	Engine *engine;
	virtual void Init() = 0;
	virtual void Update() = 0;
	void UpdateGameObjects(RenderWindow& rw);
	void RegGameObjects(GameObject &go);
	void SetEngine(Engine& eng);
	void RemoveGameObject(GameObject &go);
	Scene();
};
