#include "Character.h"

void Character::Target(Hero* h, vector<Enemy*> enems, RECT rt)
{
	bool hast = false;
	for (int i = enems.size() - 1; i >= 0; i--)
	{
		if (ut.inCircleRange(curPos, enems[i]->GetcurPos(), range))
		{
			state = 2;
			dir = { (enems[i]->GetcurPos().x - curPos.x),
				(enems[i]->GetcurPos().y - curPos.y) };
			hast = true;

			if (AttackAble)
				enems[i]->Damaged(dmg);
			if (enems[i]->GetCurHP() <= 0)
				enems[i]->Die();
		}
	}
	if (!hast)
		state = 0;
}

void Character::FindAtkDir(Hero* hero, vector<POINT> pts, RECT rect)
{
	POINT pt;
	vector<POINT> temp;
	int max = 0, m = 0;
	pt = ut.ToTilePos(hero->cs.curPos, rect.right, rect.bottom);

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
		hero->cs.dir.x = 0;
		hero->cs.dir.y = abs(temp[m].y - pt.y) / abs(temp[m].y - pt.y);
	}
	else
	{
		hero->cs.dir.x = abs(temp[m].x - pt.x) / abs(temp[m].x - pt.x);
		hero->cs.dir.y = 0;
	}
}

BOOL Character::AttackAble(Hero* hero)
{
	if (hero->cs.cnt == hero->cs.atkspd)
	{
		hero->cs.cnt = 1;
		return true;
	}
	else
	{
		hero->cs.cnt++;
		return false;
	}
}

BOOL Character::AttackAble(Enemy* enemy)
{
	if (enemy->cs.cnt == enemy->cs.atkspd)
	{
		enemy->cs.cnt = 1;
		return true;
	}
	else
	{
		enemy->cs.cnt++;
		return false;
	}
}

void Character::Move(Enemy* e, RECT rt)
{
	int w = rt.right;
	int h = rt.bottom;
	w /= ROW;
	h /= WCOL;
	int x, y, dx, dy;

	x = e->path[e->pathcount].x * w + w / 2;
	y = e->path[e->pathcount].y * h + h / 2;
	dx = e->path[e->pathcount+1].x * w + w / 2;
	dy = e->path[e->pathcount+1].y * h + h / 2;
	(dx - x >= 0) ? e->curDir = { 1,0 } : e->curDir = { -1,0 };

	if (e->movecnt < 20)
	{
		e->cs.curPos.x += (dx - x) / 20;
		e->cs.curPos.y += (dy - y) / 20;
		e->movecnt++;
	}
	else
	{
		e->movecnt = 1;
		e->pathcount++;
		e->cs.curPos.x = dx;
		e->cs.curPos.y = dy;
	}
}

void Character::Move(Projectile* p, RECT rt)
{
	int w = rt.right;
	int h = rt.bottom;
	h /= WCOL;

	p->cs.curPos.x += p->cs.dir.x / 5;
	p->cs.curPos.y += p->cs.dir.y / 5;

	if (ut.PointDistance(p->cs.curPos, p->init) > p->cs.range)
		p->cs.death = true;
	if (p->cs.curPos.x <0 || p->cs.curPos.x > w ||
		p->cs.curPos.y <0 || p->cs.curPos.y > h * COL)
		p->cs.death = true;
}

bool Character::isArrive(Enemy* e)
{
	if (e->path.size() == e->pathcount + 1)
		return true;
	else
		return false;
}

Hero::Hero(int hnum)
{
	state = 0;
	cnt = 1;
	heronum = hnum;
	switch (hnum)
	{
	case 0:
		range = 250;
		atkspd = 10;
		dmg = 15;
		maxhp = 100;
		hp = 100;
		projsize = 4;
		break;
	case 1:
		range = 300;
		atkspd = 30;
		dmg = 30;
		maxhp = 100;
		hp = 100;
		projsize = 8;
		break;
	case 2:
		range = 400;
		atkspd = 40;
		dmg = 50;
		maxhp = 200;
		hp = 200;
		projsize = 10;
		break;
	case 3:
		range = 20;
		atkspd = 30;
		dmg = 15;
		maxhp = 100;
		hp = 100;
		projsize = 1;
		break;
	case 4:
		range = 20;
		atkspd = 40;
		dmg = 10;
		maxhp = 350;
		hp = 350;
		projsize = 1;
		break;
	case 5:
		range = 20;
		atkspd = 50;
		dmg = 40;
		maxhp = 200;
		hp = 200;
		projsize = 1;
		break;
	}
}