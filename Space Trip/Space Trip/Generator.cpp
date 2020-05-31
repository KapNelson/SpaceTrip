#include "Generator.h"

Sector::Sector(Direction dir, Vector2f currPos)
{
	direct = dir;
	pos = currPos;
}

void Generator::GenerateNext()
{ 
	if (sectors.size() > 4)
	{
		sectors.pop_front();
		index--;
	}
	srand(time(NULL));
	for (int i = 0; i < 3; i++)
	{
		std::list<Sector>::iterator it;
		
		int r = rand() % 3;
		if (sectors.size() > 1)
		{
			it = sectors.end();
			((it--)--)--;
			if (abs((*it).direct - r) == 2)
				if (r == 3)
					r--;
				else
					r++;
			//std::cout << (*it).direct << "<-" <<'\n';
		}
		lastDir = static_cast<Direction> (r);
		switch (lastDir)
		{
		case TopLeft:
			CurrentPos.x -= WIDTH;
			CurrentPos.y += HEIGHT;
			break;
		case TopRight:
			CurrentPos.x += WIDTH;
			CurrentPos.y += HEIGHT;
			break;
		case BottomRight:
			CurrentPos.x += WIDTH;
			CurrentPos.y -= HEIGHT;
			break;
		case BottomLeft:
			CurrentPos.x -= WIDTH;
			CurrentPos.y -= HEIGHT;
			break;
		}
		Sector tmp(lastDir, CurrentPos);
		sectors.push_back(tmp);
	}
}

Vector2f Generator::GetNext()
{
	if ((index % 3) == 0)
	{
		GenerateNext();
	}
	std::list<Sector>::iterator it;
	it = sectors.begin();
	for (int i = 0; i < index; i++)
		it++;
	index++;
	return (*it).pos;
}

int Generator::GetMaxSectors()
{
	return max;
}