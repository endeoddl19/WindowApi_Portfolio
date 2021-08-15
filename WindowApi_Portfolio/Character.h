#pragma once

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Astar.h"
#include "Utils.h"
#include <algorithm>

struct CharStat
{
	POINT dir;
	POINT curPos;
	FLOAT maxhp;
	FLOAT hp;
	FLOAT dmg;
	FLOAT atkspd;
	FLOAT range;

	int cnt;
	int state;
	// 0: 정지 / 1: 움직임 / 2: 공격 / 3: 죽는중
	bool death;
};
struct Hero
{
	CharStat cs;
	int cost;
	int heronum; 
};
struct Enemy
{
	CharStat cs;
	int movecnt = 1;
	int pathcount = 0;
	vector<POINT> path;
	POINT curDir;
};
struct Projectile
{
	CharStat cs;
	int pnum;
	POINT init;
};

class Character
{
private:
	RECT rt;
public:
	Utils ut;

	FLOAT GetHP(Hero* h) { return (h->cs.hp / h->cs.maxhp); }
	FLOAT GetHP(Enemy* e) { return (e->cs.hp / e->cs.maxhp); }
	FLOAT getAtk(Hero* h) { return h->cs.cnt / (h->cs.atkspd / 4); }
	FLOAT getAtk(Enemy* e) { return e->cs.cnt / (e->cs.atkspd / 9); }

	void Target(Hero*, vector<Enemy*>, RECT);
	void FindAtkDir(Hero*, vector<POINT>, RECT);
	void Damaged(Hero* h, FLOAT d) { h->cs.hp -= d; }
	void Damaged(Enemy* e, FLOAT d) { e->cs.hp -= d; }
	void Move(Enemy*, RECT);
	void Move(Projectile* , RECT);
	bool isArrive(Enemy*);
};

#endif