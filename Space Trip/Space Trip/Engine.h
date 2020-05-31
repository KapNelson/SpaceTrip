#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Scene.h"
#include "Camera.h"
using namespace sf;

class Engine
{
private:
	Image icon;
	std::string const TITLE = "Space Trip";
	float const FPS = 1000 / 60;
	Clock delta;
	Scene* currentScene;
public:
	int const WIDTH = 800, HEIGHT = 600;
	RenderWindow window;
	Camera camera;
	void Run();
    void LoadScene(Scene &scn);
	Vector2f GetWindowCenter();
	Engine();
};
