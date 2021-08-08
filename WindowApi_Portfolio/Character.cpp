#include "Character.h"

void Character::SetInitPos(POINT pt)
{
	this->curPos.x = pt.x;
	this->curPos.y = pt.y;
}

Hero::Hero()
{
}

void Hero::Death()
{
}

Enemy::Enemy()
{
}

bool Enemy::isArrive()
{
	if (path.size() == pathcount + 1)
		return true;
	else
		return false;
}

void Enemy::Move(RECT rt)
{
	int w = rt.right;
	int h = rt.bottom;
	w /= 8;
	h /= 9;
	int x, y, dx, dy;

	x = path[pathcount].x * w + w / 2;
	y = path[pathcount].y * h + h / 2;
	dx = path[pathcount + 1].x * w + w / 2;
	dy = path[pathcount + 1].y * h + h / 2;
	if (cnt < 10)
	{
		curPos.x += (dx - x) / 10;
		curPos.y += (dy - y) / 10;
		cnt++;
	}
	else
	{
		cnt = 1;
		pathcount++;
		curPos.x = dx;
		curPos.y = dy;
	}
}

void Enemy::Death(int n)
{
	
}

