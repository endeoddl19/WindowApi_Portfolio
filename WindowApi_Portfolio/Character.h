#pragma once

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Astar.h"
#include "Utils.h"
#include <algorithm>

class Character
{
private:

protected:
	RECT rt;
	POINT dir;
	POINT curPos;

	FLOAT maxhp = 100;
	FLOAT hp = 70;
	int range = 5;
	int dps = 10;
	bool death = false;
public:
	Utils ut;

	void SetInitPos(POINT pt);
	POINT GetcurPos() { return curPos; }
	void FindAtkDir(vector<POINT> pts, RECT rect);
	POINT GetDir() { return dir; }
	FLOAT GetHP() { return (hp / maxhp); }
	virtual void Deal(){}
	BOOL Death() { return death; }
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
};

class Projectile :public Character
{
protected:
	int cnt = 1;
public:
	Projectile();
	~Projectile() {}

	void setDir(POINT pt) { dir = pt; }
	void Move(RECT rt);
};

#endif