#include "Character.h"

void Character::SetInitPos(POINT pt)
{
	this->curPos.x = pt.x;
	this->curPos.y = pt.y;
}

void Character::FindAtkDir(vector<POINT> pts, RECT rect)
{
	POINT pt;
	pt = ut.ToTilePos(curPos, rect.right, rect.bottom);

	int i = 0;
	while (i < pts.size() && pts[i].x != pt.x)
		i++;
	if (i == pts.size())
	{
		i = 0;
		while (i < pts.size() && pts[i].y != pt.y)
			i++;
		(pts[i].x > pt.x) ? dir = { 1,0 } : dir = { -1,0 };
	}
	else
		(pts[i].y > pt.y) ? dir = { 0,1 } : dir = { 0,-1 };
}

Hero::Hero()
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
	w /= ROW;
	h /= COL + 1;
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

Projectile::Projectile()
{
}

void Projectile::Move(RECT rt)
{
	int w = rt.right;
	int h = rt.bottom;
	h /= COL + 1;

	curPos.x += dir.x * 30;
	curPos.y += dir.y * 30;
	if (curPos.x <0 || curPos.x > w ||
		curPos.y <0 || curPos.y > h * COL)
		death = true;
}
