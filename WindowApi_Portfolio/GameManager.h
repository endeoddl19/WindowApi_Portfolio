#pragma once

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "MapTool.h"
#include "Character.h"
#include <gdiplusgraphics.h>

class GameManager
{
private:
	GameStatus gs;
	RECT rect;
	Image* MapImage;
	Image* EnemyImage;
	Image* HeroImage[6];
	vector<POINT> cpath;
	POINT respon = { 1,0 };
	POINT destin = { 7,6 };
	BOOL buyAble[6];

	int cost[6] = { 100,150,200,150,200,300 };
	int MapInfo[ROW][COL] = { 0 };
	// 0: 일반 /  1: 길 /  2: 출발 / 3: 도착 / 4: 
	int mapw, maph;
	int state;
	// 0: 플레이 / 1: 일시정지

	void FindPath();
	void DrawEnemy(HDC hdc, Graphics* graphic);
	void DrawHero(HDC hdc, Graphics* graphic);
	void DrawProj(HDC hdc, Graphics* graphic);
	void DrawHpBar(HDC,POINT,FLOAT);
	void DrawRangeTile(Graphics*);
	void DrawAdjTile(Graphics*);
	void DrawBuyableTile(Graphics*);
public:
	vector<Character*> charcs;
	vector<Hero*> heros;
	vector<Enemy*> enems;
	vector<Projectile*> projs;
	GameManager();
	~GameManager() {}
	Utils ut;

	void SetGame(RECT rt);
	void CreateEnemy();
	void CreateHero(POINT pt, int hnum);
	void setState(int s) { state = s; }
	BOOL canCreate(POINT, int);
	BOOL isBuyable(int hnum) { return buyAble[hnum]; }

	void Update();
	void Play(HWND hWnd, HDC hdc);
	void Shoot(Character*);
	GameStatus CurStatus() { return gs; }

	void close();
};

#endif