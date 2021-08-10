#pragma once

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Astar.h"
#include "Utils.h"
#include <algorithm>
class Enemy;

class Character
{
private:
	RECT rt;
protected:
	POINT dir;
	POINT curPos;
	FLOAT maxhp;
	FLOAT hp;

	int range;
	int atkspd;
	int dmg;
	int cnt = 1;
	int state;
	// 0: idle / 1: move / 2: attack
	bool death = false;
public:
	Utils ut;

	void SetInitPos(POINT pt);
	POINT GetcurPos() { return curPos; }
	void FindAtkDir(vector<POINT> pts, RECT rect);
	POINT GetDir() { return dir; }
	FLOAT GetHP() { return (hp / maxhp); }
	FLOAT GetCurHP() { return hp; }
	void Damaged(FLOAT d) { hp -= d; }
	void Die() { death = true; }
	BOOL Death() { return death; }
	int getState() { return state; }
};

class Hero :public Character
{
private:
	int cost;
	int projsize;
	int heronum;
public:
	Hero(int hnum);
	~Hero() {}

	BOOL canShoot();
	void HasTarget(vector<Enemy*>);
	void setCost(int c) { cost = c; }
	int setProjSize() { return projsize; }
	int setProjDmg() { return dmg; }
	int getHnum() { return heronum; }
};

class Enemy :public Character
{
protected:
	int type;
	int pathcount = 0;
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
	int size;
public:
	Projectile();
	~Projectile() {}

	void setDir(POINT pt) { dir = pt; }
	void setSize(int s) { size = s; }
	void setDmg(int d) { dmg = d; }
	int getSize() { return size; }
	void Move(RECT rt);
	void Collision(vector<Enemy*>);
};

#endif