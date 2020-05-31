#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
using namespace sf;

class Scene;

class GameObject
{
private:
    float Lerp(float a, float b, float delta);
protected:
    Vector2f localPos, scale, globalPos;
    float localRotation;
    Scene *parentScene;
public:
    Transformable selfTrans;
    int name;
    virtual void Draw(RenderWindow& rw) = 0;
    virtual void SetPosition(Vector2f pos) = 0;
    virtual void SetRotation(float a) = 0;
    virtual void SetScale(Vector2f sc) = 0;    
    virtual void RotateAround(Vector2f pos, float angle) = 0;
    virtual Vector2f GetPosition() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    void SetScene(Scene& scene);
    void Move(Vector2f from, Vector2f to, float speed);
};
