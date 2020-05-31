#pragma once
#include <SFML/Audio.hpp>
#include "Scene.h"
#include "GameObjects.cpp"
#include "Generator.h"
#include <iostream>
using namespace sf;

class CameraView
{
private:
    Planet firstPlanet, secondPlanet;
public:
    Vector2f center;
    Vector2f PlanetCenter();
    void SetPlanet(Planet fp, Planet sp);
};
class GameOver : public Scene
{
    Background bg;
    TextObject gameOver, esc, score, name;
    Music music;
    void Init();
    void Update();
};
class GameScene : public Scene
{
    Background bg;
    TextObject score, name;
    std::list<Planet> planets;
    std::list<Planet>::iterator it;
    Planet targetPlanet;
    Rocket rocket;
    Generator generator;
    CameraView view;
    CameraObject cameraObj;
    Ghost ghost;
    Music music;
    GameOver gameOver;
    int s = 0, n = 1;
    char sc[100] = "0";
    int c = 0;
    bool isSpace = 0;
    void CreatePlanet(Vector2f pos);
    void Init();
    void Update();
};
class Menu : public Scene
{
private:
    Background bg;
    TextObject name, author, start;
    GameScene gamescene;
    Music music;
    void Init();
    void Update();
public:
    Menu();
};