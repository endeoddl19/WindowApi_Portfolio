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

	int range;
	int atkspd;
	int dmg;
	int cnt;
	int projsize;
	int state;
	// 0: 정지 / 1: 움직임 / 2: 공격 / 3: 죽는중
	bool death = false;
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
	int movecnt;
	int pathcount = 0;
	vector<POINT> path;
	POINT moving;
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
	int getAtk(Hero* h) { return h->cs.atkspd / 5 / h->cs.cnt; }
	int getAtk(Enemy* e) { return e->cs.atkspd / 5 / e->cs.cnt; }

	void Target(Hero*, vector<Enemy*>, RECT);
	void FindAtkDir(Hero*, vector<POINT> pts, RECT rect);
	void Damaged(Hero* h, FLOAT d) { h->cs.hp -= d; }
	void Damaged(Enemy* e, FLOAT d) { e->cs.hp -= d; }
	BOOL AttackAble(Hero*);
	BOOL AttackAble(Enemy*);
	void Move(Enemy*, RECT);
	void Move(Projectile* , RECT);
	bool isArrive(Enemy*);
};

#endif