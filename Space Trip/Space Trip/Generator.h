#pragma once
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace sf;
enum Direction { Center = -1, TopLeft = 0, TopRight = 1, BottomLeft = 3, BottomRight = 2 };
class Sector
{
public:
	Direction direct;
	Vector2f pos;
	Sector(Direction dir, Vector2f currPos);
};
class Generator
{
private:
	Direction lastDir = TopLeft;
	Vector2f CurrentPos;
public:
	const int WIDTH = 400, HEIGHT = 300;
	int index, max;
	std::list<Sector> sectors;
	void GenerateNext();
	Vector2f GetNext();
	int GetMaxSectors();
};

