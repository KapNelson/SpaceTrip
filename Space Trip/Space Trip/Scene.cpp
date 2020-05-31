#include "Scene.h"

void Scene::UpdateGameObjects(RenderWindow &rw)
	{
		for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
		{
			(**it).Update();
			(**it).Draw(rw);
		}
	}
void Scene::RegGameObjects(GameObject &go)
	{
		gameObjects.push_back(&go);
		gameObjects.back()->SetScene(*this);
		gameObjects.back()->Start();
	}
void Scene::SetEngine(Engine& eng)
{
	engine = &eng;
}

void Scene::RemoveGameObject(GameObject& go)
{
	gameObjects.remove(&go);
}

Scene::Scene(){ ; }

 
