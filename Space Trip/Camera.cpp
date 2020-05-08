#include "Camera.h"
Camera::Camera(RenderWindow& rw)
{
	view.reset(FloatRect(0.0, 0.0, rw.getSize().x, rw.getSize().y));
	view.setViewport(FloatRect(0.0, 0.0, 1.0, 1.0));
	view.setCenter(Vector2f(rw.getSize().x * 1024, rw.getSize().y * 1024));
}
void Camera::SetTarget(Vector2f& position)
{
	pos = &position;
}
void Camera::Update(RenderWindow& rw)
{
	if (pos != nullptr)
	{
		Vector2f f(pos->x, pos->y);
		f.x = pos->x + rw.getSize().x / 1024;
		f.y = pos->y + rw.getSize().y / 1024;
		view.setCenter(f);
		rw.setView(view);
		//std::cout << f.x << '\t' << f.y << '\n';
	}
}