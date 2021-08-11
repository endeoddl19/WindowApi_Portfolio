#pragma once

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Astar.h"
#include "Utils.h"
#include <algorithm>
class Hero;
class Enemy;
class Projectile;

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
	int projsize;
	int state;
	// 0: idle / 1: move / 2: attack
	bool death = false;
public:
	Utils ut;

	void SetInitPos(POINT pt);
	POINT GetcurPos() { return curPos; }
	POINT GetDir() { return dir; }
	FLOAT GetHP() { return (hp / maxhp); }
	FLOAT GetCurHP() { return hp; }
	int setProjSize() { return projsize; }
	int setProjDmg() { return dmg; }
	int getState() { return state; }
	int getRange() { return range; }

	void FindAtkDir(vector<POINT> pts, RECT rect);
	void Damaged(FLOAT d) { hp -= d; }
	void Die() { death = true; }
	BOOL Death() { return death; }
	BOOL canShoot();
	
};

class Hero :public Character
{
private:
	int cost;
	int heronum;
public:
	Hero(int hnum);
	~Hero() {}

	void Collision(vector<Enemy*>);
	void Target(vector<Enemy*>, RECT);
	void setCost(int c) { cost = c; }
	int getHnum() { return heronum; }
};

class Enemy :public Character
{
private:
	int pathcount = 0;
	vector<POINT> path;
	POINT moving;
public:
	Enemy();
	~Enemy() {}

	void Collision(vector<Hero*>);
	void setPath(vector<POINT> pa) { path = pa; }
	POINT getMoving() { return path[pathcount + 1]; }
	bool isArrive();
	void Move(RECT rt);
};

class Projectile :public Character
{
private:
	int size;
	POINT init;
public:
	Projectile();
	~Projectile() {}

	void setProj(POINT, POINT, int, int, int);
	void Collision(vector<Enemy*>);
	int getSize() { return size; }
	void Move(RECT rt);
};

#endif