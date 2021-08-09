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
	~MapTool() { if (imgs[0] != nullptr) delete[]imgs; }

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

	void LoadMap(HWND hWnd, OPENFILENAME OFN);
	void SaveMap(HWND hWnd, OPENFILENAME OFN, OPENFILENAME SFN);
};

#endif