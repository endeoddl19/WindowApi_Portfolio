#include "Character.h"

void Character::Update(const RECT&)
{
	
}

void Character::FindPath()
{
	ANode* a = NULL;
	//a->setMap();
	//a->AStar(respon.x, respon.y, destin.x, destin.y);
	cpath = a->getPath();
	a->close();
}

Hero::Hero()
{
}

void Hero::Create(POINT pt, int chn)
{

}

void Hero::Deal(Hero*)
{

}

void Hero::Death()
{
}

Enemy::Enemy()
{
}

//void Enemy::getSetting(int arr[][])
//{
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			if (arr[i][j] == 2)
//				respon = { i,j };
//			if (arr[i][j] == 3)
//				destin = { i,j };
//		}
//	}
//}

void Enemy::Create(RECT rt)
{

	Enemy* e = new Enemy;
	e->curPos.x = respon.x * rt.right / 8 + rt.right / 16;
	e->curPos.y = respon.y * rt.bottom / 8 + rt.bottom / 16;
	e->path = cpath;
	enemies.push_back(e);
	characters.push_back(e);
}

void Enemy::Move(RECT rt)
{
	int w = rt.right;
	int h = rt.bottom;
	w /= 8;
	h /= 9;
	int x, y, dx, dy;

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->path.size() == enemies[i]->pathcount + 1)
			enemies.erase(enemies.begin());
		else
		{
			x = enemies[i]->path[enemies[i]->pathcount].x * w + w / 2;
			y = enemies[i]->path[enemies[i]->pathcount].y * h + h / 2;
			dx = enemies[i]->path[enemies[i]->pathcount+1].x * w + w / 2;
			dy = enemies[i]->path[enemies[i]->pathcount+1].y * h + h / 2;
			if (enemies[i]->cnt < 10)
			{
				enemies[i]->curPos.x += (dx - x) / 10;
				enemies[i]->curPos.y += (dy - y) / 10;
				enemies[i]->cnt++;
			}
			else
			{
				enemies[i]->cnt = 1;
				enemies[i]->pathcount++;
				enemies[i]->curPos.x = dx;
				enemies[i]->curPos.y = dy;
			}
				
		}
	}
}

void Enemy::DrawEnemy(HDC hdc)
{
	for (int i = 0; i < enemies.size(); i++)
		Ellipse(hdc, enemies[i]->curPos.x - 20, enemies[i]->curPos.y - 20, 
			enemies[i]->curPos.x + 20, enemies[i]->curPos.y + 20);
}


void Enemy::Deal(Enemy*)
{
}

void Enemy::Death(int n)
{
	enemies.erase(enemies.begin() + n);
}

