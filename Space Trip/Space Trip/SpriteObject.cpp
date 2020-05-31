#include "Engine.h"
#include <cmath>
#define M_PI 3.14159265358979323846
using namespace sf;

class SpriteObject : public GameObject
{
private:
    Texture texture;
protected:
    Sprite sprite;   
public:
    FloatRect collider;
    void Draw(RenderWindow &rw)
    {
        rw.draw(sprite);
    }
    void SetPosition(Vector2f pos)
    {
        localPos = pos;
        globalPos = localPos;
        sprite.setPosition(globalPos);
        NormalizeCollider();
    }
    void SetRotation(float a)
    {
        localRotation = a;
        sprite.setRotation(localRotation);
    }
    void SetScale(Vector2f sc)
    {
        scale = sc;
        sprite.setScale(scale);
    }
    void RotateAround(Vector2f pos, float angle)
    {
        angle = (angle) * (M_PI / 180);

        float rotatedX = cos(angle) * (localPos.x - pos.x) - sin(angle) * (localPos.y - pos.y) + pos.x;
        float rotatedY = sin(angle) * (localPos.x - pos.x) + cos(angle) * (localPos.y - pos.y) + pos.y;
        SetPosition(Vector2f(rotatedX, rotatedY));
    }
    void SetTexture(std::string path)
    {
        if (!texture.loadFromFile(path))
            throw("Error field to load texture!");
        sprite = Sprite(texture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        selfTrans = sprite;
        collider = sprite.getGlobalBounds();
        //SetPosition(parentScene->engine->GetWindowCenter());
    }
    void NormalizeCollider()
    {
        FloatRect bounds = sprite.getGlobalBounds();
        collider.left = bounds.left;
        collider.top = bounds.top;
    }
    Vector2f GetPosition()
    {
        return sprite.getPosition();
    }
    Vector2f& GetGlobalPosition()
    {
        return globalPos;
    }
    float GetRotation()
    {
        return localRotation;
    }
};