#pragma once
#include "framework.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

class Character
{
private:
	int hp;
	int range;
	FLOAT dps;
public:
	//Hero* heros[10];
	//Enemy* enemies[32];
	virtual void Create(){}
	void Death();
};

class Hero :public Character
{
private:
public:
	void Create(POINT pt);
};

class Enemy :public Character
{
private:
public:
	void Create();
};

#endif