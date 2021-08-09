#pragma once

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "MapTool.h"
#include "Character.h"

class GameManager
{
private:
	RECT rect;
	Image* MapImage;
	vector<POINT> cpath;
	POINT respon = { 1,0 };
	POINT destin = { 7,6 };
	
	int wave[4] = { 30,40,50,60 };
	int MapInfo[ROW][COL] = { 0 };
	// 0: 일반 /  1: 길 /  2: 출발 / 3: 도착 / 4: 
	int mapw, maph, size;

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
	~GameManager();
	Utils ut;

	void SetGame(RECT rt);
	void CreateEnemy();
	void CreateHero(POINT pt, int hnum);
	int getEnemCount() { return enems.size(); }

	void Update();
	void Play(HWND hWnd, HDC hdc);
	void Deal();
	void Clear();
};

#endif