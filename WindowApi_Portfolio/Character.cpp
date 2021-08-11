#include "Character.h"

void Character::SetInitPos(POINT pt)
{
	this->curPos.x = pt.x;
	this->curPos.y = pt.y;
}

void Character::FindAtkDir(vector<POINT> pts, RECT rect)
{
	POINT pt;
	vector<POINT> temp;
	int max = 0, m = 0;
	pt = ut.ToTilePos(curPos, rect.right, rect.bottom);

	int i = 0;
	for ( i = 0; i < pts.size(); i++)
	{
		if (pts[i].x == pt.x)
			temp.push_back(pts[i]);
		if (pts[i].y == pt.y)
			temp.push_back(pts[i]);
	}

	for (i = 0; i < temp.size(); i++)
	{
		if (ut.PointDistance(temp[i], pt) > max)
		{
			max = ut.PointDistance(temp[i], pt);
			m = i;
		}
	}
	if (temp[m].x == pt.x)
	{
		dir.x = 0;
		dir.y = abs(temp[m].y - pt.y) / abs(temp[m].y - pt.y);
	}
	else
	{
		dir.x = abs(temp[m].x - pt.x) / abs(temp[m].x - pt.x);
		dir.y = 0;
	}
}

BOOL Character::canShoot()
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

Hero::Hero(int hnum)
{
	state = 0;
	heronum = hnum;
	switch (hnum)
	{
	
	case 0:
		range = 250;
		atkspd = 5;
		dmg = 10;
		maxhp = 100;
		hp = 100;
		projsize = 4;
		break;
	case 1:
		range = 300;
		atkspd = 15;
		dmg = 40;
		maxhp = 100;
		hp = 100;
		projsize = 8;
		break;
	case 2:
		range = 400;
		atkspd = 20;
		dmg = 50;
		maxhp = 200;
		hp = 200;
		projsize = 1;
		break;
	case 3:
		range = 50;
		atkspd = 5;
		dmg = 10;
		maxhp = 100;
		hp = 100;
		projsize = 4;
		break;
	case 4:
		range = 50;
		atkspd = 15;
		dmg = 40;
		maxhp = 100;
		hp = 100;
		projsize = 8;
		break;
	case 5:
		range = 50;
		atkspd = 10;
		dmg = 30;
		maxhp = 300;
		hp = 300;
		projsize = 1;
		break;
	}
}

void Hero::Collision(vector<Enemy*> enems)
{
	for (int i = 0; i < enems.size(); i++)
	{
		if (ut.inCircleRange(curPos, enems[i]->GetcurPos(), SIZE * 2))
		{
			state = 2;
			dir = { (enems[i]->GetcurPos().x - curPos.x),
				(enems[i]->GetcurPos().y - curPos.y) };
		}
		else
			state = 0;
	}
}

void Hero::Target(vector<Enemy*> enems, RECT rt)
{
	bool hast = false;
	POINT temp;
	for (int i = enems.size()-1; i >= 0; i--)
	{
		if (ut.inCircleRange(curPos, enems[i]->GetcurPos(), range))
		{
			state = 2;
			temp = enems[i]->getMoving();
			temp = ut.ToMapPos(temp, rt.right, rt.bottom);
			dir = { ((enems[i]->GetcurPos().x + temp.x)/2 - curPos.x),
				((enems[i]->GetcurPos().y + temp.y)/2 - curPos.y)};
			hast = true;
		}
	}
	if (!hast)
		state = 0;
}

Enemy::Enemy()
{
	range = 50;
	state = 1;
	maxhp = 100;
	hp = 100;
	atkspd = 10;
	dmg = 10;
	projsize = 1;
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
	if (cnt < 20)
	{
		curPos.x += (dx - x) / 20;
		curPos.y += (dy - y) / 20;
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

void Enemy::Collision(vector<Hero*> heros)
{
	for (int i = 0; i < heros.size(); i++)
	{
		if (ut.inCircleRange(curPos, heros[i]->GetcurPos(), SIZE * 2))
		{
			state = 2;
			dir = { (heros[i]->GetcurPos().x - curPos.x),
				(heros[i]->GetcurPos().y - curPos.y) };
		}
		else
			state = 1;
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

	curPos.x += dir.x/10;
	curPos.y += dir.y/10;

	if (ut.PointDistance(curPos, init) > range)
		death = true;
	if (curPos.x <0 || curPos.x > w ||
		curPos.y <0 || curPos.y > h * COL)
		death = true;
	
}

void Projectile::setProj(POINT pt, POINT di, int s, int d, int r)
{
	curPos = init = pt;
	dir = di;
	size = s;
	dmg = d;
	range = r;
}

void Projectile::Collision(vector<Enemy*> enems)
{
	for (int i = 0; i < enems.size(); i++)
	{
		if (ut.inCircleRange(curPos, enems[i]->GetcurPos(), SIZE))
		{
			enems[i]->Damaged(dmg);
			if (enems[i]->GetCurHP() <= 0)
				enems[i]->Die();
			death = true;
		}
	}
}
