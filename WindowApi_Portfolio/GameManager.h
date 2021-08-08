#pragma once
#include "MapTool.h"
#include "Character.h"

#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

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
	void DrawEnemy(HDC hdc);
	void DrawHero(HDC hdc);
public:
	vector<Character*> charcs;
	vector<Hero*> heros;
	vector<Enemy*> enems;
	GameManager();
	~GameManager(){}

	void SetGame(RECT rt);
	void CreateEnemy();
	void CreateHero(POINT pt, int hnum);
	int getEnemCount() { return enems.size(); }

	void Update();
	void Play(HWND hWnd, HDC hdc);
	void Clear();
};

#endif