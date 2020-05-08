#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
using namespace sf;

class Camera
{
private:
	View view;
	Vector2f *pos;
public:
	Camera(RenderWindow& rw);
	void SetTarget(Vector2f& position);
	void Update(RenderWindow& rw);
};
