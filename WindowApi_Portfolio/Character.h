#pragma once
#include "Astar.h"
#include <algorithm>

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

class Character
{
private:

protected:
	RECT rt;
	int hp;
	int range;
	int dps;
	vector<POINT> cpath;
	POINT curPos;
public:
	vector<Character*> characters;

	void Update(const RECT&);
	void FindPath();
	virtual void Create(){}
	virtual void Deal(){}
	virtual void Death(){}
};

class Hero :public Character
{
private:
	int cost;
	int chnum;
public:
	Hero();
	~Hero() {}
	vector<Hero*> heros;

	void Create(POINT pt, int chn);
	void Deal(Hero*);
	void Death();
};

class Enemy :public Character
{
protected:
	int type;
	int pathcount = 0;
	int cnt = 1;
	POINT respon = {1,0};
	POINT destin = {7,6};
	vector<POINT> path;
public:
	Enemy();
	~Enemy() {}
	vector<Enemy*> enemies;

	//void getSetting();
	int getCount() { return enemies.size(); }
	void Create(RECT rt);
	void Move(RECT rt);
	void DrawEnemy(HDC hdc);
	void Deal(Enemy*);
	void Death(int n);
};

#endif