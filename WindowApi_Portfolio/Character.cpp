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

Hero::Hero(int hnum)
{
	state = 0;
	heronum = hnum;
	switch (hnum)
	{
	case 1:
		range = 250;
		atkspd = 3;
		dmg = 10;
		maxhp = 100;
		hp = 100;
		projsize = 4;
		break;
	case 2:
		range = 300;
		atkspd = 10;
		dmg = 40;
		maxhp = 100;
		hp = 100;
		projsize = 8;
		break;
	}
}

BOOL Hero::canShoot()
{
	if (cnt == atkspd)
	{
		cnt = 1;
		return true;
	}
	else
	{
		cnt++;
		return false;
	}
}

void Hero::HasTarget(vector<Enemy*> enems)
{
	bool hast = false;
	for (int i = 0; i < enems.size(); i++)
	{
		if (ut.inCircleRange(curPos, enems[i]->GetcurPos(), range))
		{
			state = 2;
			hast = true;
		}
	}
	if (!hast)
		state = 1;
}

Enemy::Enemy()
{
	range = SIZE;
	state = 1;
	maxhp = 100;
	hp = 100;
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
	if (cnt < 15)
	{
		curPos.x += (dx - x) / 15;
		curPos.y += (dy - y) / 15;
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
	range = 4;
}

void Projectile::Move(RECT rt)
{
	int w = rt.right;
	int h = rt.bottom;
	h /= COL + 1;

	curPos.x += dir.x * 15;
	curPos.y += dir.y * 15;
	if (curPos.x <0 || curPos.x > w ||
		curPos.y <0 || curPos.y > h * COL)
		death = true;
}

void Projectile::Collision(vector<Enemy*> enems)
{
	POINT pt;
	for (int i = 0; i < enems.size(); i++)
	{
		pt = { curPos.x + 2 * dir.x , curPos.y + 2 * dir.y };
		if (ut.inCircleRange(pt, enems[i]->GetcurPos(), 20))
		{
			enems[i]->Damaged(dmg);
			if (enems[i]->GetCurHP() <= 0)
				enems[i]->Die();
			death = true;
		}
	}
}
