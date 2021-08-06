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

	int MapInfo[ROW][COL] = { 0 };
	int mapw, maph;
public:
	GameManager();
	~GameManager(){}

	void SetGame(RECT rt);
	void Play(HWND hWnd, HDC hdc);
};

#endif