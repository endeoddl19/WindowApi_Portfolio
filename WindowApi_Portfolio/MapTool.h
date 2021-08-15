#pragma once

#ifndef _MAPTOOL_H_
#define _MAPTOOL_H_

#include "framework.h"
#include <Windows.h>
#include <fstream>
#include <cstdio>

using namespace Gdiplus;

struct Tile
{
	int spn;
	int index;
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

	TCHAR onBuff[128], info[128], str[128];
	TCHAR lpstrFile[128] = L"";
	TCHAR filter[64] = L"Every File(*.*)\0*.*\0Text File \0 *.txt;*.doc \0 ";
	DWORD sizeT = 512, c = 0;

	int rtw, rth, mapw, maph, spw, sph;
	int mapx, mapy, spx, spy;
	int spnum;
public:
	MapTool();
	~MapTool() { if (imgs[0] != nullptr) for (int i = 0; i < 4; i++) delete imgs[i];}

	bool posInMap(POINT);
	bool posInSp(POINT);
	POINT curposition() { return curPos; }
	POINT curtile() { return curTile; }

	void SetMapTool(RECT);
	void DrawSP(HDC, int);

	void Draw(HWND, HDC, int);
	void DrawCurTile(Graphics*);
	void SelectTile(POINT, int);
	void SetTile(POINT);

	void LoadMap(HWND, OPENFILENAME);
	void SaveMap(HWND, OPENFILENAME, OPENFILENAME);
};

#endif