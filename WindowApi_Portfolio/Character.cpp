#include "Character.h"

void Character::Target(Hero* h, vector<Enemy*> enems, RECT rt)
{
	bool hast = false;
	for (int i = enems.size() - 1; i >= 0; i--)
	{
		if (ut.inCircleRange(h->cs.curPos, enems[i]->cs.curPos, h->cs.range))
		{
			h->cs.state = 2;
			h->cs.dir = { (enems[i]->cs.curPos.x - h->cs.curPos.x),
				(enems[i]->cs.curPos.y - h->cs.curPos.y) };
			hast = true;

			if (h->cs.cnt == h->cs.atkspd)
			{
				Damaged(enems[i], h->cs.dmg);
				h->cs.cnt = 1;
				if (enems[i]->cs.hp <= 0)
					enems[i]->cs.death = true;
			}
			else
				h->cs.cnt++;
		}
	}
	if (!hast)
		h->cs.state = 0;
}

void Character::FindAtkDir(Hero* hero, vector<POINT> pts, RECT rect)
{
	if (hero->heronum > 2)
		hero->cs.dir = { -1,0 };
	else
	{
		POINT pt;
		pt = hero->cs.curPos;
		pt.x -= rect.right / WCOL;
		pt.y -= rect.bottom * 3 / WCOL;
		vector<POINT> temp;
		int min = 1024512, m = 0;
		pt = ut.ToTilePos(pt, rect.right * 7 / WCOL, rect.bottom / 2);

		int i = 0;
		for (i = 0; i < pts.size(); i++)
		{
			if (pts[i].x == pt.x)
				temp.push_back(pts[i]);
			if (pts[i].y == pt.y)
				temp.push_back(pts[i]);
		}

		for (i = 0; i < temp.size(); i++)
		{
			if (ut.PointDistance(temp[i], pt) < min)
			{
				min = ut.PointDistance(temp[i], pt);
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
}

void Character::Move(Enemy* e, RECT rt)
{
	int w = rt.right * 7 / WCOL;
	int h = rt.bottom / 2;
	w /= ROW;
	h /= COL;
	int x, y, dx, dy;

	x = rt.right / WCOL + e->path[e->pathcount].x * w + w / 2;
	y = rt.bottom * 3 / WCOL + e->path[e->pathcount].y * h + h / 2;
	dx = rt.right / WCOL + e->path[e->pathcount + 1].x * w + w / 2;
	dy = rt.bottom * 3 / WCOL + e->path[e->pathcount + 1].y * h + h / 2;
	(dx - x >= 0) ? e->curDir = { 1,0 } : e->curDir = { -1,0 };
	//(dy - y >= 0) ? e->curDir = { 0,1 } : e->curDir = { 0,-1 };

	if (e->movecnt < 25)
	{
		e->cs.curPos.x += (dx - x) / 25;
		e->cs.curPos.y += (dy - y) / 24;
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