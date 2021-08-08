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
	POINT curPos;
public:

	void SetInitPos(POINT pt);
	POINT GetcurPos() { return curPos; }
	virtual void Deal(){}
	virtual void Death(){}
};

class Hero :public Character
{
private:
	int cost;
	int heronum;
public:
	Hero();
	~Hero() {}

	void setHero(int h) { heronum = h; }
	void Death();
};

class Enemy :public Character
{
protected:
	int type;
	int pathcount = 0;
	int cnt = 1;
	vector<POINT> path;
public:
	Enemy();
	~Enemy() {}

	void setPath(vector<POINT> pa) { path = pa; }
	bool isArrive();
	void Move(RECT rt);
	void Death(int n);
};

#endif