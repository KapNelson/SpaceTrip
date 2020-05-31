#include "Engine.h"

void Engine::Run()
{
	//RenderWindow window(VideoMode(WIDTH, HEIGHT), TITLE);
	if (!icon.loadFromFile("Planet.png"))
		throw("Error field to load icon!");
	window.setIcon(200, 200, icon.getPixelsPtr());
	//Camera camera(window);
	delta.restart();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (delta.getElapsedTime().asMilliseconds() > FPS)
		{
			window.clear();
			currentScene->Update();
			currentScene->UpdateGameObjects(window);
			camera.Update(window);
			window.display();
			delta.restart();
		}
	}
}
void Engine::LoadScene(Scene &scn)

{
	currentScene = &scn;
	currentScene->SetEngine(*this);
	currentScene->Init();
}

Vector2f Engine::GetWindowCenter()
{
	return Vector2f(WIDTH/2,HEIGHT/2);
}

Engine::Engine():window(VideoMode(WIDTH, HEIGHT), TITLE), camera(window)
{

}
