#include "GameObject.h"
#include <cmath>
#define M_PI 3.14159265358979323846
using namespace sf;

class TextObject : public GameObject
{
protected:
    Font font;
    Text text;
public:
    void Draw(RenderWindow& rw)
    {
        rw.draw(text);
    }
    void SetPosition(Vector2f pos)
    {
        localPos = pos;
        text.setPosition(localPos);
    }
    void SetRotation(float a)
    {
        localRotation = a;
        text.setRotation(localRotation);
    }
    void SetScale(Vector2f sc)
    {
        scale = sc;
        text.setScale(scale);
    }
    void RotateAround(Vector2f pos, float angle)
    {
        angle = angle * (M_PI / 180.0);
        float x1 = pos.x;
        float y1 = pos.y;

        float x2 = (float)(x1 * cos(angle) - y1 * sin(angle));
        float y2 = (float)(x1 * sin(angle) + y1 * cos(angle));

        SetPosition(Vector2f(x2, y2));
    }
    Vector2f GetPosition()
    {
        return text.getPosition();
    }
    void SetFont(std::string fn)
    {
        if (!font.loadFromFile(fn))
        {
            throw("Error field to load font!");
        }
        text.setFont(font);
    }
    void SetColor(Color color)
    {
        text.setFillColor(color);
    }
    void SetStyle(Text::Style style)
    {
        text.setStyle(style);
    }
    void SetText(std::string str)
    {
        text.setString(str);
    }
    void SetSize(int size)
    {
        text.setCharacterSize(size);
    }
    void CenterText(float width, int n)
    {
        SetPosition(Vector2f((width - text.getLocalBounds().width)/2, text.getPosition().y + n*text.getLocalBounds().height));
    }
    void Start()
    {
        
    }
    void Update()
    {
        
    }
};