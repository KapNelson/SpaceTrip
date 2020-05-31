#include "GameObject.h"

void GameObject::SetScene(Scene& scene)
{
    parentScene = &scene;
}

void GameObject::Move(Vector2f from, Vector2f to, float speed)
{
     float retX = Lerp(from.x, to.x, speed);
     float retY = Lerp(from.y, to.y, speed);
     SetPosition(Vector2f(retX, retY));
}

float GameObject::Lerp(float a, float b, float delta)
{
    return a * (1 - delta) + b * delta;
}
