#pragma once

#ifndef _MAPTOOL_H_
#define _MAPTOOL_H_

#include "framework.h"
#include <Windows.h>
#include <fstream>
#include <cstdio>

#define ROW 8
#define COL 8

using namespace Gdiplus;

struct Tile
{
	int spn;
	POINT pt;
};

class MapTool
{
private:
	RECT rect;
	Image* imgs[4];
	POINT curPos;
	POINT curTile;

	Tile Map[ROW][COL];
	//Image MapImage[ROW][COL];
	int rtw, rth, mapw, maph, spw, sph;
	int mapx, mapy, spx, spy;
	int spnum;
public:
	MapTool();
	~MapTool() { delete[]imgs; }

	bool posInMap(POINT pt);
	bool posInSp(POINT pt);
	POINT curposition() { return curPos; }
	POINT curtile() { return curTile; }

	void SetMapTool(RECT rt);
	void DrawSP(Graphics* graphic, int n);

	void Draw(HWND hWnd, HDC hdc, int n);
	void DrawCurTile(Graphics* graphic);
	void SelectTile(POINT pt, int n);
	void SetTile(POINT pt);
	void LoadMap();
	void SaveMap();
};

#endif