#include "GameObject.h"
#include "SpriteObject.cpp"
#include "TextObject.cpp"
#include <ctime>
using namespace sf;

class Background : public SpriteObject
{
private:
    Vector2f *target;
    void Start()
    {
        SetTexture("Background.png");
    }
    void Update()
    {
        if (target != nullptr)
        {
            SetPosition(*target);
        }
    }
public:
    void SetTarget(Vector2f& t)
    {
        target = &t;
    }
};

class Planet : public SpriteObject
{
private:
    int run;
    //std::vector<std::string> PlanetTextures = {"Planet.png","Planet1.png","Planet2.png","Planet3.png","Planet4.png","Planet5.png","Planet6.png"};
    Vector2f position;
    void Start()
    {
        //srand(time(NULL));
        //r = rand() % 6;
        SetTexture("Planet.png");
        SetScale(Vector2f(0.5,0.5));
        SetPosition(position);
        run = rand() % 9 + 1;
    }
    void Update()
    {
        //SetPosition(Vector2f(GetPosition().x + run, GetPosition().y));
    }
public:
    void CreatePlanet(Vector2f pos)
    {
        position = pos;
    }
};

class Rocket : public SpriteObject
{
private:
    bool idle = true;
    float speed = 3;
    Vector2f* planetTarget;
    Vector2f moveTarget;
    void Start()
    {
        SetTexture("Rocket.png");
        SetScale(Vector2f(0.5, 0.5));
        //parent.setPosition(Vector2f(400, 300));
    }
    void Update()
    {
        if (planetTarget == nullptr)
            return;
        if (idle)
        {
            RotateAround(*planetTarget, speed);
            SetRotation(180 + LookOn(*planetTarget, localPos));
        }
        else 
        {
            //moveTarget = Vector2f(moveTarget.x / 100 + GetPosition().x, moveTarget.y / 100 + GetPosition().y);
            Move(GetPosition(), moveTarget, 0.001);
        }
    }
public:
    bool IsMoving()
    {
        return !idle;
    }
    float LookOn(Vector2f parent, Vector2f obj)
    {
        Vector2f tmp = obj - parent;
        return (float)atan2(tmp.y, tmp.x) * (180 / M_PI);
    }
    void SetPlanet(Vector2f& rocket)
    {
        planetTarget = &rocket;
        idle = true;
    }
    void IncSpeed()
    {
        speed += 0.01;
    }
    void Fly()
    {
        idle = false;
        SetRotation(90 + LookOn(*planetTarget, localPos));

        double k, b, tmp;
        Vector2f dir;
        k = (planetTarget->y - localPos.y) / (planetTarget->x - localPos.x);
        b = planetTarget->y - k * planetTarget->x;
        if (localPos.x - planetTarget->x == 0)
        {
            if (localPos.y - planetTarget->y > 0)
                tmp = localPos.y + 1000;
            else
                tmp = localPos.y - 1000;
            dir = Vector2f(localPos.x, tmp);
        }
        else
        {
            if (localPos.x - planetTarget->x > 0)
                tmp = localPos.x + abs(localPos.x - planetTarget->x) * 100;
            else
                tmp = localPos.x - abs(localPos.x - planetTarget->x) * 100;
            dir = Vector2f(tmp, k * tmp + b);
        }
        
        moveTarget = dir;
        //std::cout << GetPosition().x << "........" << GetPosition().y << '\n' << dir.x << "........" << dir.y << std::endl;
    }
};

class Ghost : public SpriteObject
{
    void Start() 
    {
        parentScene->engine->camera.SetTarget(GetGlobalPosition());
    };
    void Update() 
    {
        if (Keyboard::isKeyPressed(Keyboard::Left))
            SetPosition(Vector2f(GetPosition().x - 10, GetPosition().y));
        if (Keyboard::isKeyPressed(Keyboard::Right))
            SetPosition(Vector2f(GetPosition().x + 10, GetPosition().y));
        if (Keyboard::isKeyPressed(Keyboard::Up))
            SetPosition(Vector2f(GetPosition().x, GetPosition().y - 10));
        if (Keyboard::isKeyPressed(Keyboard::Down))
            SetPosition(Vector2f(GetPosition().x, GetPosition().y + 10));
    };
};
class CameraObject : public SpriteObject
{
    Vector2f dest;
    bool mustMove;
    FloatRect bounds;
    void Start()
    {

    }
    void Update()
    {
        if (!mustMove)
        {
            return;
        }
        Move(GetGlobalPosition(),dest,0.1f);
        //std::cout << GetGlobalPosition().x << GetGlobalPosition().y << '\n';
        parentScene->engine->camera.SetTarget(GetGlobalPosition());
        if (dest == GetPosition())
            mustMove = false;
        Vector2f position = Vector2f(GetGlobalPosition().x - parentScene->engine->WIDTH/2, GetGlobalPosition().y - parentScene->engine->HEIGHT / 2);
        bounds = FloatRect(position, Vector2f(parentScene->engine->WIDTH, parentScene->engine->HEIGHT));
    }
public:
    void MoveTo(Vector2f to)
    {
        dest = Vector2f(to.x, to.y);
        mustMove = true;
    }
    bool IsOutOfBounds(FloatRect obj)
    {
        //std::cout << bounds.left << '\t' << bounds.top << '\n' << obj.left << '\t' << obj.top << '\n';
        return !bounds.intersects(obj);
    }
};