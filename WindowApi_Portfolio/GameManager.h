#pragma once

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "MapTool.h"
#include "Character.h"
#include <gdiplusgraphics.h>

class GameManager
{
private:
	GameStatus gs = { 40, 300, 10, 1 };
	RECT rect;
	Image* MapImage;
	vector<POINT> cpath;
	POINT respon = { 1,0 };
	POINT destin = { 7,6 };
	
	int cost[3] = { 100,150,200 };
	int MapInfo[ROW][COL] = { 0 };
	// 0: 일반 /  1: 길 /  2: 출발 / 3: 도착 / 4: 
	int mapw, maph;

	void FindPath();
	void DrawEnemy(HDC hdc, Graphics* graphic);
	void DrawHero(HDC hdc, Graphics* graphic);
	void DrawProj(HDC hdc, Graphics* graphic);
public:
	vector<Character*> charcs;
	vector<Hero*> heros;
	vector<Enemy*> enems;
	vector<Projectile*> projs;
	GameManager();
	~GameManager() {}
	Utils ut;

	GameStatus SetGame(RECT rt);
	void CreateEnemy();
	void CreateHero(POINT pt, int hnum);
	int getCost(int hnum) { return cost[hnum]; }

	void Update();
	void Play(HWND hWnd, HDC hdc);
	void Shoot(Hero* hero);
	BOOL Purchase(int cost);
	GameStatus CurStatus() { return gs; }

	void close();
};

#endif